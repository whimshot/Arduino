/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */

int timer = 500;
int ledPins[] = {0, 1, 2, 3, 4};

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize each pin as an output.
  for (int pinIndex = 0; pinIndex < 5; pinIndex++) {
    pinMode(ledPins[pinIndex], OUTPUT);
  }
}

// the loop function runs over and over again forever
void loop() {
  for (int pinIndex = 0; pinIndex < 5; pinIndex++) {
    // turn LED pin on 
    digitalWrite(ledPins[pinIndex], HIGH);
    delay(timer); // pause
    // turn LED pin off
    digitalWrite(ledPins[pinIndex], LOW);
  }
}
