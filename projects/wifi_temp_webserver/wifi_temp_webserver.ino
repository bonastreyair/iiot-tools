#include <WiFi.h> // Includes the WiFi library
#include "DHT.h" // Include DHT library
#include <AsyncTCP.h> // Include TCP Library
#include <ESPAsyncWebServer.h> // Include WebServer Library
#include <DNSServer.h> // Includes DNS Library

#include "index.h" // Loads webpage

#define DHT_PIN 4 // Defines pin number to which the sensor is connected
#define DHT_TYPE DHT22 // Defines the sensor type. It can be DHT11 or DHT22

/* Put your desired SSID and Password */
const char *WIFI_SSID = "ESP32_WebServer";
const char *WIFI_PASSWORD = "12345678";
const byte DNS_PORT = 53;

/* Setup Access Point details */
IPAddress apIP(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
AsyncWebServer server(80);   // Creates a WebServer on port 80
DNSServer dnsServer;

DHT dhtSensor(DHT_PIN, DHT_TYPE); // Defines the sensor dht
float temperature; // Global variable

void setup() {
  Serial.begin(9600); // Starts the serial communication
  Serial.println("\nBooting device...");
  
  startAP(); // Starts Access Point
  startWebServer(); // Starts WebServer

  dhtSensor.begin(); // Starts sensor communication

  TimerHandle_t xTimer = xTimerCreate("updateTemperature", 2000, pdTRUE, (void *) 0, updateTemperature);
  xTimerStart(xTimer, 0);
}

void loop() {
  dnsServer.processNextRequest();
}

void updateTemperature(TimerHandle_t xTimer) {
  float t = dhtSensor.readTemperature(); // Updates temperature in every second
  if(!isnan(t)){
    temperature = t; // Updates the value to global variable
    Serial.println("Updated temperature: " + String(temperature) + "°C"); // Prints in a new line the result
  } else {
    Serial.println("Sensor had a bad reading");
  }
}

void startAP() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP(WIFI_SSID, WIFI_PASSWORD);
  delay(100);
  WiFi.softAPConfig(apIP, apIP, subnet);
  Serial.println("ESP32 is now an access point WiFi and it is now active");
}

void startWebServer() {
  dnsServer.start(DNS_PORT, "www.esp32_cim_project.com", apIP);
  server.on("/", HTTP_GET, helloWorld);
  server.on("/temperature", HTTP_GET, serveIndex);
  server.onNotFound(notFound);
  server.begin();
}

void helloWorld(AsyncWebServerRequest *request) {
  request->send(200, "text/plain", "Hello World!\n\nwww.esp32_cim_project.com/temperature");
}

void serveIndex(AsyncWebServerRequest *request) {
  Serial.println("Client made a GET to 192.168.1.1 to read the latest temperature");
  request->send_P(200, "text/html", indexHTML, processor);
}

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

// Replaces placeholder in HTML with temperature value
String processor(const String& var) {
  if (var == "TEMPERATURE") {
    return String(temperature);
  }
  return String();
}
