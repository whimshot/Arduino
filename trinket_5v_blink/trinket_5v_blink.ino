/*
  Blink
 */

#include <avr/power.h>      // needed to up clock to 16 MHz on 5v Trinket

const int ledPin = 1;

// the setup function runs once when you press reset or power the board
void setup() {
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1); // 5V Trinket: run at 16 MHz
  
  pinMode(ledPin, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(50);              // pause
  digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
  delay(500);              // pause
}
