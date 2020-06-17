#include <WiFi.h> // Includes the WiFi library
#include <AsyncTCP.h> // Include TCP Library
#include <ESPAsyncWebServer.h> // Include WebServer Library
#include <DNSServer.h> // Includes DNS Library
#include "SPIFFS.h" // Includes SPIFileSystem (install https://github.com/me-no-dev/arduino-esp32fs-plugin)

#define LED_PIN 2

/* Put your desired SSID and Password */
const char *WIFI_SSID = "ESP32_WebServer";
const char *WIFI_PASSWORD = "12345678";
const byte DNS_PORT = 53;

/* Setup Access Point details */
IPAddress apIP(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
AsyncWebServer server(80);   // Creates a WebServer on port 80
DNSServer dnsServer;

const char* PARAM_INPUT = "state";

// Replaces placeholder with button section in your web page
String processor(const String& var){
  if (var == "STATE") {
    String state = outputState(LED_PIN);
    return state;
  } else if (var == "PIN") {
    String pin = String(LED_PIN);
    return pin;
  }
  return String();
}

String outputState(int output){
  if (digitalRead(output)) {
    return "checked";
  } else {
    return "";
  }
}

void setup(){
  Serial.begin(9600); // Starts the serial communication
  Serial.println("\nBooting device...");
  SPIFFS.begin(); // Start file system

  pinMode(LED_PIN, OUTPUT);

  startAP();
  startWebServer();
}

void loop() {
  dnsServer.processNextRequest();
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
  server.on("/", HTTP_GET, startWeb);
  server.on("/command", HTTP_GET, commandLED);
  server.onNotFound(notFound);
  server.begin();
}

void startWeb(AsyncWebServerRequest *request) {
  request->send(SPIFFS, "/index.html", String(), false, processor);
}

// Send a GET request to <ESP_IP>/command?state=<stateMessage>
void commandLED(AsyncWebServerRequest *request) {
  String stateMessage;
  if (request->hasParam(PARAM_INPUT)) {
    stateMessage = request->getParam(PARAM_INPUT)->value();
    digitalWrite(LED_PIN, stateMessage.toInt());
    Serial.println("GPIO: "+ String(LED_PIN) + " - Set to: " + (stateMessage.toInt() ? "on" : "off"));
  } else {
    Serial.println("No message sent");
  }
  request->send(200, "text/plain", "OK");
}

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}
