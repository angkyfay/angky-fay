#include <WiFi.h>
#include <HTTPClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Definisikan pin data
#define ONE_WIRE_BUS 4  // Ubah sesuai pin GPIO yang digunakan

const char* ssid = "kkail";
const char* password = "00000001";
const char* serverName = "http://192.168.118.119:5000/post-data"; // Ganti dengan alamat IP server Anda

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(115200);
  sensors.begin();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Menghubungkan ke WiFi...");
  }
  Serial.println("Terhubung ke WiFi");
}

void loop() {
  sensors.requestTemperatures();
  float temperatureC = sensors.getTempCByIndex(0);
  
  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println("°C");

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    String httpRequestData = "{\"temperature\":" + String(temperatureC) + "}";
    int httpResponseCode = http.POST(httpRequestData);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error pada pengiriman POST: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  }
  delay(10000); // Kirim data setiap 10 detik
}
