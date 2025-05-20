Arduino Humidity Sensor can be connected online

A project to measure room humidity using a DHT11 sensor and log data to an SD card.

## 🔧 Hardware

- Arduino Uno
- DHT11
- SD Card Module
- RTC Module (DS1307)
- Jumper wires, breadboard
- ESP32 if you want to connect it to wifi

## 📐 Circuit Diagram

coming soon

## 📄 Code

All Arduino code is in the `/code` folder.

## 🧪 What it Does

- Logs humidity and temperature every minute
- Adds timestamps using the RTC
- Saves everything in `data.csv` on the SD card

## 📦 How to Run

1. Open the `.ino` file in Arduino IDE.
2. Install the DHT and RTC libraries.
3. Upload and monitor the serial output.

## 🧠 Update with WIFI ESP32

- Add Wi-Fi with ESP8266
- Upload data to a web dashboard
