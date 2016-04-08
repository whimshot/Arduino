/*
 * Raises and lowers the brightness of the LEDs based on the frequencies
 * for each channel.
 */
void Pulse_Frequencies() {
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
  int delayTime = read_Delay(0, 128);
  delay(0);
}



