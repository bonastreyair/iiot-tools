# Outputs
## OLED Screen
Enables sending text to a standard oled screen via I2C.

[[Go back]](/outputs)

### Hardware
* ESP32
* OLED Screen

### [Code]
## [SDD1306](oled_screen_SDD1306/oled_screen_SDD1306.ino)
```cpp
#include <Wire.h>    // Library for I2C communications
#include "SSD1306.h" // Library from U8g2 that enables interaction with the oled screen


#define OLED_SDA       4
#define OLED_SCL       15
#define OLED_RST       16
#define OLED_I2C_ADDR  0x3c

SSD1306 display(OLED_I2C_ADDR, OLED_SDA, OLED_SCL);  // Defines "display" variable

int up_time = 0;  // Defines a counter

void setup(){
  Serial.begin(9600);  // Starts the serial communication
  Serial.println("\nBooting device...");
  
  pinMode(OLED_RST, OUTPUT);  // Sets GPIO pin as output
  digitalWrite(OLED_RST, LOW);  // Turn Off screen
  digitalWrite(OLED_RST, HIGH);  // Turns On screen

  // Display setup
  display.init();
  display.flipScreenVertically();

}

void loop(){
  up_time++;  // Adds +1 to variable "up_time"
  Serial.println("Uptime: " + String(up_time) + "s");

  // Show some changing text
  display.setFont(ArialMT_Plain_16);  // Sets font and size
  display.drawString(0, 0, "Hello World!");  // Sets text on position (0,0)
  display.drawString(0, 24, "Uptime: " + String(up_time) + "s");  // Sets text on position (0,24)
  display.display();  // Displays the configuration
  display.clear();

  delay(1000);  // Freezes the loop for 1000 miliseconds
  
}
```

## [U8g2](oled_screen_U8g2/oled_screen_U8g2.ino)
```cpp
#include <U8g2lib.h>
#include <Wire.h>    // Library for I2C communications

#define OLED_SDA       4
#define OLED_SCL       15
#define OLED_RST       16

U8G2_SSD1306_128X64_NONAME_F_HW_I2C display(U8G2_R0, OLED_RST, OLED_SCL, OLED_SDA);   // ESP32 Thing, HW I2C with pin remapping

int up_time = 0;  // Defines a counter
int x = 0;
int y = 20;
  
void setup(){
  Serial.begin(9600);  // Starts the serial communication
  Serial.println("\nBooting device...");
  
  pinMode(OLED_RST, OUTPUT);  // Sets GPIO pin as output
  digitalWrite(OLED_RST, LOW);  // Turn Off screen
  digitalWrite(OLED_RST, HIGH);  // Turns On screen

  // Display setup
  display.begin();
  //display.setFont(u8g2_font_ncenB08_tr); //Sets font and size
  display.setFont(u8g2_font_unifont_t_symbols);
  
  //Display Orientation
  //display.u8g2.setDisplayRotation(U8G2_R0);
  display.setDisplayRotation(U8G2_R0);
  //display.u8g2.setDisplayRotation(U8G2_R2);
  //display.u8g2.setDisplayRotation(U8G2_R3);
  display.setFlipMode(0);
  //display.setFlipMode(1);


  //Show some statis text
  display.clearBuffer();          // clear the internal memory
  display.drawStr(0, 10, "Hello World!");  // write something to the internal memory
  display.sendBuffer();          // transfer internal memory to the display
  delay(2000);
}

void loop(){
   for( y = 20; y <= 64; y=y+10){
    for( x = 0; x <= 128; x=x+10){ 
      display.clearBuffer();
      display.drawGlyph(x, y, 9731);  /* dec 9731/hex 2603 Snowman */
      display.sendBuffer();
      delay(500);
    }
    x=0;
  }
  y=0;

}
```
### Libraries
* _Wire_ by [Arduino](https://www.arduino.cc/en/reference/wire) - Preinstalled with Arduino IDE
* _SSD1306_ by ThingPulse, Fabrice Weinberg [Github](https://github.com/ThingPulse/esp8266-oled-ssd1306) - Installed from the Arduino IDE Library Management
![SSD1306](docs/SSD1306_installation.jpeg)
* _U8g2_ by oliver [Github](https://github.com/olikraus/u8g2) - Installed from the Arduino IDE Library Management
![u8g2](docs/u8g2_installation.png)
