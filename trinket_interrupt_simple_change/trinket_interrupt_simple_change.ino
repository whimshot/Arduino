/*
 * This is just a simple example of an interrupt handler
 */
#include <avr/power.h>      // needed to up clock to 16 MHz on 5v Trinket

const int ledPin = 1;
const int interruptPin = 2;
int ledState = 0; // 0 = off, 1 = on
void setup() {
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1); // 5V Trinket: run at 16 MHz
  
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  attachInterrupt(0, changeLight, CHANGE);
}

void loop() {
  // Everything happens in the interrupt handler
}

void changeLight() {
  // if the light is off (ledState == 0)
  // 1. turn the light on
  // 2. change ledState to 1
  if (ledState == 0) {
    digitalWrite(ledPin, HIGH);
    ledState = 1;
  }
  else {
    // if the light is on (ledState != 0)
    // 1. turn the light off
    // 2. change ledState to 0
    digitalWrite(ledPin, LOW);
    ledState = 0;
  }
}
