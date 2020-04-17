# Communications
## Bluetooth

What is Bluetooth Low Energy?
Bluetooth Low Energy, BLE for short, is a power-conserving variant of Bluetooth. BLE’s primary application is short distance transmission of small amounts of data (low bandwidth). Unlike Bluetooth that is always on, BLE remains in sleep mode constantly except for when a connection is initiated.
This makes it consume very low power. BLE consumes approximately 100x less power than Bluetooth (depending on the use case).

![BLEDevices](BLE-Intro.png)

With Bluetooth Low Energy, there are two types of devices: the server and the client. The ESP32 can act either as a client or as a server.
The server advertises its existence, so it can be found by other devices, and contains the data that the client can read. The client scans the nearby devices, and when it finds the server it is looking for, it establishes a connection and listens for incoming data. This is called point-to-point communication.

![Server-Client](BLE-server-and-client.png)

We will divide this functionality into: 
  1. Creation of a BLE Server
  2. Scan of BLE Server
  3. Creation of a BLE Client and connect to the BLE Served created before

### Server
[Code](server/server.ino)

### Scan
[Code](scan/scan.ino)

### Client
[Code](client/client.ino)


[[Go back]](/communications)
