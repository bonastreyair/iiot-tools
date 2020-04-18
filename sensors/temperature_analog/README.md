# Sensors
## Temperature (Analog)
Using the TMP36 or the DS18B20 sensors we can measure the air temperature.

[[Go back]](/sensors)

### Hardware
* ESP32
* [TMP36](docs/datasheet_tmp36.pdf) - [Analog Source](https://www.analog.com/media/en/technical-documentation/data-sheets/TMP35_36_37.pdf)
* [DS18B20](docs/datasheet_ds18b20.pdf) - [SparkFun Source](https://cdn.sparkfun.com/datasheets/Sensors/Temp/DS18B20.pdf)

### [TMP36](TMP36/TMP36.ino)
```cpp
#define TMPPIN 32

void setup() {
  Serial.begin(9600);
}

void loop() {  
  int reading = analogRead(TMPPIN);
  //Serial.print("Reading: ");
  //Serial.println(reading);
  float voltage = reading * 3.3;
  voltage /= 4095.0;
  float temp_TMP36 = (voltage * 50);
  
  Serial.print("Temperatura_TMP36: ");
  Serial.println(temp_TMP36);
}
```

### [DS18B20](DS18B20/DS18B20.ino)
```cpp
#include <DallasTemperature.h>
#include <OneWire.h>


#define DS18B20PIN 5

OneWire oneWire(DS18B20PIN);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  
  sensors.begin();  
 }


void loop() {
    sensors.requestTemperatures(); 
  float temp_DS18B = sensors.getTempCByIndex(0);
  //float temperatureF = sensors.getTempFByIndex(0);
  if (isnan(temp_DS18B)) {
    Serial.println("Fallo en Lectura Sensor DS18B20");
  }
  else {
    Serial.print("Temperatura_DS18B20: ");
    Serial.println(temp_DS18B);    
  }
}

```

### Libraries
* _DS18B26 sensor library_ by Miles Burton [GitHub](https://github.com/milesburton/Arduino-Temperature-Control-Library) - Installed from the Arduino IDE Library Management
![dht_library](docs/DS18B20_library.png)
* _OneWire library_ by PaulStoffregen [Github](https://github.com/PaulStoffregen/OneWire) - Installed from the Arduino IDe Library Management
![OneWire_library](docs/OneWire_library.png)

### Connection 