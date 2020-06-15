/*
   Based on Neil Kolban example for IDF:
   https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleScan.cpp
   Ported to Arduino ESP32 by Evandro Copercini
*/

#include <BLEAdvertisedDevice.h>
#include <BLEDevice.h>
#include <BLEScan.h>
#include <BLEUtils.h>

int scanTime = 5; // In seconds
BLEScan *pBLEScan;

// We are setting a class named MyAdvertisedDeviceCallbacks
class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    Serial.printf("Advertised Device: %s \n",
                  advertisedDevice.toString().c_str());
    // As we are scanning, we will find new devices. When found, this call back
    // is invoked with a reference to the device that was found. During any
    // individual scan, a device will only be detected one time. And when
    // calledthis class we will be printing the Advertised Device, every time is
    // called.
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("Scanning...");

  // NOW WE SET THE SCAN PARAMETERS
  BLEDevice::init("");             // we initiate the BLEDevice class object
  pBLEScan = BLEDevice::getScan(); // returning the scan object in pBLEScan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); // uses more power, but get results faster
  pBLEScan->setInterval(100);    // Scan interval
  pBLEScan->setWindow(99);       // Scan window.
  // The duration of the LE scan shall be <= LE_Scan_Interval
}

void loop() {
  // put your main code here, to run repeatedly
  BLEScanResults foundDevices =
      pBLEScan->start(scanTime, false); // contains all the devices found
  Serial.print("Devices found: ");
  Serial.println(foundDevices.getCount());
  Serial.println("Scan done!");
  pBLEScan->clearResults(); // release memory
  delay(2000);
}
