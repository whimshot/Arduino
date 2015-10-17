/*
 * Raises and lowers the brightness of the LEDs based on the frequencies
 * for each channel.
 */
void Pulse_Frequencies() {
  int brightness = 0;
  for ( int i = 0; i < NUMPIXELS; i++)
  {
    int channelID = i % NUMCOLOURS;
    if (Frequencies_Two[channelID] > Frequencies_One[channelID]) {
      if (Frequencies_Two[channelID] < offset) {
        brightness = 0;
      }
      else {
        //brightness = map(Frequencies_Two[channelID], 0, 1023, 0, 255);
        brightness = fscale(0, 1023, 0, 255, Frequencies_Two[channelID], CURVE);
      }
      strip.setPixelColor(i, (brightness * colours[channelID][0] / 255), 
        (brightness * colours[channelID][1] / 255), 
        (brightness * colours[channelID][2] / 255));
      strip.show();
    }
    else {
      if (Frequencies_One[channelID] < offset) {
        brightness = 0;
      }
      else {
        //brightness = map(Frequencies_Two[channelID], 0, 1023, 0, 255);
        brightness = fscale(0, 1023, 0, 255, Frequencies_Two[channelID], CURVE);
      }
      strip.setPixelColor(i, (brightness * colours[channelID][0] / 255), 
        (brightness * colours[channelID][1] / 255), 
        (brightness * colours[channelID][2] / 255));
      strip.show();
    }
  }
  int delayTime = analogRead(DELAY_Pin);
  delayTime = map(delayTime, 0, 1023, 15, 127);
  delay(delayTime);
}

/*
 * Changes the colour of the LEDs based on the frequencies
 * for each channel.
 */
void Colour_Frequencies() {
  int colour;
  for ( int i = 0; i < NUMPIXELS; i++)
  {
    int channelID = i % NUMCOLOURS;
    if (Frequencies_Two[channelID] > Frequencies_One[channelID]) {
      colour = Frequencies_Two[channelID];
      strip.setPixelColor(i, Wheel(colour % 255));
      strip.show();
    }
    else {
      colour = Frequencies_One[channelID];
      strip.setPixelColor(i, Wheel(colour % 255));
      strip.show();
    }
  }
  int delayTime = analogRead(DELAY_Pin);
  delayTime = map(delayTime, 0, 1023, 127, 255);
  delay(delayTime);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

/*
 * Cycles through the full color spectrum available distributed throughout
 * the full strand. Reads a delay for the cycle from a potentiometer. 
 * Currently not in use.
 */
void rainbowCycle() {
  uint16_t i, j;
  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    int delayTime = analogRead(DELAY_Pin);
    delayTime = map(delayTime, 0, 1023, 1, 16);
    delay(delayTime);
  }
}

/*
 * Theatre-style crawling lights.
 */
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
     
      delay(wait);
     
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

/*
 * Theatre-style crawling lights with rainbow effect
 */
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        strip.show();
       
        delay(wait);
       
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}

/*
 * Input a value 0 to 255 to get a color value.
 * The colours are a transition r - g - b - back to r.
 */
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

