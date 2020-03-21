# Sensors
## Humidity (Digital)

Using the DHT11 or the DHT22 sensors we can measure the air relative humidity.

### Hardware
* ESP32
* [DHT11](docs/datasheet_dht11.pdf) - [DFRobot Source](https://image.dfrobot.com/image/data/KIT0003/DHT11%20datasheet.pdf)
* [DHT22](docs/datasheet_dht22.pdf) - [SparkFun Source](https://www.sparkfun.com/datasheets/Sensors/Temperature/DHT22.pdf)

### Code
* [humidity_digital.ino](humidity_digital.ino)
```cpp
#include "DHT.h"  // Includes the DHT library

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
```

### Libraries
* DHT sensor library by [Adafruit](https://www.adafruit.com/) - Installed from the Arduino IDE Library Management
![dht_library](docs/dht_installation.png)