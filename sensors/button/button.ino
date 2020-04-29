#define BUTTON_PIN 2  // The number of the pushbutton pin (2-> digital pin)

void setup() {
  Serial.begin(9600);  // Starts the serial communication
  Serial.println("\nBooting device...");

  pinMode(BUTTON_PIN, INPUT);  // Initialize the button pin as an input
}

void loop() {
  static int buttonState;  // Variable for reading the pushbutton status

  buttonState = digitalRead(BUTTON_PIN);  // Read the state of the button value
  // Show the state of button on serial monitor
  if (buttonState == HIGH) {
    Serial.println('Button is pressed');
  } else {
    Serial.println('Button is not pressed');
  }
  delay(1000);  // Check the button every 1000 miliseconds
}