#include <ESP32Servo.h>
#include "DHT.h"

#define DHTPIN 15
#define DHTTYPE DHT22

#define SERVO_PIN 5
#define RELAY_PIN 18
#define BUTTON_PIN 25

volatile bool emergencyStop = false;

DHT dht(DHTPIN, DHTTYPE);
Servo servo;

void IRAM_ATTR myISR() {
  emergencyStop = true;
}

void setup() {
  Serial.begin(115200);

  dht.begin();
  servo.attach(SERVO_PIN);

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), myISR, FALLING);
}

void loop() {

  // 🔴 Emergency stop (locks system forever)
  if (emergencyStop) {
    digitalWrite(RELAY_PIN, LOW);
    servo.write(0);

    Serial.println("EMERGENCY STOP ACTIVATED");

    while (true) {
      delay(1000);
    }
  }

  float temp = dht.readTemperature();

  Serial.println(temp);

  int angle = map(temp, 0, 50, 0, 180);
  servo.write(constrain(angle, 0, 180));

  if (temp > 28) {
    digitalWrite(RELAY_PIN, HIGH);
  } else {
    digitalWrite(RELAY_PIN, LOW);
  }

  delay(1000);
}