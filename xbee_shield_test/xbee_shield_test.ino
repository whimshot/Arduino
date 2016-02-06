/*****************************************************************
XBee_Serial_Passthrough.ino

Set up a software serial port to pass data between an XBee Shield
and the serial monitor.

Hardware Hookup:
  The XBee Shield makes all of the connections you'll need
  between Arduino and XBee. If you have the shield make
  sure the SWITCH IS IN THE "DLINE" POSITION. That will connect
  the XBee's DOUT and DIN pins to Arduino pins 2 and 3.

*****************************************************************/

#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

// We'll use SoftwareSerial to communicate with the XBee:
#include <SoftwareSerial.h>

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

// XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)
SoftwareSerial XBee(2, 3); // RX, TX


void setup() {
  // Set up both ports at 9600 baud. This value is most important
  // for the XBee. Make sure the baud rate matches the config
  // setting of your XBee.
  XBee.begin(9600);
  Serial.begin(9600);
  matrix.begin(0x70);  // pass in the address
}

void loop() {
  String incomingStr = "";
  while (XBee.available() > 0) {
    // If data comes in from XBee, send it out to serial monitor
    //Serial.write(XBee.read());
    char incoming = XBee.read();
    Serial.print(incoming);
    incomingStr += incoming;
  }
  matrix.setTextSize(1);
  matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix.setTextColor(LED_ON);
  int incomingLength = 0 - (incomingStr.length() * 8);
  for (int8_t x = 0; x >= incomingLength; x--) {
    matrix.clear();
    matrix.setCursor(x, 0);
    matrix.print(incomingStr);
    matrix.writeDisplay();
    delay(64);
  }
}

