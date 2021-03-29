# automated-hydroponics
Automated home garden using hydroponics concepts

## Components

* Net cup for hydroponics: buy or 3d print (https://www.thingiverse.com/make:893504)
* Plant grow lights (https://www.aliexpress.com/item/1005001599994011.html)
* DHT22 temperature and humidity sensor (https://learn.adafruit.com/dht)
* Light/color sensor AS7341 (https://www.adafruit.com/product/4698)
  * Instructions: https://learn.adafruit.com/adafruit-as7341-10-channel-light-color-sensor-breakout?view=all
  * Datasheet: https://ams.com/documents/20143/36005/AS7341_DS000504_3-00.pdf/
  * Connecting with Arduino Uno - Arduino library: Adafruit AS7341
  * Connecting with ESP32 - Arduino library: https://github.com/DFRobot/DFRobot_AS7341
* PH meter - DIYmore pH Sensor PH-4502C (https://www.aliexpress.com/item/32957428276.html)
  * Instructions: https://www.youtube.com/watch?v=zUEl3Y3yKL4&ab_channel=ElectronicClinic / https://www.electroniclinic.com/ph-meter-arduino-ph-meter-calibration-diymore-ph-sensor-arduino-code/ / https://cimpleo.com/blog/simple-arduino-ph-meter/ / https://scidle.com/how-to-use-a-ph-sensor-with-arduino/
  * Pins: V (Can be used with 5V and 3.3V compatible controller boards), GND, GND, Po (PH analog output), Do (3.3V pH limit trigger), To (analog temperature output)
* TDS sensor - (https://www.aliexpress.com/item/4001010691199.html)
  * Instructions: https://wiki.dfrobot.com/Gravity__Analog_TDS_Sensor___Meter_For_Arduino_SKU__SEN0244
* Ultrasound mist - Water Atomization Grove actuator (https://www.seeedstudio.com/Grove-Water-Atomization-v1-0.html)
* Water level - HC-SR04 Ultrasonic Sensor
  * Instructions: https://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/
* Fan 5V (https://www.adafruit.com/product/4468)
* Air pump 5V (https://www.adafruit.com/product/4700) 
* Air stone (https://www.aliexpress.com/item/32942776713.html)
* Water pump 5V (https://www.banggood.com/DIY-Automatic-Irrigation-Module-Kit-Soil-Moisture-Detection-Automatic-Watering-Pumping-p-1338728.html)
* Camera

## Schematics

![Schematics](hydroponics_schematic_bb.png?raw=true "Schematics")
