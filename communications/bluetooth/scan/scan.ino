/*
   Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleScan.cpp
   Ported to Arduino ESP32 by Evandro Copercini
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

int scanTime = 5; //Set the number of seconds for every scan
BLEScan* pBLEScan; //define a BLEScan class object as pBLEScan from BLEScan.h

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks { //We are setting a class named MyAdvertisedDeviceCallbacks 
                                                                         //as a BLEAdvertisedDeviceCallbacks class BLEAdvertisedDevice.h 
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());
      //As we are scanning, we will find new devices.  When found, this call back is invoked with a reference to the
      //device that was found.  During any individual scan, a device will only be detected one time.
      //And when called this class we will be printing the Advertised Device, every time is called.
    }
};

void setup() {
  Serial.begin(115200);
  Serial.println("Scanning...");
  
  //NOW WE SET THE SCAN PARAMETERS
  
  BLEDevice::init(""); //we initiate the BLEDevice class object
  pBLEScan = BLEDevice::getScan(); //asking the BLEDevice for scanning, with the getScan() function, 
                                    //we are returning the scan object and saving it in pBLEScan
  (*pBLEScan).setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks()); //when a Device is found we will 
                                                                       //call the class function above (MyAdvertisedDeviceCallbacks())
  (*pBLEScan).setActiveScan(true); //active scan uses more power, but get results faster
  (*pBLEScan).setInterval(100); //Scan interval. This is defined as the time interval from when the 
                              //Controller started its last LE scan until it begins the subsequent LE scan. 
  (*pBLEScan).setWindow(99);  // Scan window. The duration of the LE scan. LE_Scan_Window shall be less than 
                            //or equal to LE_Scan_Interval
}

void loop() {
  // put your main code here, to run repeatedly:
  BLEScanResults foundDevices = (*pBLEScan).start(scanTime, false);//as a return we get a BLEScanResults class object 
                                                                  //which contains all the devices found
  Serial.print("Devices found: ");
  Serial.println(foundDevices.getCount());//counting the number of devices found between this 5 seconds, by calling getCount()
  Serial.println("Scan done!");
  (*pBLEScan).clearResults();   // delete results fromBLEScan buffer to release memory
  delay(2000);
}
