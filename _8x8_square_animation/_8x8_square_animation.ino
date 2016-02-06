#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

void setup() {
  matrix.begin(0x70);  // pass in the address
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 8; i++) {
    matrix.clear();
    matrix.drawRect(i, i, (8-(2*i)), (8-(2*i)), LED_ON);
    matrix.writeDisplay();
    delay(24);
  }
}
