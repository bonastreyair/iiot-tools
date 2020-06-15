#include <WiFi.h> // Includes the WiFi library

/* Put your desired SSID and Password */
const char *WIFI_SSID = "DESIRED_SSID_NAME";
const char *WIFI_PASSWORD = "DESIRED_WIFI_PASSWORD";

/* Setup Router details */
IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

void setup() {
  Serial.begin(9600); // Starts the serial communication
  Serial.println("\nBooting device...");

  WiFi.softAP(WIFI_SSID, WIFI_PASSWORD);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  Serial.println("ESP32 is now a router WiFi and it is now active");
}

void loop() {}