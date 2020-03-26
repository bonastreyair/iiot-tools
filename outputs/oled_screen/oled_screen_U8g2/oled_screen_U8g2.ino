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
