# Sensors
## Humidity - DHT (Digital)
Using the DHT11 or the DHT22 sensors we can measure the air relative humidity.

[[Go back]](/sensors/humidity)

### Hardware
- ESP32
- [DHT11](../docs/datasheet_dht11.pdf) - [DFRobot Source](https://image.dfrobot.com/image/data/KIT0003/DHT11%20datasheet.pdf)
- [DHT22](../docs/datasheet_dht22.pdf) - [SparkFun Source](https://www.sparkfun.com/datasheets/Sensors/Temperature/DHT22.pdf)

### [Code](DHT.ino)
```cpp
#include "DHT.h" // Include DHT library

#define DHT_PIN 22     // Defines pin number to which the sensor is connected
#define DHT_TYPE DHT11 // Defines the sensor type. It can be DHT11 or DHT22

DHT dhtSensor(DHT_PIN, DHT_TYPE); // Defines the sensor

void setup() {
  Serial.begin(9600); // Starts the serial communication
  Serial.println("\nBooting device...");

  dhtSensor.begin(); // Starts sensor communication
}

void loop() {
  static float humidity; // Variable that will store the last humidity value
  humidity = dhtSensor.readHumidity(); // Reads the humidity, it takes about 250
                                       // milliseconds

  Serial.println("Humidity: " + String(humidity) +" %"); // Prints in a new line the result

  delay(1000); // Freezes the loop for 1000 milliseconds
}
```

### Libraries
- [_DHT sensor library_](https://github.com/adafruit/DHT-sensor-library) by Adafruit - Installed from the Arduino IDE Library Management
  
  ![dht_library](../docs/dht_installation.png)

[[Go back]](/sensors/humidity)
