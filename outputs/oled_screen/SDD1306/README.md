# Outputs
## OLED Screen
Enables sending text to a standard oled screen via I2C.

[[Go back]](/outputs)

### Hardware
* ESP32
* OLED Screen

### [Code](SDD1306.ino)
```cpp
#include <Wire.h>  // Library for I2C communications
#include "SSD1306.h" // Library from U8g2 that enables interaction with the oled screen

#define OLED_SDA       4
#define OLED_SCL       15
#define OLED_RST       16
#define OLED_I2C_ADDR  0x3c

SSD1306 display(OLED_I2C_ADDR, OLED_SDA, OLED_SCL);  // Defines "display" variable

int upTime = 0;  // Defines a counter

void setup() {
  Serial.begin(9600);  // Starts the serial communication
  Serial.println("\nBooting device...");

  pinMode(OLED_RST, OUTPUT);  // Sets GPIO pin as output
  digitalWrite(OLED_RST, LOW);  // Turn Off screen
  digitalWrite(OLED_RST, HIGH);  // Turns On screen

  // Display setup
  display.init();
  display.flipScreenVertically();

  // Show some static text
  display.setFont(ArialMT_Plain_16);  // Sets font and size
  display.drawString(0, 0, "Hello World!");  // Sets text on position (0,0)
  display.display();  // Displays the configuration on the screen
}

void loop() {
  upTime++;  // Adds +1 to variable "upTime"
  Serial.println("Uptime: " + String(upTime) + "s");

  // Show some changing text
  display.setFont(ArialMT_Plain_16);  // Sets font and size
  display.drawString(0, 0, "Hello World!");  // Sets text on position (0,0)
  display.drawString(0, 24, "Uptime: " + String(upTime) + "s");  // Sets text on position (0,24)
  display.display();  // Displays the configuration
  display.clear();

  delay(1000);  // Freezes the loop for 1000 miliseconds
}
```

### Libraries
* _Wire_ by [Arduino](https://www.arduino.cc/en/reference/wire) - Preinstalled with Arduino IDE
* _SSD1306_ by ThingPulse, Fabrice Weinberg [Github](https://github.com/ThingPulse/esp8266-oled-ssd1306) - Installed from the Arduino IDE Library Management
![SSD1306](docs/SSD1306_installation.jpeg)