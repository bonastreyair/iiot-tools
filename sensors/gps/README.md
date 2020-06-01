# Sensors
## GPS
This example uses TinyGPS library to translate the GPS [NMEA protocol](https://www.gpsinformation.org/dale/nmea.htm#GGA) for easy implementation.
 
[[Go back]](/sensors)

### Hardware
- ESP32
- [GPS](docs/gep-neo-6.pdf) - [terraelectronica Source](https://www.terraelectronica.ru/pdf/show?pdf_file=%2Fz%2FDatasheet%2FU%2FUART+GPS+NEO-6M+User+Manual.pdf)

### [Code](gps.ino)
```cpp
#include <SoftwareSerial.h>
#include <TinyGPS.h>

#define RX_PIN 4  // Pinout Rx of ESP32
#define TX_PIN 3  // Pinout Tx of ESP32

TinyGPS gps;
SoftwareSerial Serialgps(RX_PIN, TX_PIN);

void setup() {
  Serial.begin(9600);
  Serial.println("\nBooting device...");
  Serialgps.begin(9600);  // Starts gps communication with UART
}

void loop() {
  static float flatitude, flongitude;
  static unsigned long age;

  if (Serialgps.available()) {
    char data = Serialgps.read();
    if (gps.encode(data)) {
      gps.f_get_position(&flatitude, &flongitude, &age);
      Serial.println("[I] - gps - lat: %.4f lon: %.4f age: %ums", flatitude, flongitude, age);
    } else {
      Serial.println("[E] - data could not be encoded");
    }
    delay(1000);
  } else {
    Serial.println('[E] - lost connection with serial gps');
    Serial.println('[W] - trying reconnection in 5 seconds...');
    delay(5000);
  }
}
```

### Libraries
- [_SoftwareSerial_](https://github.com/plerup/espsoftwareserial/) by Peter Lerup and Dirk Kaar - Installed from Arduino Library

  ![SoftwareSerial_library](docs/SoftwareSerial_library.png)

- [_TinyGPS_](https://github.com/neosarchizo/TinyGPS) by Mikal Hart - Installed from Arduino Library

  ![TinyGPS_library](docs/TinyGPS_library.png)

### Connection
![Connection gps image](docs/gps-neo-6.png)

[[Go back]](/sensors)
