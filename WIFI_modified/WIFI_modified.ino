#include <stdio.h>
#include <WiFi.h>

#define WIFI_TIMEOUT 100000
#define DEFAULT_LED_PIN 2

// Wi-Fi variables
WiFiClient wifi_client;
const char *wifi_ssid = "Codavali's-5G";
const char *wifi_password = "janishi123";
const int wifiButton = 4;

//Declaring Setup
void setup() {
  Serial.begin(115200);              // Config Serial
  pinMode(DEFAULT_LED_PIN, OUTPUT);  // Config LED
  pinMode(wifiButton, INPUT);        // Config Wi-Fi button
}

void loop() {
  // read and save data
  
void connectWiFi();

void log_info();
void log_info(String message);
void log_error(String message);
  // if button is pressed, send data to MQTT
  if (digitalRead(wifiButton) == HIGH) {
    log_info("Wi-FI Enabked success");
    
  }
}

// function to connect to Wi-Fi
void connectWiFi() {
  if (WiFi.status() == WL_CONNECTED) {
    return;
  }

  WiFi.begin(wifi_ssid, wifi_password);
  log_info("Connecting to WiFi network...");

  unsigned long startTime = millis();
  while (WiFi.status() != WL_CONNECTED && (millis() - startTime < WIFI_TIMEOUT)) {
    digitalWrite(DEFAULT_LED_PIN, HIGH);
    Serial.print(".");
    delay(300);
    digitalWrite(DEFAULT_LED_PIN, LOW);
    delay(300);
  }

  if (WiFi.status() != WL_CONNECTED) {
    log_error("Failed to connect to WiFi!");
    digitalWrite(DEFAULT_LED_PIN, HIGH);
  } else {
    log_info("Connected! IP address: " + String(WiFi.localIP()));
    digitalWrite(DEFAULT_LED_PIN, LOW);
  }
}

void log_info(String message) {
  Serial.println("[INFO]  " + message);
}

void log_error(String message) {
  Serial.println("[ERROR] " + message);
}
