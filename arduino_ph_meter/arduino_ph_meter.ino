int phpin_value; 
int vplus = 5; //5V provided to the module
float calibration_value = 21.34 + 0.20;

void setup() 
{ 
  Serial.begin(9600);
} 

float ph(int val) {
  return val * 14.0 / 1023.0;
}

float ph_adj(int val) {
  return -5.70 * voltage(val) + calibration_value;
}

float voltage(int val) {
  return val * vplus / 1023.0; 
}

void loop() 
{ 
  phpin_value = analogRead(A0); 
  Serial.print("V: ");
  Serial.print(voltage(phpin_value));
  //Serial.print(" pH: ");
  //Serial.print(ph(phpin_value));
  Serial.print(" pH adj: ");
  Serial.println(ph_adj(phpin_value));
  delay(500); 
}
