

int WATER_ATOM_PIN = 2;

void setup() {
  pinMode(WATER_ATOM_PIN, OUTPUT);
}

void loop() {
  digitalWrite(WATER_ATOM_PIN, HIGH);
  delay(10000);
  digitalWrite(WATER_ATOM_PIN, LOW);
  delay(5000);
}
