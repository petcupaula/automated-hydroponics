#!/usr/bin/env python3
import sys
import time
import glob
import serial
from Adafruit_IO import MQTTClient
import config

ADAFRUIT_IO_KEY = config.ADAFRUIT_IO_KEY
ADAFRUIT_IO_USERNAME = config.ADAFRUIT_IO_USERNAME
FEED_ID_CMDS = 'hydroponics'
FEED_ID_WATERTEMP = 'hydro-watertemp'
FEED_ID_PH = 'hydro-ph'
FEED_ID_TDS = 'hydro-tds'

def connected(client):
    print('Connected to Adafruit IO!  Listening for {0} changes...'.format(FEED_ID_CMDS))
    client.subscribe(FEED_ID_CMDS)

def subscribe(client, userdata, mid, granted_qos):
    print('Subscribed to {0} with QoS {1}'.format(FEED_ID_CMDS, granted_qos[0]))

def disconnected(client):
    print('Disconnected from Adafruit IO!')
    sys.exit(1)

def message(client, feed_id, payload):
    print('Feed {0} received new value: {1}'.format(feed_id, payload))
    ser.write((payload+"\n").encode('ascii'))

if __name__ == '__main__':
    ttys = glob.glob('/dev/ttyAC*')
    ser = serial.Serial(ttys[0], 9600, timeout=1)
    ser.flush()

    client = MQTTClient(ADAFRUIT_IO_USERNAME, ADAFRUIT_IO_KEY)

    client.on_connect    = connected
    client.on_disconnect = disconnected
    client.on_message    = message
    client.on_subscribe  = subscribe

    client.connect()

    client.loop_background()

    while True:
        ser.write(b"READ\n")
        line = ser.readline().decode('utf-8').rstrip()
        print(line)
        datadict = None
        if (line != ""):
             try:
                 datadict = eval(line)
                 print(datadict)
             except SyntaxError:
                 pass
        if (datadict):
             if ('Water Temperature (C)' in datadict):
                 value = datadict['Water Temperature (C)']
                 client.publish(FEED_ID_WATERTEMP, value)
             if ('pH' in datadict):
                 value = datadict['pH']
                 client.publish(FEED_ID_PH, value)
             if ('PPM' in datadict):
                 value = datadict['PPM']
                 client.publish(FEED_ID_TDS, value)
        time.sleep(20)


