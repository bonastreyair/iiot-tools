#include <WiFi.h>  // Includes the WiFi library
#include <WebServer.h>  // Includes WebServer library

/* Put your SSID and Password */
const char *WIFI_SSID = "YOUR_SSID_NAME";
const char *WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

WebServer server(80);  // Creates server on standard port 80

void setup() {
  Serial.begin(9600); // Starts the serial communication

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
    Serial.println("No arguments\n");
  }
}

void connectToWiFiNetwork() {
  Serial.print("Connecting with Wi-Fi: " + String(WIFI_SSID));  // Print the network which you want to connect
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print("..");  // Connecting effect
  }
  Serial.print("..connected! (ip: ");  // After being connected to a network, our ESP32 should have a IP
  Serial.println(WiFi.localIP());
}

void checkWiFiConnection() {
  if (WiFi.status() != WL_CONNECTED) {  // Check WiFi connection
    Serial.println("Connection has been lost with Wi-Fi");
    connectToWiFiNetwork();  // Reconnect WiFi
  }
}