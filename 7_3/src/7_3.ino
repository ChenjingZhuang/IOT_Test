#include <ESP32Servo.h>
#include "DHT.h"

#define DHTPIN 15
#define DHTTYPE DHT22

#define SERVO_PIN 5
#define RELAY_PIN 18

DHT dht(DHTPIN, DHTTYPE);
Servo servo;

  void setup() {
  Serial.begin(115200);

  dht.begin();

  servo.attach(SERVO_PIN);

  pinMode(RELAY_PIN, OUTPUT);
}

  void loop() {
  float temp = dht.readTemperature();

  Serial.print("Temperature: ");
  Serial.println(temp);

  // map temperature to servo angle
  int angle = map(temp, 0, 50, 0, 180);
  angle = constrain(angle, 0, 180);

  servo.write(angle);

  // relay control
  if (temp > 30) {
    digitalWrite(RELAY_PIN, HIGH);  
  } else {
    digitalWrite(RELAY_PIN, LOW);   
  }

  delay(1000);
}