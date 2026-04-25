#define BUTTON_PIN 14
#define LED_PIN 4
#define BUZ_PIN 17

bool ledState = false;       
bool lastButtonState = HIGH; 

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  bool currentButtonState = digitalRead(BUTTON_PIN);
  
  if(currentButtonState == LOW && lastButtonState == HIGH) {
    ledState = !ledState;           
    digitalWrite(LED_PIN, ledState);
    delay(300);                      
  }

  lastButtonState = currentButtonState;
}
