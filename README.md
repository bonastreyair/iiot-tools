# Industrial Internet of Things Tools
This repository tries to keep order on many _Industrial Internet of Things (IIoT)_ code examples using Arduino IDE as the main software development and the ESP32 as the hardware device. Also there are some examples using Node-RED as a way to show full integration with a gateway and its communications.

Each of the referenced examples will consist of a simple `code` in Arduino IDE format `.ino` that will try to auto-explain the way you can reuse the code in other and more complex projects. Sensors and outputs will also contain information about the `datasheet` and its `connection scheme` to the ESP32.

All the examples are ordered in the following groups. Navigate through them and try them all!

| | | | | |
|-|-|-|-|-|
|[**Sensors**](#sensors) |[**Outputs**](#outputs) |[**Communications**](#communications) |[**System**](#system) |[**Projects**](#projects)|
| | | | | |

## [Sensors](/sensors)
### [Temperature](/sensors/temperature)
| | Description | Code | Docs |
|-|:------------|:----:|:----:|
|[DHT](/sensors/temperature/DHT) |How to integrate a digital `DHT` temperature sensor? |[:white_check_mark:](/sensors/temperature/DHT/DHT.ino)|[:white_check_mark:](/sensors/temperature/README.md)|
|[DS18B20](/sensors/temperature/DS18B20) |How to integrate a digital `DS18B20` temperature sensor? |[:white_check_mark:](/sensors/temperature/DS18B20/DS18B20.ino)|[:white_check_mark:](/sensors/temperature/README.md)|
|[TMP36](/sensors/temperature/TMP36) |How to integrate a analog `TMP36` temperature sensor? |[:white_check_mark:](/sensors/temperature/TMP36/TMP36.ino)|[:white_check_mark:](/sensors/temperature/README.md)|

### [Electricity Current](/sensors/electricity_current)
| | Description | Code | Docs |
|-|:------------|:----:|:----:|
|[PZEM004Tv30](/sensors/electricity_current/PZEM004Tv30) |How to integrate a `PZEM004Tv30` electricity current sensor? |[:white_check_mark:](/sensors/electricity_current/PZEM004Tv30/PZEM004Tv30.ino)|[:white_check_mark:](/sensors/electricity_current/README.md)|
|[SCT-013-30](/sensors/electricity_current/SCT-013-30) |How to integrate a `SCT-013-30` electricity current sensor? |[:white_check_mark:](/sensors/electricity_current/SCT-013-30/SCT-013-30.ino)|[:white_check_mark:](/sensors/electricity_current/README.md)|

### Others
| | Description | Code | Docs |
|-|:------------|:----:|:----:|
|[Button](/sensors/button) |How to integrate a button? |[:white_check_mark:](/sensors/button/button.ino)|[:white_check_mark:](/sensors/button/README.md)|
|[Ultrasounds](/sensors/ultrasounds) |How to integrate an ultrasounds sensor? |[:white_check_mark:](/sensors/ultrasounds/ultrasounds.ino)|[:white_check_mark:](/sensors/ultrasounds/README.md)|
|[Foto Resistor](/sensors/foto-resistor) |How to integrate an analog foto resistor sensor? |[:white_check_mark:](/sensors/foto-resistor/foto-resistor.ino)|[:white_check_mark:](/sensors/foto-resistor/README.md)|
|[Humidity - DHT](/sensors/humidity/DHT) |How to integrate a digital `DHT` humidity sensor? |[:white_check_mark:](/sensors/humidity/DHT/DHT.ino)|[:white_check_mark:](/sensors/humidity/README.md)|
|[GPS](/sensors/gps) |How to integrate a `GPS` sensor using `TinyGPS` library using `Serial` connection? |[:white_check_mark:](/sensors/gps/gps.ino)|[:white_check_mark:](/sensors/gps/README.md)|

[[Go to top]](#industrial-internet-of-things-tools)

## [Outputs](/outputs)
### [LED Light](/outputs/led_light)
| | Description | Code | Docs |
|-|:------------|:----:|:----:|
|[Basic](/outputs/led_light/basic) |How to integrate a basic `LED` light? |[:white_check_mark:](/outputs/led_light/basic/basic.ino)|[:white_check_mark:](/outputs/led_light/basic/README.md)|
|[RGB](/outputs/led_light/RGB) |How to integrate an  `RGB LED` light? |[:white_check_mark:](/outputs/led_light/RGB/RGB.ino)|[:white_check_mark:](/outputs/led_light/RGB/README.md)|

### [OLED Screen](/output/oled_screen)
| | Description | Code | Docs |
|-|:------------|:----:|:----:|
|[SDD1306](/outputs/oled_screen/SDD1306) |How to integrate a  `OLED` Screen using `SDD1306` library? |[:white_check_mark:](/outputs/oled_screen/SDD1306/SDD1306.ino)|[:white_check_mark:](/outputs/oled_screen/SDD1306/README.md)|
|[U8g2](/outputs/oled_screen/U8g2) |How to integrate an `OLED` Screen using `U8g2` library? |[:white_check_mark:](/outputs/oled_screen/U8g2/U8g2.ino)|[:white_check_mark:](/outputs/oled_screen/U8g2/README.md)|

[[Go to top]](#industrial-internet-of-things-tools)

## [Communications](/communications)
### [Wifi](/communications/wifi)
| | Description | Code | Docs |
|-|:------------|:----:|:----:|
|[Basic](/communications/wifi/basic) |How to connect to a `WiFi` router as a client and scan the `WiFi` area? |[:white_check_mark:](/communications/wifi/basic/basic.ino)|[:white_check_mark:](/communications/wifi/basic/README.md)|
|[Acces Point](/communications/wifi/access_point) |How to create a `WiFi` Acces Point? |[:white_check_mark:](/communications/wifi/access_point/access_point.ino)|[:white_check_mark:](/communications/wifi/access_point/README.md)| 
|[HTTP Server](/communications/wifi/http_server) |How to create a simple `HTTP` Webserver? |[:white_check_mark:](/communications/wifi/http_server/http_server.ino)|[:white_check_mark:](/communications/wifi/http_server/README.md)| 

### [MQTT](/communications/mqtt)
| | Description | Code | Docs |
|-|:------------|:----:|:----:|
|[Publish](/communications/mqtt/publish) |How publish a string or a json using `MQTT` protocols over `WiFi`? |[:white_check_mark:](/communications/mqtt/publish/publish.ino)|[:white_check_mark:](/communications/mqtt/publish/README.md)| 
|[Subscribe](/communications/mqtt/subscribe) |How subscribe to a topic and recieve information from a `MQTT Broker` over `WiFi`? |[:white_check_mark:](/communications/mqtt/subscribe/subscribe.ino)|[:white_check_mark:](/communications/mqtt/subscribe/README.md)| 

### [Bluetooth](/communications/bluetooth)
| | Description | Code | Docs |
|-|:------------|:----:|:----:|
|[Scanner](/communications/bluetooth/scan) |How to scan the bluetooth space area? |[:white_check_mark:](/communications/bluetooth/scan/scan.ino)|[:white_check_mark:](/communications/bluetooth/README.md)|
|[Server](/communications/bluetooth/server) |How to build a bluetooth server? |[:white_check_mark:](/communications/bluetooth/server/server.ino)|[:white_check_mark:](/communications/bluetooth/README.md)|
|[Client](/communications/bluetooth/client) |How to connect to a bluetooth as a client? |[:white_check_mark:](/communications/bluetooth/client/client.ino)|[:white_check_mark:](/communications/bluetooth/README.md)|

[[Go to top]](#industrial-internet-of-things-tools)

## [System](/system)
| | Description | Code | Docs |
|-|:------------|:----:|:----:|
|[Basic](/system/basic) |Some basic examples to understand how `C++` works using `Arduino IDE` |[:x:](/system/basic/basic.ino)|[:x:](/system/basic/README.md)|
|[Low Power](/system/low_power) |Some basic examples to understand how ESP32 works in deep sleep mode |[:white_check_mark:](/system/low_power/low_power.ino)|[:white_check_mark:](/system/low_power/README.md)|
|[Multi Tasks](/system/multi-tasks) |Some basic examples how to use more than one simultaneous task |[:white_check_mark:](/system/multi-tasks/multi-tasks.ino)|[:white_check_mark:](/system/multi-tasks/README.md)|

[[Go to top]](#industrial-internet-of-things-tools)

## Projects
| | Description | Dependancies | Difficulty |
|-|:------------|:------------:|:----------:|

[[Go to top]](#industrial-internet-of-things-tools)

## Tested Hardware
- ESP32 Dev Kit V1 - [Info](https://docs.zerynth.com/latest/official/board.zerynth.doit_esp32/docs/index.html)
- Heltec V2 (ESP32) - [Info](https://heltec.org/project/wifi-lora-32/)

## Software
- Arduino IDE 1.8.12 - [Download](https://www.arduino.cc/en/main/software)
- Node-RED 1.0.6 - [Getting started](https://nodered.org/docs/getting-started/)

## Contributors
- [@bonastreyair](https://github.com/bonastreyair)
- [@Ferrancf5](https://github.com/Ferrancf5)
- [@Eugenill](https://github.com/Eugenill)
