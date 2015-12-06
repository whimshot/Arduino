// Adafruit_NeoMatrix example for single NeoPixel Shield.
// Scrolls 'Howdy' across the matrix in a portrait (vertical) orientation.

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
#define PSTR // Make Arduino Due happy
#endif

#define PIN 6

// MATRIX DECLARATION:
// Parameter 1 = width of NeoPixel matrix
// Parameter 2 = height of matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
//   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
//     Position of the FIRST LED in the matrix; pick two, e.g.
//     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
//   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs are arranged in horizontal
//     rows or in vertical columns, respectively; pick one or the other.
//   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns proceed
//     in the same order, or alternate lines reverse direction; pick one.
//   See example below for these values in action.
// Parameter 5 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)


// Example for NeoPixel Shield.  In this application we'd like to use it
// as a 5x8 tall matrix, with the USB port positioned at the top of the
// Arduino.  When held that way, the first pixel is at the top right, and
// lines are arranged in columns, progressive order.  The shield uses
// 800 KHz (v2) pixels that expect GRB color data.
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 5, PIN,
                            NEO_MATRIX_BOTTOM + NEO_MATRIX_LEFT +
                            NEO_MATRIX_ROWS   + NEO_MATRIX_PROGRESSIVE,
                            NEO_GRB           + NEO_KHZ800);

int colours[][3] = {
  { 255, 0 , 0 },   // Red
  { 255, 160, 0 },   // Orange
  { 160, 160, 0 },  // Yellow
  { 0, 255, 0 },    // Green
  { 0, 0, 255 },    // Blue
  { 128, 0, 255 },   // Indigo
  { 255, 0, 255 },  // Violet
  { 128, 128, 128}, // White
};

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255)
};

void setup() {
  matrix.begin();
  matrix.setBrightness(100);
}

void loop() {
  matrix.fillScreen(0);
  for (int i = 0; i < matrix.width() - 1; i++) {
    for (int j = 0; j < random(matrix.height() + 1); j++) {
      matrix.drawPixel(i, j, matrix.Color(colours[i][0], colours[i][1], colours[i][2]));
    }
  }
  matrix.show();
  delay(32);
}

