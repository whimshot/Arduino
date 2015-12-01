/*
 * A beginning of disco lights
 */

/*
 * Adafruit NeoPixel initialization values
 */
#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define NEO_PIN  12

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      150
/*
 *  Parameter 1 = number of pixels in strip
 *  Parameter 2 = Arduino pin number (most are valid)
 *  Parameter 3 = pixel type flags, add together as needed:
 *    NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
 *    NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
 *    NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
 *    NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
 */

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, NEO_PIN, NEO_GRB + NEO_KHZ800);

/*
 * The following pins are for controlling the Spectrum Shield
 */
#define STROBE 4
#define RESET 6
#define DC_One A0
#define DC_Two A1

#define DELAY_Pin A5
#define CURVE_Pin A4

#define NUMCOLOURS      7

/*
 * Define the colour values that we will be using. Aiming for ROY G BIV
 * or the nearest equivalent.
 */
int colours[][3] = {
  { 255, 0 , 0 },   // Red
  { 255, 128, 0 },   // Orange
  { 128, 128, 0 },  // Yellow
  { 0, 128, 0 },    // Green
  { 0, 64, 255 },    // Blue
  { 64, 0, 255 },   // Indigo
  { 255, 0, 255 },  // Violet
  { 128, 128, 128}, // White
};

// Define some Spectrum Shield variables
int freq_amp;
int Frequencies_One[7];
int Frequencies_Two[7];
int offset = 0;

volatile int modeState = 0;

/*
 * Setup the following:
 * 1. NEO Pixels
 * 2. Spectrum Shield
 * 3. Delay pin
 * 4. Interrupt handler
 */

void setup() {
  /*
   * NEO Pixels
   */
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

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
   * Set up delay pin
   */
  pinMode(DELAY_Pin, INPUT);
  
  attachInterrupt(0, modeChange, CHANGE);
}

/*
 * Main loop. Runs the appropriate function(s) based on the mode
 * selection.
 */
void loop() {
  //  if (modeState == 0) {
  //    Read_Frequencies();
  //    Pulse_Frequencies();
  //  }
  //  else {
  //    rainbowCycle(8);
  //  }
  //
  Read_Frequencies();
  Pulse_Frequencies();
}

void modeChange() {
  if (modeState == 0) {
    modeState++;
  }
  else {
    modeState = 0;
  }
}

/*******************Pull frequencies from Spectrum Shield********************/
void Read_Frequencies() {
  String output;
  //Read frequencies for each band
  for (freq_amp = 0; freq_amp < 7; freq_amp++)
  {
    Frequencies_One[freq_amp] = analogRead(DC_One);
    Frequencies_Two[freq_amp] = analogRead(DC_Two);
    digitalWrite(STROBE, HIGH);
    digitalWrite(STROBE, LOW);
  }
}

int read_Delay(float delayMin, float delayMax) {
  int delayTime = analogRead(DELAY_Pin);
  delayTime = map(delayTime, 0, 1023, delayMin, delayMax);
  return delayTime;
}

float read_Curve() {
  float curve = analogRead(CURVE_Pin);
  curve = map(curve, 0, 1023, -10, 10);
  return curve;
}
