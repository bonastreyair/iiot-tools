const int ledPIN = X; //Pin where you connect led

void setup() {
	Serial.begin(9600);    //start serial port
	pinMode(ledPIN , OUTPUT);  //pinout as output
}

void loop() {
	digitalWrite(ledPIN , HIGH);   // set pin to HIGH
	delay(1000);                   // wait a second
	digitalWrite(ledPIN , LOW);    // set pin to LOW
	delay(1000);                   // wait a second
}
