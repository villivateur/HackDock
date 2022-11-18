# HackDock

*A cute box for pushing notice from servers to reality. For developers!*

Runs on ESP8266 with Arduino Framework via PlatformIO.

## Features

You can configure HackDock's parameters by Serial communication.

Parameters:
- Wifi SSID
- Wifi Password
- IP address
- Net mask
- Gateway

After configuring, you can send notifications to HackDock with UDP.

Notifications:
- 2 LEDs (Always on, blink, etc.)
- Beep

You can also read button status with UDP.

## Development progress

- [x] LED Blink
- [x] Beep
- [ ] Custom pins
- [x] Button
- [x] Wifi connect
- [x] Serial communication
- [x] UDP communication
- [x] Push button to mute
- [ ] Watchdog
- [ ] More error code
