#define LED_PIN 4

const char *pattern = "10101010";

int len;

  void setup() {
  pinMode(LED_PIN, OUTPUT);
  len = strlen(pattern);
}

  void loop() {
  for (int i = 0; i < len; i++) {

    if (pattern[i] == '1') {
      digitalWrite(LED_PIN, HIGH);
      delay(200);   // short ON
    } else {
      digitalWrite(LED_PIN, LOW);
      delay(600);   // long OFF
    }

    digitalWrite(LED_PIN, LOW);
    delay(50); 
  }
}