#define LED_PIN 4

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  analogWrite(LED_PIN, 255); // LED on (max brightness)
  delay(1000);                
  analogWrite(LED_PIN, 0);   
  delay(1000);               
}
