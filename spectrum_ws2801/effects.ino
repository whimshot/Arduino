/*
 * A collection of subroutines for manipulating the color and brightness of NeoPixels.
 *
 */

/*
 * Raises and lowers the brightness of the LEDs based on the frequencies
 * for each channel.
 */
void Pulse_Frequencies() {
  for ( int q = 0; q < NUMCOLOURS; q++ ) {
    for ( int i = 0; i < strip.numPixels(); i = i + NUMCOLOURS ) {
      float curve = read_Curve();
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
  int delayTime = read_Delay(32, 256);
  delay(delayTime);
}

void rainbow(uint8_t wait) {
  int i, j;

  for (j = 0; j < 256; j++) {   // 3 cycles of all 256 colors in the wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel( (i + j) % 255));
    }
    strip.show();   // write all the pixels out
    delay(wait);
  }
}

// Slightly different, this one makes the rainbow wheel equally distributed
// along the chain
void rainbowCycle(uint8_t wait) {
  int i, j;

  for (j = 0; j < 256 * 5; j++) {   // 5 cycles of all 25 colors in the wheel
    for (i = 0; i < strip.numPixels(); i++) {
      // tricky math! we use each pixel as a fraction of the full 96-color wheel
      // (thats the i / strip.numPixels() part)
      // Then add in j which makes the colors go around per pixel
      // the % 96 is to make the wheel cycle around
      strip.setPixelColor(i, Wheel( ((i * 256 / strip.numPixels()) + j) % 256) );
    }
    if (modeState == 0) {
      break;
    }
    strip.show();   // write all the pixels out
    int delayTime = read_Delay(4, 16);
    delay(delayTime);
    //delay(wait);
  }
}

// fill the dots one after the other with said color
// good for testing purposes
void colorWipe(uint32_t c, uint8_t wait) {
  int i;

  for (i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

/* Helper functions */

// Create a 24 bit color value from R,G,B
uint32_t Color(byte r, byte g, byte b)
{
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}

//Input a value 0 to 255 to get a color value.
//The colours are a transition r - g -b - back to r
uint32_t Wheel(byte WheelPos)
{
  if (WheelPos < 85) {
    return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
