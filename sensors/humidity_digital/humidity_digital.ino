#include "DHT.h"

#define DHT_PIN 21  // Defines pin number to which the sensor is connected 
#define DHT_TYPE DHT22  // Defines the sensor type. It can be DHT11 or DHT22
#define REFRESH_RATE  2 // Defined in seconds

DHT dht(DHT_PIN, DHT_TYPE);  // Defines the sensor
float h;  // Variable that will store the last humidity value

void setup(){
  Serial.begin(9600);

  Serial.println("Starting sensor...");
  dht.begin();  // Starts sensor communication
}

void loop(){
  h = dht.readHumidity();  // Reads the humidity, it takes about 250 milliseconds
  
  Serial.println("Humidity: " + String(h) + "%");  // Prints in a new line the result
  
  delay(REFRESH_RATE*1000);  // Freezes the loop for X milliseconds
}
