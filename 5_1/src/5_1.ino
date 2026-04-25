#define LED_PIN 4
#define TOUCH_PIN T0

  void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
}

  oid loop() {
  int value = touchRead(TOUCH_PIN);

  if (value < 30) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }

  Serial.println(value);
  delay(50);
}