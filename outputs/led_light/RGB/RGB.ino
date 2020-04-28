#define RED_PIN   3
#define GREEN_PIN 4
#define BLUE_PIN  5

void setup() {
  Serial.begin(9600);
  Serial.println("\nBooting device...");
  
  pinMode(RED_PIN, OUTPUT);  // Pinout as output
  pinMode(RED_PIN, OUTPUT);  // Pinout as output
  pinMode(RED_PIN, OUTPUT);  // Pinout as output
}

void loop() {
  setColor('red');
  delay(1000);
  setColor('green');
  delay(1000);
  setColor('white');
  delay(1000);
  setRGB(13, 227, 201);  // Mix color
  delay(1000);
  setColor('black')  // Turn off
  delay(1000);
}

/* Additional functions */
void setRGB(int R, int G, int B) {
  digitalWrite(RED_PIN, R);
  digitalWrite(GREEN_PIN, G);
  digitalWrite(BLUE_PIN, B);
}

void setColor(char color) {
  if (color == 'red') {
    setRGB(255, 0, 0);
  } else if (color == 'green') {
    setRGB(0, 255, 0);
  } else if (color == 'blue') {
    setRGB(0, 0, 255);
  } else if (color == 'white') {
    setRGB(255, 255, 255);
  } else if (color == 'black') {
    setRGB(0, 0, 0);
  }
}