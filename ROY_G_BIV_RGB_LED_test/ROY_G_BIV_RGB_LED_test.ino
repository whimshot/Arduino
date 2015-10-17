int colors[7][3] = {
  {255, 0, 0}, {255, 32, 0}, {255, 128, 0}, 
  {0, 255, 0}, {0, 0, 255}, {255, 0, 255}, {64, 0, 255}
};


void setup() {
  // put your setup code here, to run once:
  analogWrite(9, 128);
  analogWrite(10, 128);
  analogWrite(11, 128);
  delay(512);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < 7; i++) {
    analogWrite(9, colors[i][0]);
    analogWrite(10, colors[i][1]);
    analogWrite(11, colors[i][2]);
    delay(1024);
  }
}
