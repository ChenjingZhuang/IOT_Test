#define LDR_PIN 34
#define LED_PIN 4

int minVal = 4095;
int maxVal = 0;

  void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  Serial.println("Calibrating...");

  unsigned long startTime = millis();

  while (millis() - startTime < 5000) {
    int value = analogRead(LDR_PIN);

    if (value < minVal) minVal = value;
    if (value > maxVal) maxVal = value;

    delay(50);
  }

  Serial.println("Calibration done!");
  Serial.print("Min value: ");
  Serial.println(minVal);
  Serial.print("Max value: ");
  Serial.println(maxVal);
}

  void loop() {
  int value = analogRead(LDR_PIN);

  int threshold = minVal + 50; 

  if (value <= threshold) {
    digitalWrite(LED_PIN, HIGH);  // dark → LED ON
  } else {
    digitalWrite(LED_PIN, LOW);   // light → LED OFF
  }

  delay(100);
}