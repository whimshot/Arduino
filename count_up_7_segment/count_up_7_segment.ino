

//Pin connected to latch pin (ST_CP) of 74HC595
const int latchPin = 8;
//Pin connected to clock pin (SH_CP) of 74HC595
const int clockPin = 12;
//Pin connected to Data in (DS) of 74HC595
const int dataPin = 7;

int delayTime = 0;

// numerals 0 - 9 in byte format for shift register output to a 
// 7 segment display
byte numerals[] = { B01011111, B00000110, B00111011, B00101111, 
                    B01100110, B01101101, B01111101, B00000111, 
                    B01111111, B01101111, B01110111, B01011001,
                    B01111001, B01110001, B01110110, B00011110,
                    B01011000, B01110011, B01011110};

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
}

void loop() {
  byte bitsToSend = 0;
  for(int j = 0; j < 19; j++ ) {
    // select the numeral to display on the 7 sgement LDED
    bitsToSend = numerals[j];
    digitalWrite(latchPin, LOW);
    digitalWrite(dataPin, bitsToSend);  
    // shift the bits out:
    shiftOut(dataPin, clockPin, MSBFIRST, bitsToSend);
    // turn on the output so the LEDs can light up:
    digitalWrite(latchPin, HIGH);
    delay(delayTime);
  }
  delayTime++;
}
