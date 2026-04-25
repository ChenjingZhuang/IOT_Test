int counter = 0; 

void setup() {
  Serial.begin(115200);
}

void loop() {
  // Exercise 2
  Serial.print("Seconds since start/reset: ");
  Serial.println(counter);
  
  counter++;

  // Exercise 3
  if (counter > 10) {
    counter = 0;
  }

  delay(1000); 
}