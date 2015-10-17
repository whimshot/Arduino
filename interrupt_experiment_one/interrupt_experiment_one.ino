
const int ledPin = 1;
const int interruptPin = 2;
int ledState = 0; // 0 = off, 1 = on
void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  attachInterrupt(0, changeLight, FALLING);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void changeLight() {
  if (ledState == 0) {
    digitalWrite(ledPin, HIGH);
    ledState = 1;
  }
  else {
    digitalWrite(ledPin, LOW);
    ledState = 0;
  }
}
