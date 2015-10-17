
#define Z_Pin A0
#define Y_Pin A1
#define X_Pin A2

 const int minVal = 380;
 const int maxVal = 480;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  float xVal = analogRead(X_Pin);
  float yVal = analogRead(Y_Pin);
  float zVal = analogRead(Z_Pin);

  int xAng = map(xVal, minVal, maxVal, -90, 90);
  int yAng = map(yVal, minVal, maxVal, -90, 90);
  int zAng = map(zVal, minVal, maxVal, -90, 90);

  double x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);
  double y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
  double z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);
  
  Serial.print(x);
  Serial.print("\t");
  Serial.print(y);
  Serial.print("\t");
  Serial.print(z);
  Serial.println("\t");
  delay(100);
}
