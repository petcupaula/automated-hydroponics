const int trigPin = 8;
const int echoPin = 9;

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  Serial.begin(9600);
}

void loop() {
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Set the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echoPin, return the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  // The speed of sound is 0.034 cm/ns
  // time = distance / speed => distance = time * speed
  // but /2 because sound has at this point traveled towards and back from the object
  distance = duration * 0.034 / 2;
  
  Serial.print("Distance (cm): ");
  Serial.println(distance);
}
