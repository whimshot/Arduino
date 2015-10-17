/*
 * Fibbo Blink
 * 
 * This sketch blinks the LED for a count of each fibonacci number
 * in the sequence up to a given fibonacci number.
 * 
 * 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 
 * 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 
 * 46368, 75025, 121393, 196418, 317811
 */

#include <avr/power.h>      // needed to up clock to 16 MHz on 5v Trinket

const int ledPin = 1;
const int delayTime = 50;
const int maxFibonacci = 34;

// the setup function runs once when you press reset or power the board
void setup() {
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1); // 5V Trinket: run at 16 MHz

  pinMode(ledPin, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  int fn = 1;
  int fn_minus_one = 0;
  while (fn_minus_one < maxFibonacci) {
    for (int i = 1; i <= fn; i++) {
      digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(delayTime);              // pause
      digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
      delay(delayTime);              // pause
    }
    int tmp = fn;
    fn += fn_minus_one;
    fn_minus_one = tmp;
    delay(1000);
  }
}
