
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
  xVal = map(xVal, 0, 1023, -10, 10);
  yVal = map(yVal, 0, 1023, -8, 10);
  servo_1_pos += xVal;
  servo_2_pos += yVal;
  if (servo_1_pos < 1) { servo_1_pos = 0; }
  if (servo_1_pos > 170) { servo_1_pos = 170; }
  if (servo_2_pos < 1) { servo_2_pos = 0; }
  if (servo_2_pos > 170) { servo_2_pos = 170; }
//  Serial.print("X: ");
//  Serial.println(servo_1_pos);
//  Serial.print("Y: ");
//  Serial.println(servo_2_pos);
  servo_1.write(servo_1_pos);
  servo_2.write(servo_2_pos);
  delay(50);
}
