/*
 * A beginning of disco lights
 */

#include "Adafruit_WS2801.h"
#include "SPI.h"

uint8_t lefStripDataPin  = 11;    // Yellow wire on Adafruit Pixels
uint8_t leftStripClockPin = 13;    // Green wire on Adafruit Pixels

//Adafruit_WS2801 strip = Adafruit_WS2801(25, lefStripDataPin, leftStripClockPin);
Adafruit_WS2801 strip = Adafruit_WS2801(25);

/*
 * The following pins are for controlling the Spectrum Shield
 */
#define STROBE 4
#define RESET 6
#define DC_One A0
#define DC_Two A1

#define DELAY_Pin A5

#define NUMCOLOURS      7

#define CURVE -3

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

/*
 * Setup the following:
 * 1. NEO Pixels
 * 2. Spectrum Shield
 * 3. Delay pin
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
}


/*
 * Main loop. Runs the appropriate function(s) based on the mode
 * selection.
 */
void loop() {
  Read_Frequencies();
  Pulse_Frequencies();
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


