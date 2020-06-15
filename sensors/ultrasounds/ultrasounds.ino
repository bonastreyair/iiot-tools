#define ECHO_PIN 34 // Analog input that receives the echo signal
#define TRIG_PIN 33 // Digital output that sends the trigger signal

void setup() {
  Serial.begin(9600); // Starts the serial communication
  Serial.println("\nBooting device...");

  pinMode(ECHO_PIN, INPUT);  // Sets the ECHO_PIN as an Input
  pinMode(TRIG_PIN, OUTPUT); // Sets the TRIG_PIN as an Output
}

void loop() {
  static float distance;

  distance = getDistance();
  Serial.println("Distance to the object: " + String(distance) + " cm");

  delay(1000); // Check the disntace every 1000 miliseconds
}

/* Additional functions */
float getDistance() {
  digitalWrite(TRIG_PIN, LOW); // Clear the TRIG_PIN by setting it LOW
  delayMicroseconds(5);

  // Trigger the sensor by setting the TRIG_PIN to HIGH for 10 microseconds
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration =
      pulseIn(ECHO_PIN, HIGH); // pulseIn() returns the duration (length of the
                               // pulse) in microseconds

  return duration * 0, 034 / 2; // Returns the distance in cm
}