
#include <Servo.h>;

Servo servo_1;
Servo servo_2;

int xPin = 0;
int yPin = 1;

int xVal;
int yVal;

int servo_1_pos = 90;
int servo_2_pos = 90;

void setup() {
  // put your setup code here, to run once:
  servo_1.attach(9);
  servo_2.attach(8);
  servo_1.write(servo_1_pos);
  servo_2.write(servo_2_pos);
//  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  xVal = analogRead(xPin);
  yVal = analogRead(yPin);
  servo_1_pos = map(xVal, 0, 1023, 0, 170);
  servo_2_pos = map(yVal, 0, 1023, 0, 170);
  servo_1.write(servo_1_pos);
  servo_2.write(servo_2_pos);
  delay(50);
}
