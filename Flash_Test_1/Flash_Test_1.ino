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

int ledPin1 = 2;
int ledPin2 = 4;

int tipPin1 = 3;
int tipPin2 = 5;

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(tipPin1, OUTPUT);
  pinMode(tipPin2, OUTPUT);
  
  digitalWrite(ledPin1, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(ledPin2, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(tipPin1, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(tipPin2, HIGH);   // turn the LED on (HIGH is the voltage level)


}

// the loop function runs over and over again forever
void loop() {
  delay(1000);              // wait for a second
  digitalWrite(tipPin1, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(ledPin1, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(10);              // wait for a second
  digitalWrite(tipPin1, HIGH);    // turn the LED off by making the voltage LOW
  digitalWrite(ledPin1, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(tipPin2, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(ledPin2, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(10);              // wait for a second
  digitalWrite(tipPin2, HIGH);    // turn the LED off by making the voltage LOW
  digitalWrite(ledPin2, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
}
