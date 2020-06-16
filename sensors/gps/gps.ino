#include <SoftwareSerial.h>
#include <TinyGPS.h>

#define RX_PIN 4 // Pinout Rx of ESP32
#define TX_PIN 3 // Pinout Tx of ESP32

TinyGPS gps;
SoftwareSerial Serialgps(RX_PIN, TX_PIN);

void setup() {
  Serial.begin(9600);
  Serial.println("\nBooting device...");
  Serialgps.begin(9600); // Starts gps communication with UART
}

void loop() {
  static float flatitude, flongitude;
  static unsigned long age;

  if (Serialgps.available()) {
    char data = Serialgps.read();
    if (gps.encode(data)) {
      gps.f_get_position(&flatitude, &flongitude, &age);
      Serial.println("[I] - gps - lat: %.4f lon: %.4f age: %ums", flatitude,
                     flongitude, age);
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

void print_date(TinyGPS &gps) {
  int year;
  byte month, day, hour, minute, second, hundredths;
  unsigned long age;
  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
  if (age == TinyGPS::GPS_INVALID_AGE) {
    Serial.print("********** ******** ");
  } else {
    char gps_datetime[32];
    sprintf(gps_datetime, "%02d/%02d/%02d %02d:%02d:%02d ",
        day, month, year, hour, minute, second);
    Serial.print(gps_datetime);
  }
  print_int(age, TinyGPS::GPS_INVALID_AGE, 5);
  smartdelay(0);
}