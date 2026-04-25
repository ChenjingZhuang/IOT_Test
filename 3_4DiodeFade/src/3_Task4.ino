#define LED_PIN 4
int brightness = 0;     
int fadeAmount = 5;     

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  analogWrite(LED_PIN, brightness); 
  brightness += fadeAmount;

  if (brightness <= 0) {
    brightness = 0;
    fadeAmount = -fadeAmount;
  }

  if (brightness >= 255) {
    brightness = 255;
    fadeAmount = -fadeAmount;
  }

  delay(50); 
}