#include <Arduino.h>

// Define the analog pin connected to the MQ-3 sensor
const int mq3Pin = 33; // Example pin, adjust according to your actual connection

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Wait for serial monitor to open
  while (!Serial) {
    ; // Wait for serial port to connect. Needed for native USB port only
  }

  // Configure the ADC resolution to 12 bits (0-4095)
  analogReadResolution(12);
}

void loop() {
  // Read the analog value from the MQ-3 sensor
  int sensorValue = analogRead(mq3Pin);

  // Check for errors reading from the sensor
  if (sensorValue == -1) {
    Serial.println("Error reading from sensor!");
  } else {
    // Print the sensor value to the serial monitor
    Serial.print("MQ-3 Sensor Value: ");
    Serial.println(sensorValue);
  }

  // Wait for a short delay before taking the next reading
  delay(500);
}
