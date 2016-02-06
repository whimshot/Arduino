
#include <Servo.h>

Servo pan;    // create servo object to control a servo
Servo tilt;   // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  pan.attach(9);    // attaches the servo on pin 9 to the servo object
  tilt.attach(10);  // attaches the servo on pin 9 to the servo object
  pan.write(90);   // tell servo to go to position in variable 'pos'
  tilt.write(100);  // tell servo to go to position in variable 'pos'
  delay(2048 );
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    pan.write(pos);   // tell servo to go to position in variable 'pos'
    tilt.write(pos);  // tell servo to go to position in variable 'pos'
    delay(16);        // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    pan.write(pos);   // tell servo to go to position in variable 'pos'
    tilt.write(pos);  // tell servo to go to position in variable 'pos'
    delay(16);        // waits 15ms for the servo to reach the position
  }
}

