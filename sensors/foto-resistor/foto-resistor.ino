#define DARKNESS_RES 1000  // Resistance in darkness in KΩ
#define BRIGHTNESS_RES 15  // Resistance in brightness (10 Lux) in KΩ
#define CALIBRARION_RES 10 // Calibration resistance in KΩ
#define LDR_PIN 33         // LDR Pin

#define ANALOG_BIT_RESOLUTION 12.0

int voltage_measure;
int lux;

void setup() {
  Serial.begin(9600); // Starts the serial communication
  Serial.println("\nBooting device...");

  analogReadResolution(ANALOG_BIT_RESOLUTION); // Sets the reading resolution
                                               // value to 12 bits (0-4095)
}

void loop() {
  voltage_measure =
      analogRead(LDR_PIN); // Reads the value from the pin in a 0-4095
                           // resolution corresponding to a linear 0-3.3V

  lux = voltage_measure * DARKNESS_RES * 10 /
        (BRIGHTNESS_RES * CALIBRARION_RES *
         (pow(2.0, ANALOG_BIT_RESOLUTION) -
          voltage_measure)); // Use with LDR & Vcc

  Serial.println("Light intensity: " + String(lux) + " lux");

  delay(1000); // Check the light every 1000 miliseconds
}