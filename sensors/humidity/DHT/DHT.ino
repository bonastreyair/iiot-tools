#include "DHT.h"  // Include DHT library

#define DHT_PIN  21     // Defines pin number to which the sensor is connected 
#define DHT_TYPE DHT22  // Defines the sensor type. It can be DHT11 or DHT22

DHT dht(DHT_PIN, DHT_TYPE);  // Defines the sensor

float humidity;  // Variable that will store the last humidity value

void setup(){
  Serial.begin(9600);  // Starts the serial communication

  Serial.println("Starting sensor...");
  dht.begin();  // Starts sensor communication
}

void loop(){
  humidity = dht.readHumidity();  // Reads the humidity, it takes about 250 milliseconds
  
  Serial.println("Humidity: " + String(humidity) + "%");  // Prints in a new line the result
  
  delay(1000);  // Freezes the loop for 1000 milliseconds
}