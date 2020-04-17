# Outputs
## LED Light
Using basic led and RGB led. 

[[Go back]](/outputs)

### Hardware
* ESP32
* [Button](docs/datasheet_button.pdf) - [4donline Source](https://4donline.ihs.com/images/VipMasterIC/IC/OMRN/OMRN-S-A0001309768/OMRN-S-A0001309768-1.pdf?hkey=52A5661711E402568146F3353EA87419)

### [Code basic LED Light](basic/basic.ino)
```cpp
const int ledPIN = 3; //Pin where you connect led
 
void setup() {
  Serial.begin(9600);    //start serial port
  pinMode(ledPIN , OUTPUT);  //pinout as output
}
 
void loop(){
  digitalWrite(ledPIN , HIGH);   // set pin to HIGH
  delay(1000);                   // wait a second
  digitalWrite(ledPIN , LOW);    // set pin to LOW
  delay(1000);                   // wait a second
}
```


### [Code RGB LED Light](RGB/RGB.ino)
```cpp
const int BluePIN = 4; 
const int GreenPIN = 3; 
const int RedPIN = 5;
 
void setup() {
  Serial.begin(9600);    //start serial port
  pinMode(RedPIN , OUTPUT);  //pinout as output
  pinMode(GreenPIN , OUTPUT);  //pinout as output
  pinMode(BluePIN , OUTPUT);  //pinout as output
}
 
void loop()
   {    Color(255 ,0 ,0) ;//Red
        delay(1000); 
        Color(0,255 ,0) ;//Green
        delay(1000);
        Color(0 ,0 ,255) ;//Blue
        delay(1000);
    //If you have only digital output, you can't send these values.
    //Because you only send 1 or 0. When you send these values with
    //digital output, you really send 1 at the same time in all outputs.
    //For that reason, led will be white
        Color(13,227,201); // Mix Color or White
        delay(1500);
        Color(0,0,0);
        delay(1500);
   }

void Color(int R, int G, int B)
{
  digitalWrite(RedPIN, R); 
  digitalWrite(GreenPIN, G);
  digitalWrite(BluePIN, B);
}
```

### Libraries
* No needed libraries

### Connection
![Connection basic LED light](docs/connection_basic.jpeg)

![Connection RGB LED light](docs/arduino_RGB.jpeg)

