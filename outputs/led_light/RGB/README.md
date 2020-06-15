# Outputs
## LED Light - RGB
Using an RGB LED. 

[[Go back]](/outputs/led_light)

### Hardware
- ESP32
- [RGB LED](../docs/RGB.jpg)
- Resistor - 330 Ohm

### [Code](RGB.ino)
```cpp
#define RED_PIN 25
#define GREEN_PIN 14
#define BLUE_PIN 27

void setup() {
  Serial.begin(9600);
  Serial.println("\nBooting device...");

  pinMode(RED_PIN, OUTPUT); // Pinout as output
  pinMode(GREEN_PIN, OUTPUT); // Pinout as output
  pinMode(BLUE_PIN, OUTPUT); // Pinout as output
}

void loop() {
  setColor("red");
  delay(1000);
  setColor("green");
  delay(1000);
  setColor("blue");
  delay(1000);
}

/* Additional functions */
void setRGB(int R, int G, int B) {
  digitalWrite(RED_PIN, R);
  digitalWrite(GREEN_PIN, G);
  digitalWrite(BLUE_PIN, B);
}

void setColor(const char* color) {
  if (color == "red") {
    setRGB(1, 0, 0);
  } else if (color == "green") {
    setRGB(0, 1, 0);
  } else if (color == "blue") {
    setRGB(0, 0, 1);
  }
}
```

### Libraries
- No needed libraries

### Connection
![Connection RGB LED light](../docs/connection_RGB.png)

[[Go back]](/outputs/led_light)
