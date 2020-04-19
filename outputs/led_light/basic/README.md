# Outputs
## LED Light - Basic
Using a basic LED Light.

[[Go back]](/outputs/led_light)

### Hardware
* ESP32
* [Simple LED](docs/basic.png)

### [Code](basic.ino)
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

### Libraries
* No needed libraries

### Connection
![Connection basic LED light](docs/connection_basic.jpeg)