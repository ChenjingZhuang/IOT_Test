#define BUTTON_PIN 14
#define LED_PIN 4
#define BUZ_PIN 17

bool ledState = false;       
bool lastButtonState = HIGH; 

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZ_PIN, OUTPUT);
}

void loop() {
  if(digitalRead(BUTTON_PIN) == LOW) { 
    unsigned long pressStart = millis(); 

    while(digitalRead(BUTTON_PIN) == LOW) {
    }

    unsigned long pressDuration = millis() - pressStart; 

    if(pressDuration < 5000) { // short press < 5s
      digitalWrite(LED_PIN, HIGH);
      delay(2000);              // LED ON for 2 seconds
      digitalWrite(LED_PIN, LOW);
    } else {                    
      digitalWrite(BUZ_PIN, HIGH);
      delay(2000);              
      digitalWrite(BUZ_PIN, LOW);
    }
  }
}
