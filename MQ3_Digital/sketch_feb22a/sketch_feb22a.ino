#include <Arduino.h>

// Define the analog pin connected to the MQ-3 sensor
const int mq3Pin = 34; // Example pin, adjust according to your actual connection

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Read the analog value from the MQ-3 sensor
  int sensorValue = digitalRead(mq3Pin);

  // Print the sensor value to the serial monitor
  Serial.print("MQ-3 Sensor Value: ");
  Serial.println(sensorValue);

  // You can add further processing or actions based on the sensor value here

  // Wait for a short delay before taking the next reading
  delay(1000);
}
