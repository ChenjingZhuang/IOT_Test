#define BUTTON_PIN 14
#define LED_PIN 4
#define BUZ_PIN 17

unsigned long pressStart = 0;
bool wasPressed = false;
bool buzzerOn = false;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZ_PIN, OUTPUT);
}

void loop() {
  bool pressed = (digitalRead(BUTTON_PIN) == LOW);

  if (pressed && !wasPressed) {
    pressStart = millis();
    buzzerOn = false;
  }

  if (pressed) {
    unsigned long pressDuration = millis() - pressStart;

    if (pressDuration >= 5000 && !buzzerOn) {
      tone(BUZ_PIN, 1000);
      buzzerOn = true;
    }

    digitalWrite(LED_PIN, LOW);
  }

  if (!pressed && wasPressed) {
    noTone(BUZ_PIN);
    digitalWrite(BUZ_PIN, LOW);
    buzzerOn = false;
  }

  if (!pressed) {
    digitalWrite(LED_PIN, HIGH);
  }

  wasPressed = pressed;
}