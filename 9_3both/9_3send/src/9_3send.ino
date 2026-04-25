#include "secrets.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include "DHTesp.h"

#define DHT_PIN 15

#define MQTT_SERVER "io.adafruit.com"
#define MQTT_PORT 1883

const char* TOPIC_TEMP = "cz/dht22/temperature";
const char* TOPIC_HUM  = "cz/dht22/humidity";

WiFiClient espClient;
PubSubClient mqttClient(espClient);
DHTesp dht;

void reconnect() {
  while (!mqttClient.connected()) {
    mqttClient.connect(AIO_USERNAME, AIO_USERNAME, AIO_KEY);
  }
}

void setup() {
  Serial.begin(115200);

  dht.setup(DHT_PIN, DHTesp::DHT22);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
  }

  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
}

void loop() {

  if (!mqttClient.connected()) {
    reconnect();
  }

  mqttClient.loop();

  TempAndHumidity data = dht.getTempAndHumidity();

  if (isnan(data.temperature) || isnan(data.humidity)) {
    Serial.println("Sensor error");
    delay(2000);
    return;
  }

  String temp = String(data.temperature, 1);
  String hum  = String(data.humidity, 1);

  mqttClient.publish(TOPIC_TEMP, temp.c_str());
  mqttClient.publish(TOPIC_HUM, hum.c_str());

  Serial.println("Sent Temp: " + temp);
  Serial.println("Sent Hum: " + hum);

  delay(2000);
}