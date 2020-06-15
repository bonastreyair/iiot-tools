# Outputs
## LED Light - Basic
Using a basic LED Light.

[[Go back]](/outputs/led_light)

### Hardware
- ESP32
- [Simple LED](../docs/basic.png)

### [Code](basic.ino)
```cpp
#define LED_PIN 25

void setup() {
  Serial.begin(9600);
  Serial.println("\nBooting device...");

  pinMode(LED_PIN, OUTPUT); // Pinout as output
}

void loop() {
  digitalWrite(LED_PIN, HIGH); // Set pin to HIGH
  delay(1000);                 // Wait 1 second
  digitalWrite(LED_PIN, LOW);  // Set pin to LOW
  delay(1000);                 // Wait 1 second
}
```

### Libraries
- No needed libraries

### Connection
![Connection basic LED light](../docs/connection_basic.jpeg)

[[Go back]](/outputs/led_light)