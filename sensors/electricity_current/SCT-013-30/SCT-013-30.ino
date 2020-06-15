#define SCT013 34

void setup() {
  Serial.begin(9600);
  Serial.println("\nBooting device...");
}

void loop() {
  delay(3000);
  float tension = 225.00;
  float irms = readEnergyConsumption();  // Corriente eficaz (A)
  float P = irms * tension;  // P = I*V (Watts)
  Serial.print("irms: ");
  Serial.print(irms, 3);
  Serial.print("A, Potencia: ");
  Serial.print(P, 3);
  Serial.println("W");
}

float readEnergyConsumption() {
  float sensorVoltage;
  float current = 0;
  float sumatory = 0;
  long time = millis();
  int N = 0;

  while (millis() - time < 500) {  // Duración 0.5 segundos (Aprox. 25 ciclos de 50Hz)
    sensorVoltage = (analogRead(34) * (3.3 / 4095.0)) / 8;
    current = sensorVoltage * 25.5;  // current = sensorVoltage * (20A / 1V)
    sumatory = sumatory + sq(current);  // sumatory of square roots
    N = N + 1;
    delay(1);
  }
  sumatory = sumatory * 2;  // compensates the squares of the negative semicicles
  current = sqrt((sumatory) / N);  // RMS equation
  return current;
}
