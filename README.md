# ESP32 Digital Lights

ESP32 digital lights with discovery, speed, multiple effects etc.

## Hardware Setup

TBD

## Software Setup

- Using Atom or VS Code, install [Platform IO](https://platformio.org/platformio-ide)
- Once setup, install the `esp32` embedded platform
- Copy `src/setup-template.h` to `src/setup.h` and add your network, MQTT and
 other setup information. Take note of the `HOSTNAME` you set. You will need
 this later to send MQTT messages.
- Build the project (Ctrl+Alt+B) and check for any errors
- Upload to your board of choice (Ctrl+Alt+U).

## Example Home Assistant Configuration

```yaml
```
