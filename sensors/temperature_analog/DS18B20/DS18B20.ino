#include <DallasTemperature.h>
#include <OneWire.h>


#define DS18B20PIN 5

OneWire oneWire(DS18B20PIN);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  
  sensors.begin();  
 }


void loop() {
    sensors.requestTemperatures(); 
  float temp_DS18B = sensors.getTempCByIndex(0);
  //float temperatureF = sensors.getTempFByIndex(0);
  if (isnan(temp_DS18B)) {
    Serial.println("Fallo en Lectura Sensor DS18B20");
  }
  else {
    Serial.print("Temperatura_DS18B20: ");
    Serial.println(temp_DS18B);    
  }
}
