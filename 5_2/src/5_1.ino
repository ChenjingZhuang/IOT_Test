#define CLK 18
#define DT 19

int counter = 0;
int lastStateCLK;

  void setup() {
  Serial.begin(115200);

  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);

  lastStateCLK = digitalRead(CLK);
}

  void loop() {
  int currentStateCLK = digitalRead(CLK);

  if (currentStateCLK != lastStateCLK && currentStateCLK == HIGH) {

    if (digitalRead(DT) != currentStateCLK) {
      counter++;
    } else {
      counter--;
    }

    Serial.println(counter);
  }

  lastStateCLK = currentStateCLK;
}