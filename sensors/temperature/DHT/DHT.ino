#include "DHT.h"  // Include DHT library

#define DHT_PIN  21  // Defines pin number to which the sensor is connected 
#define DHT_TYPE DHT22  // Defines the sensor type. It can be DHT11 or DHT22

DHT dhtSensor(DHT_PIN, DHT_TYPE);  // Defines the sensor dht

void setup() {
  Serial.begin(9600);  // Starts the serial communication
  Serial.println("\nBooting device...");

  dhtSensor.begin();  // Starts sensor communication
}

void loop() {
  static float tempreature;
  tempreature = dhtSensor.readTemperature();  // Reads the temperature, it takes about 250 milliseconds
  Serial.println("Temperature: " + String(temperature) + "°C");  // Prints in a new line the result

  delay(1000);  // Freezes the loop for 1000 milliseconds
}