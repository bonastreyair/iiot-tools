#include <DallasTemperature.h>  // Includes the Dallas Temperature library
#include <OneWire.h>  // Includes the One Wire library

#define DS18B20_PIN 5  // Number pin where the sensor is connected to

OneWire oneWire(DS18B20_PIN);
DallasTemperature ds18b20Sensor(&oneWire);

void setup() {
  Serial.begin(9600);
  Serial.println("\nBooting device...");
  
  ds18b20Sensor.begin();
}

void loop() {
  static float tempCelcius;
  static float tempFarenheit;
  ds18b20Sensor.requestTemperatures();
  tempCelcius = ds18b20Sensor.getTempCByIndex(0);  // Reads temp in Celcius
  tempFarenheit = ds18b20Sensor.getTempFByIndex(0);  // Reads temp in Farenheit

  if (isnan(tempCelcius) || isnan(tempFarenheit)) {  // Check if there is any reading error
    Serial.println("Error reading Sensor DS18B20");
  } else {
    Serial.println("Temperature: " + String(tempCelcius) + "°C - " + String(tempFarenheit) + "°F");
  }
  delay(1000);  // Waits for 1000 miliseconds
}
