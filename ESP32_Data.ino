#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// Replace with your network credentials
const char* ssid = "Your_SSID";
const char* password = "Your_Password";

// Google Sheets API credentials
const char* google_script_id = "-----------Paste Your Deploye ID -----------------"; // This will be created in step 4


// Analog pin
const int analogPin = 32; // Changed to pin 32 for testing
float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  pinMode(analogPin, INPUT);

  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    int analogValue = analogRead(analogPin);
    float voltage = floatMap(analogValue, 0, 4095, 0, 12);
    Serial.print("Analog Value: ");
    Serial.println(analogValue); // Debugging: Print the analog value

    String url = String("https://script.google.com/macros/s/") + google_script_id + "/exec?value=" + voltage;

    http.begin(url);
    int httpCode = http.GET();

    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println("Response: " + payload);
    } else {
      Serial.println("Error in sending request");
    }

    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }

  delay(10000); // Send data every 10 seconds
}
