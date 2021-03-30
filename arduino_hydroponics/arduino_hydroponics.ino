#include "DHT.h"
#include <Adafruit_AS7341.h>
#include <EEPROM.h>
#include "GravityTDS.h"

// DHT - temp & humidity
#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Ultrasonic sensor - distance
#define TRIGPIN 8
#define ECHOPIN 9
long duration;
int distance;

// Color sensor AS7341
Adafruit_AS7341 as7341;

// TDS sensor
#define TDSPIN A1
GravityTDS gravityTds;
float temperature = 25.0;
float tdsValue = 0;
float vplusTDS = 3.3; // connected to 3.3 or 5V

// pH sensor
#define PHPIN A0
int phpin_value; 
int vplusPH = 5; // connected to 3.3 or 5V
float ph_offset = 21.34;//20.61;
float ph_coefficient = -5.72;//-5.23;

float adcRef = 1024.0;

// Fan
#define FANPIN 10
bool fanOn = false;

// Grow lights
#define LIGHTPIN 11
bool lightsOn = false;

// Water atomizer
#define ATOMPIN 2
bool waterAtomOn = false;

// Air pump
#define AIRPIN 12
bool airPumpOn = false;

// Water pump
#define WATERPIN 13
bool waterPumpOn = false;

void setup()
{
  Serial.begin(9600);
  
  dht.begin();

  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);

  as7341.begin();
  as7341.setATIME(100);
  as7341.setASTEP(999);
  as7341.setGain(AS7341_GAIN_256X);

  gravityTds.setPin(TDSPIN);
  gravityTds.setAref(vplusTDS);
  gravityTds.setAdcRange(adcRef);
  gravityTds.begin();

  pinMode(FANPIN, OUTPUT);
  turnFanOff();
  
  pinMode(LIGHTPIN, OUTPUT);
  turnLightsOff();

  pinMode(ATOMPIN, OUTPUT);

  pinMode(AIRPIN, OUTPUT);
  turnAirPumpOff();
  
  pinMode(WATERPIN, OUTPUT);
  turnWaterPumpOff();

  //Serial.println("Starting...");
  
}

void loop()
{

  // Wait a few seconds between measurements.
  // delay(5000);
  
  if (Serial.available() > 0) {
      String data = Serial.readStringUntil('\n');
      //Serial.print("You sent me (string): ");
      //Serial.println(data);

  Serial.print("{");
  getDHT();
  getUltrasonic();
  getColors();
  getTDS();
  getPH();

//  if(temperature>22) {
//    if (fanOn == false) {
//      turnFanOn();
//    }
//  }
//  else {
//    if (fanOn == true) {
//      turnFanOff();
//      
//    }
//  }

//  if(distance>5) {
//    if (lightsOn == false) {
//      turnLightsOn();
//    }
//  }
//  else {
//    if (lightsOn == true) {
//      turnLightsOff();
//    }
//  }


//  if(distance>5) {
//    if (waterAtomOn == false) {
//      turnWaterAtomOn();
//    }
//  }
//  else {
//    if (waterAtomOn == true) {
//      turnWaterAtomOff();
//    }
//  }

//  if(distance>5) {
//    if (airPumpOn == false) {
//      turnAirPumpOn();
//    }
//  }
//  else {
//    if (airPumpOn == true) {
//      turnAirPumpOff();
//    }
//  }

//  if(distance>5) {
//    if (waterPumpOn == false) {
//      turnWaterPumpOn();
//    }
//  }
//  else {
//    if (waterPumpOn == true) {
//      turnWaterPumpOff();
//    }
//  }

  Serial.println("}");
}
}


void getUltrasonic() {
  // Clear the trigPin
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  
  // Set the trigPin on HIGH state for 10 micro seconds
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);
  
  // Read the echoPin, return the sound wave travel time in microseconds
  duration = pulseIn(ECHOPIN, HIGH);
  
  // Calculate the distance
  // The speed of sound is 0.034 cm/ns
  // time = distance / speed => distance = time * speed
  // but /2 because sound has at this point traveled towards and back from the object
  distance = duration * 0.034 / 2;
  
  Serial.print(", 'Distance (cm)': ");
  Serial.print(distance);
}

