#!/usr/bin/env python3
import serial
import random
import time
import datetime

if __name__ == '__main__':
  ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
  ser.flush()

  while True:
    ser.write(b"READ\n")
    #ser.write((str(random.randint(10,170))+'\n').encode('utf-8'))
    line = ser.readline().decode('utf-8').rstrip()
    print("[" + datetime.datetime.now().strftime('%m-%d-%Y_%H.%M.%S') + "] " + line)
    time.sleep(5)
    ser.write(b"WATERATOM\n")
    time.sleep(5)


