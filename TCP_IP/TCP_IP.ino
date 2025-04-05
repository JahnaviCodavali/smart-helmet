#include <WiFi.h>

// WiFi credentials (replace with your network SSID and password)
const char* ssid = "your_wifi_ssid";
const char* password = "your_wifi_password";

// TCP server details (replace with server IP and port)
const char* server_address = "192.168.1.100"; // Replace with your server IP
const int server_port = 8080; // Replace with your server port

WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Connect to WiFi network
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Send some data to the server (replace with your data)
  String data = "Hello from ESP32!";
  client.print(data);
  Serial.println("Sent data: " + data);
  delay(2000);
}

void reconnect() {
  Serial.print("Connecting to TCP server... ");
  if (client.connect(server_address, server_port)) {
    Serial.println("connected");
  } else {
    Serial.print("failed, retrying in 5 seconds");
    delay(5000);
  }
}
