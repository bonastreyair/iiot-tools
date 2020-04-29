# Sensors
## GPS - Complex
This example uses a library to translate the GPS protocol for easy implementation.

[[Go back]](/sensors/gps)

### Hardware
- ESP32
- [GPS](../docs/gep-neo-6.pdf) - [terraelectronica Source](https://www.terraelectronica.ru/pdf/show?pdf_file=%2Fz%2FDatasheet%2FU%2FUART+GPS+NEO-6M+User+Manual.pdf)

### [Code](complex.ino)
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
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;

  // Trying read new message for one second
  for (unsigned long start = millis(); millis() - start < 1000;) {
    while (Serialgps.available()) {
      char data;
      data = Serialgps.read();
      if (gps.encode(data)) { // New message received
        newData = true;
      }
    }
  }

  if (newData) {
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    Serial.print("LAT=");
    Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    Serial.print(" LON=");
    Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    Serial.print(" SAT=");
    Serial.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
    Serial.print(" PREC=");
    Serial.print(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());
  }

  gps.stats(&chars, &sentences, &failed);
  Serial.print(" CHARS=");
  Serial.print(chars);
  Serial.print(" SENTENCES=");
  Serial.print(sentences);
  Serial.print(" CSUM ERR=");
  Serial.println(failed);
}
```

### Libraries
- [_SoftwareSerial_](https://github.com/plerup/espsoftwareserial/) by Peter Lerup and Dirk Kaar - Installed from GitHub

  ![SoftwareSerial_library](../docs/SoftwareSerial_library.png)

- [_TinyGPS_](https://github.com/neosarchizo/TinyGPS) by Mikal Hart - Installed from GitHub

   ![TinyGPS_library](../docs/TinyGPS_library.png)

### Connection
![Connection gps image](../docs/gps-neo-6.png)

[[Go back]](/sensors/gps)
