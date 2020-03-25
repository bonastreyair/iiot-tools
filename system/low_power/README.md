# System
## Low Power
This code gives a simple example to set deep sleep mode and enable a timer to start the ESP32.

### Hardware
* ESP32

### Code
* [low_power.ino](low_power.ino)

```cpp
#define SLEEP_TIME  5  // Time ESP32 will go into deep sleep (in seconds)

RTC_DATA_ATTR int bootCount = 0;  // Data that will be stored during deep sleep mode

void setup(){
  Serial.begin(9600);  // Starts the serial communication

  print_wakeup_reason();  // Print the wakeup reason for ESP32

  bootCount++;  // Increment boot number and prints it on every reboot
  Serial.println("Boot: " + String(bootCount));

  esp_sleep_enable_timer_wakeup(SLEEP_TIME * 1000000);  // Setup to wake up after 5 seconds, defined in microseconds

  // Turns off all RTC peripherals in deep sleep
  //esp_deep_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_OFF);  
  
  Serial.println("Going to sleep for " + String(SLEEP_TIME) + " seconds");
  Serial.flush();  // Clears all unsent serial information
  esp_deep_sleep_start();  // Set the ESP32 to deep sleep mode

  Serial.println("This will never be printed");
}

void loop(){
  // This is not going to be called
}

/* Additional functions */
void print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();
  
  Serial.println("");  // Add a new line to better show the information
  switch(wakeup_reason){
    case ESP_SLEEP_WAKEUP_UNDEFINED:
      Serial.println("Reset was not caused by an exit from deep sleep");
      bootCount = 0;  // Reset counter
      break;
    case ESP_SLEEP_WAKEUP_EXT0: 
      Serial.println("Wakeup caused by external signal using RTC_IO"); 
      break;
    case ESP_SLEEP_WAKEUP_EXT1: 
      Serial.println("Wakeup caused by external signal using RTC_CNTL"); 
      break;
    case ESP_SLEEP_WAKEUP_TIMER: 
      Serial.println("Wakeup caused by timer"); 
      break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD: 
      Serial.println("Wakeup caused by touchpad");
      break;
    case ESP_SLEEP_WAKEUP_ULP: 
      Serial.println("Wakeup caused by ULP program"); 
      break;
    case ESP_SLEEP_WAKEUP_GPIO:
      Serial.println("Wakeup caused by GPIO (light sleep only)");
      break;
    case ESP_SLEEP_WAKEUP_UART:
      Serial.println("Wakeup caused by UART (light sleep only)");
      break;
  }
}
```

### Libraries
* Standard ESP32 Library - [Sleep Modes](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/sleep_modes.html)