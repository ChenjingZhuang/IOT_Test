#define BUTTON_PIN 14
#define LED_PIN 4
#define BUZ_PIN 17

int Buttonstate = LOW;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN,  OUTPUT);
  pinMode(BUZ_PIN, OUTPUT);
}

void loop() {
  Buttonstate = digitalRead(BUTTON_PIN); 
  if(Buttonstate == LOW) {   
    digitalWrite(BUZ_PIN, HIGH);  // buzzer ON
    digitalWrite(LED_PIN, LOW);   // LED OFF
  } else {                   
    digitalWrite(BUZ_PIN, LOW);   
    digitalWrite(LED_PIN, HIGH);  
  }


}



/*
//Test
int buttonState;

void setup() {
pinMode(BUTTON_PIN, INPUT);
Serial.begin(9600);
}

void loop() {
buttonState = digitalRead(BUTTON_PIN);
Serial.println(buttonState);
}

*/