
int floatSwitch = 3;

void setup() {
  Serial.begin(9600);
  pinMode(floatSwitch, INPUT_PULLUP);
}

void loop() {
  
  int floatState = digitalRead(floatSwitch);

  if (floatState == LOW) 
  { 
    Serial.println( "WATER LEVEL - HIGH"); 
  } 
  else 
  { 
    Serial.println( "WATER LEVEL - LOW" ); 
  } 
  delay(1000);
}
