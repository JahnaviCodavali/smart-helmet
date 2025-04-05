#include <WiFi.h>
#include <PubSubClient.h>
#include <vector>

// WiFi credentials
const char *ssid = "Codavali's-5G";
const char *password = "janishi123";

// Adafruit IO credentials
const char *IO_USERNAME = "your_io_username";
const char *IO_KEY = "your_io_key";

// MQTT variables
const char *mqtt_broker = "io.adafruit.com";
const int mqtt_port = 1883;
const int mqtt_timeout = 10000;
const char *MQTT_TOPIC = "smart_helme";

WiFiClient wifi_client;
PubSubClient mqtt_client(wifi_client);

// Function prototypes
void connectWiFi();
void connectMQTT();
void sendDataToMQTT();

void setup() {
  pinMode(wifiButton, INPUT_PULLUP);
  connectWiFi();
}

void loop() {
  if (digitalRead(wifiButton) == HIGH) {
    sendDataToMQTT();
  }
}

// Function to connect to WiFi
void connectWiFi() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
}

// Function to connect to MQTT
void connectMQTT() {
  unsigned long tempoInicial = millis();
  while (!mqtt_client.connected() && (millis() - tempoInicial < mqtt_timeout)) {
    if (WiFi.status() != WL_CONNECTED) {
      return;
    }

    Serial.println("Connecting to MQTT Broker...");
    if (mqtt_client.connect("pc_lixeira", IO_USERNAME, IO_KEY)) {
      Serial.println("Connected to MQTT broker!");
    } else {
      Serial.println("Connection to MQTT broker failed!");
    }
    delay(150);
  }
}

// Function to send data to MQTT
void sendDataToMQTT() {
  connectMQTT();

  // Restore data from the file system
  std::vector<HelmetData> dataList = restoreUnsentHelmetData();

  for (HelmetData data : dataList) {
    // Convert the data to a JSON string
    String jsonPayload = printHelmetData(data);

    // Convert the JSON string to a char array
    char payload[jsonPayload.length() + 1];
    jsonPayload.toCharArray(payload, sizeof(payload));

    // Publish the data to the MQTT topic
    if (mqtt_client.publish(MQTT_TOPIC, payload)) {
      Serial.println("Data published to MQTT topic");
    } else {
      Serial.println("Failed to publish data to MQTT topic");
    }
    delay(1000);
  }
}
