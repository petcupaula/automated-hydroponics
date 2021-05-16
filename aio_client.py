#!/usr/bin/env python3
import sys
import glob
import serial
from Adafruit_IO import MQTTClient
import config

ADAFRUIT_IO_KEY = config.ADAFRUIT_IO_KEY
ADAFRUIT_IO_USERNAME = config.ADAFRUIT_IO_USERNAME
FEED_ID = 'hydroponics'

def connected(client):
    print('Connected to Adafruit IO!  Listening for {0} changes...'.format(FEED_ID))
    client.subscribe(FEED_ID)

def subscribe(client, userdata, mid, granted_qos):
    print('Subscribed to {0} with QoS {1}'.format(FEED_ID, granted_qos[0]))

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

    client.loop_blocking()
