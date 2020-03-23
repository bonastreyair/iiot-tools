#include <WiFi.h> // Includes the WiFi library

/* Put your SSID and Password */
const char *WIFI_SSID = "YOUR_SSID_NAME";  // Enter SSID here
const char *PASSWORD = "YOUR_WIFI_PASSWORD";  // Enter Password here

/* Put IP Address details */
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

void setup() {
  Serial.begin(9600);
  
  WiFi.softAP(WIFI_SSID, PASSWORD);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  Serial.println("WiFi AP is now active");
}

void loop() {
}