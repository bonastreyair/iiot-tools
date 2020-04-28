# Communications
## Wifi - HTTP Server
Code to create a HTTP server in your network enabling GET and PUT methods.

[[Go back]](/communications/wifi)

### Hardware
- ESP32
  
### [Code](http_server.ino)
```cpp
#include <WiFi.h>  // Includes the WiFi library
#include <WebServer.h>  // Includes WebServer library

/* Put your SSID and Password */
const char *WIFI_SSID = "YOUR_SSID_NAME";
const char *WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

WebServer server(80);  // Creates server on standard port 80

void setup() {
  Serial.begin(9600); // Starts the serial communication
  Serial.println("\nBooting device...");
  
  connectToWiFiNetwork();  // Connect the configured network

  // Define active server endpoints
  server.on("/", handle_OnConnect);
  server.on("/hello", handle_Hello);
  server.onNotFound(handle_NotFound);

  server.begin();  // Start the server
  Serial.println("HTTP Server has started");
}

void loop() {
  checkWiFiConnection();
  server.handleClient();  // If there is a new connection it handles it
}

/* Additional functions */
void handle_OnConnect() {
  server.send(200, "text/html", "Main page. Try to go to /hello endpoint");
  print_request_info();
}

void handle_Hello() {
  server.send(200, "text/html", "Hello-world!");
  print_request_info();
}

void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
  print_request_info();
}

void print_request_info() {
  String server_method = (server.method() == HTTP_GET) ? "GET" : "PUT";
  Serial.println("New " + server_method + " request to " + String(server.uri()));
  if (server.args()) {
    Serial.println("Arguments");
    String arguments = "";
    for (uint8_t i = 0; i < server.args(); i++) {
      arguments += " - " + server.argName(i) + ": " + server.arg(i) + "\n";
    }
    Serial.println(arguments);
  } else {
    Serial.println("No arguments");
  }
}

void connectToWiFiNetwork() {
  Serial.print("Connecting with Wi-Fi: " + String(WIFI_SSID));  // Print the network which you want to connect
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print("..");  // Connecting effect
  }
  Serial.print("..connected!  (ip: ");  // After being connected to a network, our ESP32 should have a IP
  Serial.print(WiFi.localIP());
  Serial.println(")");
}

void checkWiFiConnection() {
  if (WiFi.status() != WL_CONNECTED) {  // Check WiFi connection
    Serial.println("Connection has been lost with Wi-Fi");
    connectToWiFiNetwork();  // Reconnect WiFi
  }
}
```

### Libraries
- [_Wifi_](https://www.arduino.cc/en/Reference/WiFi) by Arduino - Installed from the Arduino IDE Library Management

  ![WiFi_library](../docs/WiFi_library.png)
 
  This library allows an Arduino board to connect to a wifi router. It can be used as either a server accepting incoming connections or as a client. Some of the functions we use are:
  - `WiFi.begin(WIFI_SSID, WIFI_PASSWORD)`: Initializes the WiFi library's network settings and provides the current status
  - `WiFi.status()`: Return the connection status
  - `WiFi.macAdress()`: Gets the MAC Address of your WiFi shield
  - `WiFi.localIP()`: Gets the WiFi shield's IP address

- [_WebServer_](https://www.arduino.cc/en/Tutorial/WebServer) by Arduino - Preinstalled with the Arduino IDE

  This library allows to create a simple web server that helps to serve an HTTP API. Some of the functions we user are:
  - `WebServer server(80)`: Creates the server on port 80
  - `server.on(endpoint, handle_function)`: Creates and `endpoint` that when activated it runs the `handle_function`
  - `server.send(code, format, payload)`: Sends standard http messages making usage of standard `code` and `format`
  - `server.handleClient()`: Handles any new client and needs to be called continuously to catch any new request

[[Go back]](/communications/wifi)