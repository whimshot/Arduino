
#include <avr/power.h>      // needed to up clock to 16 MHz on 5v Trinket

const int sensorPowerPin = 1;
const int interruptPin = 2;
const int dataOutputPin = 0;

void setup() {
  // put your setup code here, to run once:
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1); // 5V Trinket: run at 16 MHz

  pinMode(sensorPowerPin, OUTPUT);
  digitalWrite(sensorPowerPin, LOW);

  pinMode(dataOutputPin, OUTPUT);
  digitalWrite(dataOutputPin, LOW);

  attachInterrupt(0, readSensor, RISING);
}



void loop() {
  // put your main code here, to run repeatedly:

}

void readSensor() {
  digitalWrite(sensorPowerPin, HIGH);
  int sensorData = analogRead(2);
  int dataOutput = map(sensorData, 0, 1023, 0, 255);
  analogWrite(dataOutputPin, dataOutput);
  delayMicroseconds(65536);
  digitalWrite(sensorPowerPin, LOW);
}
