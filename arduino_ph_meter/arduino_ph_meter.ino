int phpin_value; 
int vplus = 5; //5V provided to the module

// Derived from ph_calibration/ph_calibration.org
float ph_offset = 20.61
float ph_coefficient = -5.23

void setup() 
{ 
  Serial.begin(9600);
} 

float ph(int val) {
  return  ph_coefficient* voltage(val) + ph_offset;
}

float voltage(int val) {
  return val * vplus / 1024.0; 
}

void loop() 
{ 
  phpin_value = analogRead(A0); 
  Serial.print("V: ");
  Serial.print(voltage(phpin_value));
  //Serial.print(" pH: ");
  Serial.print(" pH: ");
  Serial.println(ph(phpin_value));
  delay(500); 
}
