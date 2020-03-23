# Sensor
## Button
Using the button we can control the state of a LED.

### Hardware
* ESP32
* [Button](docs/datasheet_button.pdf) - [4donline Source](https://4donline.ihs.com/images/VipMasterIC/IC/OMRN/OMRN-S-A0001309768/OMRN-S-A0001309768-1.pdf?hkey=52A5661711E402568146F3353EA87419)
* [LED](docs/datasheet_led.pdf) - [Farnell Source](http://www.farnell.com/datasheets/2861525.pdf?_ga=2.19618812.573571583.1584967001-1225251318.1584967001) 

### Code
* [button.ino](button.ino)
```cpp
// constants won't change. They're used here to
// set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
void setup() {
  Serial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}
void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  // Show the state of pushbutton on serial monitor
  Serial.println(buttonState);
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
  // Added the delay so that we can see the output of button
  delay(100);
}
```

### Libraries
* No needed libraries
### Image
* [Connection image](docs/arduino_button.jpeg)
