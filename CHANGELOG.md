# Changelog
All notable changes to this project will be documented in this file.

## [Unreleased]
### Added
- Code Examples
  - MQTT
    - publishing
    - subscribing
  - WiFi
    - Basic connection
    - Acces Point
    - HTTP Server
  - Bluetooth
    - Scanner
    - Server
    - Client
  - Temperature
    - DHT (digital sensor)
    - DS18B20 (digital sensor)
    - TMP36 (analog sensor)
  - Humidity
    - DHT (digital sensor)
  - Button
  - Current (eletricity) sensor
    - PZEM004Tv30
    - SCT01330
  - Foto Resistor
  - GPS
  - Ultrasounds
  - LED Light
  - OLED Screen
  - Low Power
  - Multi Task
- Proposed exercises
- Datasheets for the sensors

### Changed
- `README` file list of available code
- Styled all `C++` codes as Standard

### Removed 
- `websockets` from the main list
- References to `Digital` and `Analogical` in `Temperature` and `Humidity`
- GPS simple and left only the one that uses `TinyGPS` library

## [0.1.0] - 2020-03-19
### Added
- CHANGELOG.md file
- README.md file
- Main folder structure with standard README.md to force the creation of folders

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/)