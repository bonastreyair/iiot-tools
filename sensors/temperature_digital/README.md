# Sensors
## Temperature (Digital)
Using the DHT11 or the DHT22 sensors we can measure the air temperature.

[[Go back]](/sensors)

### Hardware
* ESP32
* [DHT11](docs/datasheet_dht11.pdf) - [DFRobot Source](https://image.dfrobot.com/image/data/KIT0003/DHT11%20datasheet.pdf)
* [DHT22](docs/datasheet_dht22.pdf) - [SparkFun Source](https://www.sparkfun.com/datasheets/Sensors/Temperature/DHT22.pdf)

### Code
```cpp
#include "DHT.h"  // Include DHT library

#define DHT_PIN  21     // Defines pin number to which the sensor is connected 
#define DHT_TYPE DHT22  // Defines the sensor type. It can be DHT11 or DHT22

DHT dht(DHT_PIN, DHT_TYPE);  // Defines the sensor dht

float temperature;  // Variable that will store the last temperature value

void setup(){
  Serial.begin(9600);  // Starts the serial communication

  Serial.println("Starting sensor...");
  dht.begin();  // Starts sensor communication
}

void loop(){
  tempreature = dht.readTemperature();  // Reads the temperature, it takes about 250 milliseconds
  
  Serial.println("Temperature: " + String(temperature) + "°C");  // Prints in a new line the result
  
  delay(1000);  // Freezes the loop for 1000 milliseconds
}
```
[[source]](temperature_digital.ino)

### Libraries
* DHT sensor library by [Adafruit](https://www.adafruit.com/) - Installed from the Arduino IDE Library Management
![dht_library](docs/dht_installation.png)