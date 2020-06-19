#include <WiFi.h>      // Includes the WiFi library
#include <DNSServer.h> // Includes DNS library

/* Put your desired SSID and Password */
const char *WIFI_SSID = "DESIRED_SSID_NAME";
const char *WIFI_PASSWORD = "DESIRED_WIFI_PASSWORD";
const byte DNS_PORT = 53;

/* Setup Router details */
IPAddress apIP(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
DNSServer dnsServer;

void setup() {
  Serial.begin(9600); // Starts the serial communication
  Serial.println("\nBooting device...");

  WiFi.mode(WIFI_AP);
  WiFi.softAP(WIFI_SSID, WIFI_PASSWORD);
  delay(100);
  WiFi.softAPConfig(apIP, apIP, subnet);

  dnsServer.start(DNS_PORT, "www.esp32_cim_project.com", apIP);

  Serial.println("ESP32 is now a router WiFi and it is now active");
}

void loop() {
  dnsServer.processNextRequest();
}
