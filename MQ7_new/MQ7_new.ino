const int mq7Pin = 35; // Analog input pin connected to the MQ7 sensor

void setup() {
  Serial.begin(9600); // Initialize serial communication for debugging
}

void loop() {
  int sensorValue = analogRead(mq7Pin); // Read analog sensor value
  float voltage = sensorValue * (5.0 / 1023.0); // Convert sensor value to voltage (assuming 5V reference)
  
  // Convert voltage to ppm using the sensitivity of MQ7 sensor (refer to datasheet)
  float ppm = mapFloat(voltage, 0.4, 2.0, 0, 10000); // Example mapping, adjust according to your sensor's calibration
  
  Serial.print("CO Concentration: ");
  Serial.print(ppm);
  Serial.println(" ppm");
  
  delay(1000); // Delay for readability, adjust as needed
}

// Function to map floats (since Arduino's map() function works only with integers)
float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
