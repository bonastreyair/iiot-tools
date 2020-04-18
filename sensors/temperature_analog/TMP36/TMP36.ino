#define TMPPIN 32

void setup() {
  Serial.begin(9600);
}

void loop() {  
  int reading = analogRead(TMPPIN);
  //Serial.print("Reading: ");
  //Serial.println(reading);
  float voltage = reading * 3.3;
  voltage /= 4095.0;
  float temp_TMP36 = (voltage * 50);
  
  Serial.print("Temperatura_TMP36: ");
  Serial.println(temp_TMP36);
}
