#define BUTTON_PIN 2  // The number of the pushbutton pin (2-> digital pin)

int buttonState = 0;  // Variable for reading the pushbutton status

void setup() {
  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT);  // Initialize the button pin as an input
}

void loop() {
  buttonState = digitalRead(BUTTON_PIN);  // Read the state of the button value
  
  // Show the state of button on serial monitor
  if (buttonState == HIGH) {
    Serial.println('Button pressed');
  } else {
    Serial.println('Button is not pressed');
  }

  delay(1000);  // Check the button every 1000 miliseconds
}