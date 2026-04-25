#define LED_PIN 4

unsigned long ledTime = 0, printTime = 0;
bool ledState = false;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  unsigned long now = millis();

  // LED: 0.5s ON, 2s OFF
  if (ledState && now - ledTime >= 500) {
    ledState = false;
    ledTime = now;
    digitalWrite(LED_PIN, LOW);
  } 
  else if (!ledState && now - ledTime >= 2000) {
    ledState = true;
    ledTime = now;
    digitalWrite(LED_PIN, HIGH);
  }

  if (now - printTime >= 1000) {
    printTime = now;
    Serial.print("Running time: ");
    Serial.print(now / 1000);
    Serial.println(" seconds");
  }
} 