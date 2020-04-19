# Industrial Internet of Things Tools
This repository tries to keep order on many _Industrial Internet of Things (IIoT)_ code examples using Arduino IDE as the main software development and the ESP32 as the hardware device. Also there are some examples using Node-RED as a way to show full integration with a gateway and its communications.

## Code examples
Each of the referenced examples will consist of a simple `code` in Arduino IDE format `.ino` that will try to auto-explain the way you can reuse the code in other and more complex projects. Sensors and outputs will also contain information about the `datasheet` and its `connection scheme` to the ESP32.

* [sensors](/sensors)
  * [button](/sensors/button)
  * [temperature digital](/sensors/temperature_digital)
  * [humidity digital](/sensors/humidity_digital)
  * [ultrasounds](/sensors/ultrasounds)
  * [foto-resistor](/sensors/foto-resistor)
  * [temperature analog](/sensors/temperature_analog)
  * [electricity current](/sensors/electricity_current)
  * [gps](/sensors/gps)
* [outputs](/outputs)
  * [led light](/outputs/led_light)
  * [oled screen](/outputs/oled_screen)
* [communications](/communications)
  * [wifi](/communications/wifi)
    * [basic](/communications/wifi/basic)
    * [access point](/communications/wifi/access_point) (AP)
    * [http server](/communications/wifi/http_server)
  * [mqtt](/communications/mqtt)
    * [publish](/communications/mqtt/publish)
    * [subscribe](/communications/mqtt/publish)
  * [bluetooth](/communications/bluetooth)
* [system](/system)
  * [basic](/system/basic)
  * [low power](/system/low_power) (deep sleep)
  * [multi-tasks](/system/multi-tasks)

## Exercises
1. monitor room temperature
   1. http api integration
   1. mqtt integration
1. dashboard (visualize your data)
1. telegrambot (interact with your data)

### Tested Hardware
* ESP32 Dev Kit V1 - [Info](https://docs.zerynth.com/latest/official/board.zerynth.doit_esp32/docs/index.html)
* Heltec V2 (ESP32) - [Info](https://heltec.org/project/wifi-lora-32/)

### Software
* Arduino IDE 1.8.12 - [Download](https://www.arduino.cc/en/main/software)
* Node-RED 1.0.5 - [Getting started](https://nodered.org/docs/getting-started/)

### Contributors
* [@bonastreyair](https://github.com/bonastreyair)
* [@Ferrancf5](https://github.com/Ferrancf5)
* [@Eugenill](https://github.com/Eugenill)
