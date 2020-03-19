
# Industrial Internet of Things Tools
This repository tries to keep order on many _Industrial Internet of Things (IIoT)_ code examples using Arduino IDE as the main software development and the ESP32 as the hardware device. Also there are some examples using Node-RED as a way to show full integration with a gateway and its communications.

## Code examples
Each of the referenced examples will consist of a simple `code` in Arduino IDE format `.ino` that will try to auto-explain the way you can reuse the code in other and more complex projects. Sensors and outputs will also contain information about the `datasheet` and its `connection scheme` to the ESP32.

* [basic](/basic)
* [sensors](/sensors)
  * [button](/sensors/button)
  * [temperature analog](/sensors/temperature_analog)
  * [temperature digital](/sensors/temperature_digital)
  * [humidity digital](/sensors/humidity_digital)
  * [foto-resistor](/sensors/foto-resistor)
  * [ultrasounds](/sensors/ultrasounds)
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
  * [websockets](/communications/websockets)
  * [mqtt](/communications/mqtt)
    * [publish](/communications/mqtt/publish)
    * [subscribe](/communications/mqtt/publish)
  * [bluetooth](/communications/bluetooth)
* [system](/system)
  * [low power](/system/low_power) (deep sleep)
  * [multi-tasks](/system/multi-tasks)

## Exercises
1. monitor room temperature
   1. http api integration
   1. mqtt integration
1. dashboard (visualize your data)
1. telegrambot (interact with your data)

### Tested on
* ESP32 - Heltec - [Info](https://heltec.org/project/wifi-lora-32/)
* Arduino IDE 1.8.12 - [Download](https://www.arduino.cc/en/main/software)
* Node-RED - [Getting started](https://nodered.org/docs/getting-started/)

### Mantained by
[@bonastreyair](https://github.com/bonastreyair)
[@Ferrancf5](https://github.com/Ferrancf5)
[@Eugenill](https://github.com/Eugenill)
