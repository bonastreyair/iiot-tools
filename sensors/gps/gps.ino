#include <HardwareSerial.h>
#include <TinyGPS++.h>

#define RX_PIN 16 // Pinout RX of ESP32
#define TX_PIN 17 // Pinout TX of ESP32
#define REFRESH_RATE 5000 // Defined in miliseconds

HardwareSerial SerialGPS(1);

TinyGPSPlus gps;

void setup() {
  Serial.begin(9600); // Starts the serial communication
  Serial.println("\nBooting device...");
  
  SerialGPS.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN); // Starts gps communication with UART

  TimerHandle_t xTimer = xTimerCreate("printGpsReadings", REFRESH_RATE, pdTRUE, (void *) 0, printGpsReadings);
  xTimerStart(xTimer, 0);
}

void loop() {
  if (SerialGPS.available()) {
    gps.encode(SerialGPS.read()); // Encodes all messages from GPS
  }
}

void printGpsReadings(TimerHandle_t xTimer){
  Serial.print("LAT=");   Serial.println(gps.location.lat(), 6); // Latitude in degrees (double)
  Serial.print("LONG=");  Serial.println(gps.location.lng(), 6); // Longitude in degrees (double)
  Serial.print("ALT=");   Serial.println(gps.altitude.meters());  // Altitude in meters (double)
  Serial.print("SATS=");  Serial.println(gps.satellites.value()); // Number of satellites in use (u32)
  Serial.print("YEAR=");  Serial.println(gps.date.year()); // Year (2000+) (u16)
  Serial.print("MONTH="); Serial.println(gps.date.month()); // Month (1-12) (u8)
  Serial.print("DAY=");   Serial.println(gps.date.day()); // Day (1-31) (u8)
  Serial.print("HOUR=");  Serial.println(gps.time.hour()); // Hour (0-23) (u8)
  Serial.print("MIN=");   Serial.println(gps.time.minute()); // Minute (0-59) (u8)
  Serial.print("SEC=");   Serial.println(gps.time.second()); // Second (0-59) (u8)
}

/* More GPS functions examples */
//  Serial.println(gps.location.lat(), 6); // Latitude in degrees (double)
//  Serial.println(gps.location.lng(), 6); // Longitude in degrees (double)
//  Serial.print(gps.location.rawLat().negative ? "-" : "+");
//  Serial.println(gps.location.rawLat().deg); // Raw latitude in whole degrees
//  Serial.println(gps.location.rawLat().billionths);// ... and billionths (u16/u32)
//  Serial.print(gps.location.rawLng().negative ? "-" : "+");
//  Serial.println(gps.location.rawLng().deg); // Raw longitude in whole degrees
//  Serial.println(gps.location.rawLng().billionths);// ... and billionths (u16/u32)
//  Serial.println(gps.date.value()); // Raw date in DDMMYY format (u32)
//  Serial.println(gps.date.year()); // Year (2000+) (u16)
//  Serial.println(gps.date.month()); // Month (1-12) (u8)
//  Serial.println(gps.date.day()); // Day (1-31) (u8)
//  Serial.println(gps.time.value()); // Raw time in HHMMSSCC format (u32)
//  Serial.println(gps.time.hour()); // Hour (0-23) (u8)
//  Serial.println(gps.time.minute()); // Minute (0-59) (u8)
//  Serial.println(gps.time.second()); // Second (0-59) (u8)
//  Serial.println(gps.time.centisecond()); // 100ths of a second (0-99) (u8)
//  Serial.println(gps.speed.value()); // Raw speed in 100ths of a knot (i32)
//  Serial.println(gps.speed.knots()); // Speed in knots (double)
//  Serial.println(gps.speed.mph()); // Speed in miles per hour (double)
//  Serial.println(gps.speed.mps()); // Speed in meters per second (double)
//  Serial.println(gps.speed.kmph()); // Speed in kilometers per hour (double)
//  Serial.println(gps.course.value()); // Raw course in 100ths of a degree (i32)
//  Serial.println(gps.course.deg()); // Course in degrees (double)
//  Serial.println(gps.altitude.value()); // Raw altitude in centimeters (i32)
//  Serial.println(gps.altitude.meters()); // Altitude in meters (double)
//  Serial.println(gps.altitude.miles()); // Altitude in miles (double)
//  Serial.println(gps.altitude.kilometers()); // Altitude in kilometers (double)
//  Serial.println(gps.altitude.feet()); // Altitude in feet (double)
//  Serial.println(gps.satellites.value()); // Number of satellites in use (u32)
//  Serial.println(gps.hdop.value()); // Horizontal Dim. of Precision (100ths-i32)
