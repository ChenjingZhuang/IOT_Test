#include "secrets.h"
#include <WiFi.h>
#include <PubSubClient.h>

#define MQTT_SERVER "io.adafruit.com"
#define MQTT_PORT 1883

const char* TOPIC = "cz/hello/world";

WiFiClient espClient;
PubSubClient mqttClient(espClient);

bool subscribed = false;

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Received: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

  void setup() {
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("WiFi connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
  mqttClient.setCallback(callback);
}

  void reconnectMQTT() {
  if (mqttClient.connected()) return;

  Serial.print("Connecting MQTT...");

  if (mqttClient.connect(AIO_USERNAME, AIO_USERNAME, AIO_KEY)) {
    Serial.println("OK");

    if (!subscribed) {
      mqttClient.subscribe(TOPIC);
      Serial.println("Subscribed once to: cz/hello/world");
      subscribed = true;
    }

  } else {
    Serial.print("FAILED rc=");
    Serial.println(mqttClient.state());
  }
}

  void loop() {
  if (!mqttClient.connected()) {
    reconnectMQTT();
  }

  mqttClient.loop();
}