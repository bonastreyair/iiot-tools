#include <WiFi.h> // Includes the WiFi library

/* Put your desired SSID and Password */
const char *WIFI_SSID = "YOUR_SSID_NAME";
const char *PASSWORD = "YOUR_WIFI_PASSWORD";

/* Put IP Address details */
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

void setup(){
  Serial.begin(9600);  // Starts the serial communication
  
  // Set desired AP configuration
  WiFi.softAP(WIFI_SSID, PASSWORD);
  WiFi.softAPConfig(local_ip, gateway, subnet);  
  Serial.println("WiFi AP is now active");
}

void loop(){
}