void getDHT() {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    //Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  temperature = t;

  Serial.print(F("'Humidity (%)': "));
  Serial.print(h);
  Serial.print(F(", 'Temperature (C)': "));
  Serial.print(t);  
}

void getColors() {
  // Read all channels at the same time and store in as7341 object
  if (!as7341.readAllChannels()){
    //Serial.println("Error reading all channels!");
    return;
  }

  // Print out the stored values for each channel
  Serial.print(", 'F1 415nm (Violet)': ");
  Serial.print(as7341.getChannel(AS7341_CHANNEL_415nm_F1));
  Serial.print(", 'F2 445nm (Indigo)': ");
  Serial.print(as7341.getChannel(AS7341_CHANNEL_445nm_F2));
  Serial.print(", 'F3 480nm (Blue)': ");
  Serial.print(as7341.getChannel(AS7341_CHANNEL_480nm_F3));
  Serial.print(", 'F4 515nm (Cyan)': ");
  Serial.print(as7341.getChannel(AS7341_CHANNEL_515nm_F4));
  Serial.print(", 'F5 555nm (Green)': ");
  Serial.print(as7341.getChannel(AS7341_CHANNEL_555nm_F5));
  Serial.print(", 'F6 590nm (Yellow)': ");
  Serial.print(as7341.getChannel(AS7341_CHANNEL_590nm_F6));
  Serial.print(", 'F7 630nm (Orange)': ");
  Serial.print(as7341.getChannel(AS7341_CHANNEL_630nm_F7));
  Serial.print(", 'F8 680nm (Red)': ");
  Serial.print(as7341.getChannel(AS7341_CHANNEL_680nm_F8));
  Serial.print(", 'Clear': ");
  Serial.print(as7341.getChannel(AS7341_CHANNEL_CLEAR));
  Serial.print(", 'Near IR': ");
  Serial.print(as7341.getChannel(AS7341_CHANNEL_NIR));
}

void getTDS() {
  gravityTds.setTemperature(temperature);  // set the temperature and execute temperature compensation
  gravityTds.update();  //sample and calculate 
  tdsValue = gravityTds.getTdsValue();  // then get the value
  Serial.print(", 'TDS_V': ");
  Serial.print(voltage(analogRead(TDSPIN),vplusTDS));
  Serial.print(", 'TDS_Vref': ");
  Serial.print(vplusTDS);
  Serial.print(", 'TDS_aSteps': ");
  Serial.print(adcRef,0);
  Serial.print(", 'PPM': ");
  Serial.print(tdsValue);
}


float ph(int val) {
  return  ph_coefficient* voltage(val, vplusPH) + ph_offset;
}

float voltage(int val, int vRef) {
  return val * vRef / adcRef; 
}

void getPH() {
  phpin_value = analogRead(PHPIN); 
  Serial.print(", 'pH_V': ");
  Serial.print(voltage(phpin_value, vplusPH));
  Serial.print(", 'pH_Vref': ");
  Serial.print(vplusPH);
  Serial.print(", 'ph_aSteps': ");
  Serial.print(adcRef,0);
  Serial.print(", 'pH': ");
  Serial.print(ph(phpin_value));
}

void turnFanOn() {
  digitalWrite(FANPIN, LOW);
  fanOn = true;
}

void turnFanOff() {
  digitalWrite(FANPIN, HIGH);
  fanOn = false;
}

void turnLightsOn() {
  digitalWrite(LIGHTPIN, LOW);
  lightsOn = true;
}

void turnLightsOff() {
  digitalWrite(LIGHTPIN, HIGH);
  lightsOn = false;
}

void turnWaterAtomOn() {
  digitalWrite(ATOMPIN, HIGH);
  waterAtomOn = true;
}

void turnWaterAtomOff() {
  digitalWrite(ATOMPIN, LOW);
  waterAtomOn = false;
}

void turnAirPumpOn() {
  digitalWrite(AIRPIN, LOW);
  airPumpOn = true;
}

void turnAirPumpOff() {
  digitalWrite(AIRPIN, HIGH);
  airPumpOn = false;
}

void turnWaterPumpOn() {
  digitalWrite(WATERPIN, LOW);
  waterPumpOn = true;
}

void turnWaterPumpOff() {
  digitalWrite(WATERPIN, HIGH);
  waterPumpOn = false;
}
