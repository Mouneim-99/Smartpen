#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>
#include <MPU6050_tockn.h>

const char* ssid = "D-Link";
const char* password = "MAMRI2000";
const char* host = "192.168.1.3";
const uint16_t port = 5000;

WiFiClient client;
MPU6050 mpu6050(Wire);

void setup() {
  Serial.begin(115200);
  delay(1000);

  // I2C pins for ESP32
  Wire.begin(21, 22);

  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi connected!");

  // Connect to Python server
  if (!client.connect(host, port)) {
    Serial.println("Failed to connect to server!");
    while (1);
  }
  Serial.println("Connected to server!");

  // Initialize MPU6050
  Serial.println("Initializing MPU6050...");
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  Serial.println("MPU6050 is ready!");
}

void loop() {
  mpu6050.update();

  String hand = "Right";                    // or Left
String timestamp = String(millis());      // time since boot

String data =
      hand + "," +
      timestamp + "," +
      String(mpu6050.getAccX()) + "," +
      String(mpu6050.getAccY()) + "," +
      String(mpu6050.getAccZ()) + "," +
      String(mpu6050.getGyroX()) + "," +
      String(mpu6050.getGyroY()) + "," +
      String(mpu6050.getGyroZ());

  client.println(data);
  Serial.println("Sent: " + data);

  delay(500);
}
