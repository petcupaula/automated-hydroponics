int phpin_value; 
int vplus = 5; //5V provided to the module
int samples = 10;

// Derived from ph_calibration/ph_calibration.org
float ph_offset = 21.34;//20.61;
float ph_coefficient = -5.72;//-5.23;

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

void loop() { 

  float samples_sum = 0;
  for(int i=0; i<samples; i++) {
    samples_sum += analogRead(A0); 
    delay(10);
    }
  phpin_value = samples_sum/samples;
  
  Serial.print("V: ");
  Serial.print(voltage(phpin_value));
  Serial.print(" pH: ");
  Serial.println(ph(phpin_value));
  delay(500);
}
