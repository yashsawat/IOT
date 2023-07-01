#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <UrlEncode.h>
#include <SparkFun_MAX3010x_Sensor_Library.h>
#include <Wire.h>

const char* ssid = "....";
const char* password = "****";

String phoneNumber = "************";
String apiKey = "*****";

const int alcoholSensorPin = A0;

MAX30105 particleSensor;

void sendMessage(String message) {
  // Data to send with HTTP POST
  String url = "http://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + "&apikey=" + apiKey + "&text=" + urlEncode(message);
  WiFiClient client;
  HTTPClient http;
  http.begin(client, url);

  // Specify content-type header
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  // Send HTTP POST request
  int httpResponseCode = http.POST(url);
  if (httpResponseCode == 200) {
    Serial.print("Message sent successfully");
  } else {
    Serial.println("Error sending the message");
    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);
  }

  // Free resources
  http.end();
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  // Initialize the heart rate sensor
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) {
    Serial.println("MAX30105 sensor not found. Please check wiring!");
    while (1);
  }
  particleSensor.setup(); // Configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A); // Set pulse amplitude for LED
}

void loop() {
  // Read alcohol sensor input
  int alcoholValue = analogRead(alcoholSensorPin);

  // Read heart rate sensor
  float heartRate = particleSensor.getHeartRate();
  if (particleSensor.checkForBeat()) {
    Serial.println("Heartbeat detected!");
  }

  // Check for critical situations
  if (alcoholValue > 500 && heartRate > 150) {
    sendMessage("Unsafe drive! High alcohol level and high stress detected.");
    delay(5000);
  } else if (alcoholValue > 500) {
    sendMessage("Unsafe drive! High alcohol level detected.");
    delay(5000);
  } else if (heartRate > 150) {
    sendMessage("Unsafe drive! High stress detected.");
    delay(5000);
  } else if (heartRate > 0 && heartRate < 150) {
    sendMessage("Good drive! All safe.");
    delay(900000);  // Delay 15 minutes (15 mins = 900,000 milliseconds)
  }

  // Other code in the loop if needed
}
