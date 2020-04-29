# Sensors
## GPS - Simple 
More difficult to understand because this type of GPS use NMEA protocol communication.

[[Go back]](/sensors/gps)

### Hardware
- ESP32
- [GPS](../docs/gep-neo-6.pdf) - [terraelectronica Source](https://www.terraelectronica.ru/pdf/show?pdf_file=%2Fz%2FDatasheet%2FU%2FUART+GPS+NEO-6M+User+Manual.pdf)

### [Code](simple.ino)
```cpp
#include <SoftwareSerial.h>

#define RX_PIN 4  // Pinout Rx of ESP32
#define TX_PIN 3  // Pinout Tx of ESP32

SoftwareSerial Serialgps(RX_PIN, TX_PIN);

void setup() {
  Serial.begin(9600);
  Serial.println("\nBooting device...");
  Serialgps.begin(9600);  // Starts gps communication with UART
}

void loop() {  // Trying read new message for one second
  for (unsigned long start = millis(); millis() - start < 1000;) {
    if (Serialgps.available()) {  // If there is a good signal
      char data;
      data = Serialgps.read();
      Serial.print(data);
    }
  }
}
```

### Libraries
- [_SoftwareSerial_](https://github.com/plerup/espsoftwareserial/) by Peter Lerup and Dirk Kaar - Installed from GitHub

  ![SoftwareSerial_library](../docs/SoftwareSerial_library.png)

### Connection
![Connection gps image](../docs/gps-neo-6.png)

[[Go back]](/sensors/gps)
