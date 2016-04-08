/*
 * Adafruit NeoPixel initialization values
 */
#include <Adafruit_NeoPixel.h>

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>

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

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      40
/*
 *  Parameter 1 = number of pixels in strip
 *  Parameter 2 = Arduino pin number (most are valid)
 *  Parameter 3 = pixel type flags, add together as needed:
 *    NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
 *    NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
 *    NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
 *    NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
 */

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

/*
 * The following pins are for controlling the Spectrum Shield
 */
#define STROBE 4
#define RESET 5
#define DC_One A0
#define DC_Two A1

#define DELAY_Pin A3
#define CURVE_Pin A2

#define NUMCOLOURS      7

/*
 * Define the colour values that we will be using. Aiming for ROY G BIV
 * or the nearest equivalent.
 */
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

// Define some Spectrum Shield variables
int freq_amp;
int Frequencies_One[8];
int Frequencies_Two[8];
int offset = 0;

char serialIncoming = 'b'; // default to bar graph

/*
 * Setup the following:
 * 1. NEO Pixels
 * 2. Spectrum Shield
 * 3. Delay pin
 * 4. Interrupt handler
 */

void setup() {
  matrix.begin();
  matrix.setBrightness(100);
  strip.begin();
  strip.show();
  /*
   * Set Spectrum Shield pin configurations
   */
  pinMode(STROBE, OUTPUT);
  pinMode(RESET, OUTPUT);
  pinMode(DC_One, INPUT);
  pinMode(DC_Two, INPUT);
  digitalWrite(STROBE, HIGH);
  digitalWrite(RESET, HIGH);
  /*
   * Initialize Spectrum Analyzers
   */
  digitalWrite(STROBE, LOW);
  delay(1);
  digitalWrite(RESET, HIGH);
  delay(1);
  digitalWrite(STROBE, HIGH);
  delay(1);
  digitalWrite(STROBE, LOW);
  delay(1);
  digitalWrite(RESET, LOW);
  /*
   *
   */
  Serial.begin(9600);
}

/*
 * Main loop.
 *
 * Gets the values from the spectrum shield and then displays them as
 * an animated bar graph.
 */
void loop() {
  Read_Frequencies();
  if (Serial.available() > 0) {
    serialIncoming = Serial.read();
    Serial.println(serialIncoming);
  }
  switch (serialIncoming) {
    case 'b':
      bar_graph();
      break;
    case 'p':
      pulse_matrix();
      break;
  }
}

/*******************Pull frequencies from Spectrum Shield********************/

void Read_Frequencies() {
  int sumOne = 0;
  int sumTwo = 0;
  //Read frequencies for each band
  for (freq_amp = 0; freq_amp < 7; freq_amp++)
  {
    Frequencies_One[freq_amp] = analogRead(DC_One);
    sumOne += Frequencies_One[freq_amp];
    Frequencies_Two[freq_amp] = analogRead(DC_Two);
    sumTwo += Frequencies_Two[freq_amp];
    digitalWrite(STROBE, HIGH);
    digitalWrite(STROBE, LOW);
  }
  Frequencies_One[7] = sumOne / 7;
  Frequencies_Two[7] = sumTwo / 7;
}

void bar_graph() {
  matrix.fillScreen(0);
  int columnHeight = 0;
  for (int i = 0; i < matrix.width(); i++) {
    if (Frequencies_One[i] > Frequencies_Two[i]) {
      columnHeight = fscale(0, 1023, 0, 5, Frequencies_One[i], 0);
    }
    else {
      columnHeight = fscale(0, 1023, 0, 5, Frequencies_Two[i], 0);
    }
    for (int j = 0; j < columnHeight; j++) {
      matrix.drawPixel(i, j, matrix.Color(colours[i][0], colours[i][1], colours[i][2]));
    }
  }
  matrix.show();
  delay(0);
}
/*
 * Raises and lowers the brightness of the LEDs based on the frequencies
 * for each channel.
 */
void pulse_matrix() {
  for ( int q = 0; q < NUMCOLOURS; q++ ) {
    for ( int i = 0; i < NUMPIXELS; i = i + NUMCOLOURS ) {
      //float curve = read_Curve();
      float curve = -3;
      int brightness;
      if (Frequencies_One[q] > Frequencies_Two[q]) {
        brightness = fscale(0, 1023, 0, 255, Frequencies_One[q], curve);
      }
      else {
        brightness = fscale(0, 1023, 0, 255, Frequencies_Two[q], curve);
      }
      strip.setPixelColor(i + q, (brightness * colours[q][0] / 255),
                          (brightness * colours[q][1] / 255),
                          (brightness * colours[q][2] / 255));
    }
  }
  strip.show();
  delay(0);
}

