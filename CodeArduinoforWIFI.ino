#include <WiFi.h>
#include <HTTPClient.h>

// 🔹 WiFi credentials
const char* ssid = "YOUR_WIFI";             // ⚠️ Replace with your WiFi name
const char* password = "YOUR_PASSWORD";     // ⚠️ Replace with your WiFi password

// 🔹 Firebase URL (with `/data.json`)
const char* firebaseURL = "https://esp32-data-xxxxxxxxxxxxxxxxxxx.firebasedatabase.app/data.json";  // ⚠️ Replace with your Firebase URL

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, 16, 17); // RX2 = GPIO 16

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\n✅ WiFi connected!");
}

void loop() {
  if (Serial2.available()) {
    String data = Serial2.readStringUntil('\n');
    data.trim();

    Serial.println("📩 Data received from Uno: " + data);

    int sep = data.indexOf(',');
    if (sep != -1) {
      String temp = data.substring(0, sep);
      String hum = data.substring(sep + 1);

      Serial.print("📡 Temperature: ");
      Serial.print(temp);
      Serial.print("°C | Humidity: ");
      Serial.print(hum);
      Serial.println("%");

      if (temp.length() > 0 && hum.length() > 0) {
        // 🔹 Build JSON payload
        String payload = "{\"temperature\":" + temp + ",\"humidity\":" + hum + "}";

        Serial.println("🌍 Sending data to Firebase: " + payload);

        if (WiFi.status() == WL_CONNECTED) {
          HTTPClient http;
          http.begin(firebaseURL);  // ✅ `firebaseURL` is defined here
          http.addHeader("Content-Type", "application/json");
          int httpCode = http.PUT(payload);  // 🔹 Use `PUT` to replace data

          if (httpCode > 0) {
            Serial.println("✅ Data successfully sent to Firebase!");
          } else {
            Serial.print("❌ Error sending data! HTTP Code: ");
            Serial.println(httpCode);
          }

          http.end();
        } else {
          Serial.println("❌ WiFi disconnected!");
        }
      } else {
        Serial.println("❌ Invalid values received!");
      }
    }
  }

  delay(5000);
}
