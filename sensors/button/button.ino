// constants won't change. They're used here to
// set pin number:
const int buttonPin = 2;     // the number of the pushbutton pin (2-> digital pin)

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
void setup() {
  Serial.begin(9600);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}
void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
  // Show the state of pushbutton on serial monitor
  Serial.println('Button pressed');
  } else {
  //Nothing
  }
  // Added the delay so that we can see the output of button
  delay(100);
}
