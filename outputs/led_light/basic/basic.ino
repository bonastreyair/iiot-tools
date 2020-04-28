#define LED_PIN 3

void setup() {
  Serial.begin(9600); 
  Serial.println("\nBooting device...");
  
  pinMode(LED_PIN, OUTPUT);  // Pinout as output
}

void loop() {
  digitalWrite(LED_PIN, HIGH); // Set pin to HIGH
  delay(1000);  // Wait 1 second
  digitalWrite(LED_PIN, LOW);  // Set pin to LOW
  delay(1000);  // Wait 1 second
}