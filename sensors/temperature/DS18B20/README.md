# Sensors
## Temperature - DS18B20
Using the DS18B20 digital sensor we can measure the air temperature.

[[Go back]](/sensors/temperature)

### Hardware
- ESP32
- [DS18B20](../docs/datasheet_ds18b20.pdf) - [SparkFun Source](https://cdn.sparkfun.com/datasheets/Sensors/Temp/DS18B20.pdf)

### [Code](DS18B20.ino)
```cpp
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
```

### Libraries
- [_DS18B26 sensor library_](https://github.com/milesburton/Arduino-Temperature-Control-Library) by Miles Burton - Installed from the Arduino IDE Library Management
  
  ![dht_library](../docs/DS18B20_library.png)

- [_OneWire library_](https://github.com/PaulStoffregen/OneWire) by PaulStoffregen - Installed from the Arduino IDE Library Management

  ![OneWire_library](../docs/OneWire_library.png)

[[Go back]](/sensors/temperature)
