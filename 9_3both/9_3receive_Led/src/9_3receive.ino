#include "secrets.h"
#include <WiFi.h>
#include <PubSubClient.h>

#define RED_LED 13
#define GREEN_LED 12

#define MQTT_SERVER "io.adafruit.com"
#define MQTT_PORT 1883

const char* TOPIC_TEMP = "cz/dht22/temperature";

WiFiClient espClient;
PubSubClient mqttClient(espClient);

float lastTemp = 0;

void callback(char* topic, byte* payload, unsigned int length) {

  String msg = "";

  for (int i = 0; i < length; i++) {
    msg += (char)payload[i];
  }

  lastTemp = msg.toFloat();

  Serial.print("Temperature received: ");
  Serial.println(lastTemp);

  if (lastTemp > 25.0) {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
  } else {
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
  }
}

void reconnect() {
  while (!mqttClient.connected()) {
    if (mqttClient.connect(AIO_USERNAME, AIO_USERNAME, AIO_KEY)) {
      mqttClient.subscribe(TOPIC_TEMP);
    } else {
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
  }

  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
  mqttClient.setCallback(callback);
}

void loop() {

  if (!mqttClient.connected()) {
    reconnect();
  }

  mqttClient.loop();
}