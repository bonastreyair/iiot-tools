# Communications
## Wifi - Access Point
Code to enable and ESP32 to create its own WiFi network (Access Point - AP) and act as a hub (like WiFi router) for one or more stations. The maximum number of stations that can connect to it is limited to five.

[[Go back]](/communications/wifi)

### Hardware
- ESP32
	
### [Code](access_point.ino)
```cpp
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

```

### Libraries
- [_Wifi_](https://www.arduino.cc/en/Reference/WiFi) by Arduino - Installed from the Arduino IDE Library Management

  ![WiFi_library](../docs/WiFi_library.png)
 
  This library allows an Arduino board to connect to a wifi router. It can be used as either a server accepting incoming connections or as a client. Some of the functions we use are:
  - `WiFi.softAP(WIFI_SSID, WIFI_PASSWORD)`: Initializes the WiFi `SSID` name and `PASSWORD` to become a router
  - `WiFi.softAPConfig(local_ip, gateway, subnet)`: Sets up the main configuration of the router 

[[Go back]](/communications/wifi)
