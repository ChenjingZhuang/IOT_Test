#include <ESP32Servo.h>

#define CLK 18
#define DT 19
#define SERVO_PIN 5

Servo myservo;

int counter = 0;
int lastCLK;
int angle = 90;

  void setup() {
  Serial.begin(115200);

  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);

  myservo.attach(SERVO_PIN);

  lastCLK = digitalRead(CLK);
}

  void loop() {
  int currentCLK = digitalRead(CLK);

  if (currentCLK != lastCLK && currentCLK == HIGH) {

    if (digitalRead(DT) != currentCLK) {
      counter++;
      angle += 5;
    } else {
      counter--;
      angle -= 5;
    }

    angle = constrain(angle, 0, 180);

    myservo.write(angle);

    Serial.println(angle);
  }

  lastCLK = currentCLK;
}