#include <Arduino.h>

#define DEFAULT_LED_PIN 2

// LDR variables
const int ldrPin = 32;

// MQ-3 sensor variables
const int mq3Pin = 34;

// MQ-7 sensor variables
const int mq7Pin = 35;

void setup() {
  Serial.begin(9600); // Initialize serial communication

  // LDR Setup
  pinMode(ldrPin, INPUT);

  // MQ-3 Setup
  analogReadResolution(12);
  pinMode(mq3Pin, INPUT);

  // MQ-7 Setup
  pinMode(mq7Pin, INPUT);
}

void loop() {
  // LDR loop
  int ldrValue = analogRead(ldrPin);
  Serial.println(ldrValue);
  if (ldrValue <= 1500) {
    Serial.println("Helmet Detected");
   // Serial.println(ldrValue);
  } else {
    Serial.println("Helmet Not Detected");
  }

  // MQ-3 loop
  int mq3SensorValue = analogRead(mq3Pin);
  Serial.println(mq3SensorValue);
  if (mq3SensorValue != -1) {
    if (mq3SensorValue >= 3000) {
      Serial.print("Alcohol detected with value : ");
      Serial.println(mq3SensorValue);
    } else {
      Serial.println("No Alcohol Found");
    }
  } else {
    Serial.println("Error reading from MQ-3 sensor!");
  }

  // MQ-7 loop
  int mq7SensorValue = analogRead(mq7Pin);
  float voltage = mq7SensorValue * (5.0 / 1023.0);

  float ppm = mapFloat(voltage, 0.2, 2.0, 0, 10000);
  Serial.print("ppm obtained ");
  Serial.println(ppm);
  if (ppm > 20000) {
    Serial.println("CO gas detected with value : ");
    Serial.println(ppm);
  } else {
    Serial.println("No CO gas detected.");
  }

  delay(3000);
}

// Function to map floats (since Arduino's map() function works only with integers)
float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
