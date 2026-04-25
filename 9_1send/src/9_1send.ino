#include "secrets.h"
#include <WiFi.h>
#include <PubSubClient.h>

#define MQTT_SERVER "io.adafruit.com"
#define MQTT_PORT 1883

const char* TOPIC = "cz/hello/world";

WiFiClient espClient;
PubSubClient mqttClient(espClient);

bool sent = false;

void callback(char* topic, byte* payload, unsigned int length) {
}

void reconnect() {
  while (!mqttClient.connected()) {
    Serial.print("Connecting MQTT...");

    if (mqttClient.connect(AIO_USERNAME, AIO_USERNAME, AIO_KEY)) {
      Serial.println("OK");
    } else {
      Serial.print("FAILED rc=");
      Serial.println(mqttClient.state());
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }

  Serial.println(" Connected!");

  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
}

void loop() {

  if (!mqttClient.connected()) {
    reconnect();
  }

  mqttClient.loop();

  if (!sent) {
    mqttClient.publish(TOPIC, "Hello World!");
    Serial.println("Message sent: Hello World!");
    sent = true;
  }
}