#include <DHT.h>
#include <Wire.h>
#include <RTClib.h>
#include <SD.h>

#define DHT11_PIN A0      // Pin A0 for the DHT11 sensor
#define SD_CS_PIN 10      // Chip select pin for the SD card

DHT dht(DHT11_PIN, DHT11);
RTC_DS1307 RTC;  // Create an RTC object for the DS1307

void setup(){
  Serial.begin(9600);

  // Initialize the SD card
  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("SD card error");
    return;
  }
  Serial.println("SD card initialized");

  // Initialize the RTC module
  if (!RTC.begin()) {
    Serial.println("RTC error");
    while (1);  // Infinite loop if RTC is not found
  }

  if (!RTC.isrunning()) {
    Serial.println("RTC is not running, initializing...");
    RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));  // Set RTC to compile time
  }

  Serial.println("RTC is working correctly");

  dht.begin();  // Initialize the DHT sensor
}

void loop()
{
  // Read date and time from the RTC
  DateTime now = RTC.now();

  // Read humidity and temperature from the DHT sensor
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check if the reading failed
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Sensor reading error!");
    return;
  }

  // Print data to the serial monitor
  Serial.print("Temperature = ");
  Serial.println(temperature);
  Serial.print("Humidity = ");
  Serial.println(humidity);
  Serial.print("Date and Time: ");
  Serial.print(now.day(), DEC);
  Serial.print("/");
  Serial.print(now.month(), DEC);
  Serial.print("/");
  Serial.print(now.year(), DEC);
  Serial.print(" ");
  Serial.print(now.hour(), DEC);
  Serial.print(":");
  Serial.print(now.minute(), DEC);
  Serial.print(":");
  Serial.println(now.second(), DEC);

  // Open or create "data.csv" on the SD card
  File dataFile = SD.open("data.csv", FILE_WRITE);

  // If the file opened correctly, write to it
  if (dataFile) {
    // Write date, time, temperature, and humidity in CSV format
    dataFile.print(now.day(), DEC);
    dataFile.print("/");
    dataFile.print(now.month(), DEC);
    dataFile.print("/");
    dataFile.print(now.year(), DEC);
    dataFile.print(" ");
    dataFile.print(now.hour(), DEC);
    dataFile.print(":");
    dataFile.print(now.minute(), DEC);
    dataFile.print(":");
    dataFile.print(now.second(), DEC);
    dataFile.print(",");
    dataFile.print(temperature);
    dataFile.print(",");
    dataFile.println(humidity);
    dataFile.close();  // Close the file after writing

    // Confirm successful writing in serial monitor
    Serial.println("Data written to SD card");
  } else {
    Serial.println("File open error");
  }

  // Wait 5 minutes before the next reading (300,000 milliseconds)
  delay(300000);  // 5 minutes = 300,000 milliseconds
}
