/******************************************************************************
SparkFun Spectrum Shield PWM Demo
Toni Klopfenstein @ SparkFun Electronics
February 2015
https://github.com/sparkfun/Spectrum_Shield

This sketch shows the basic functionality of the Spectrum Shield, working with a basic RGB LED Matrix.

The Spectrum Shield code is based off of the original demo sketch by Ben Moyes @Bliptronics.
This sketch is available in the Spectrum Shield repository.

Development environment specifics:
Developed in Arduino 1.6.

This code is beerware; if you see me (or any other SparkFun employee) at the local, and you've found our code helpful, please buy us a round!
Distributed as-is; no warranty is given.
*********************************************************************************/

//Declare Spectrum Shield pin connections
#define STROBE 4
#define RESET 6
#define DC_One A0
#define DC_Two A1

const int SIGNAL_HIGH = 1024;
const int SIGNAL_LOW = 0;
const int BRIGHTNESS_HIGH = 255;
const int BRIGHTNESS_LOW = 0;
const int INTERVAL_PIN = 5;

//Define LED connections on the shield
int LED[] = {3, 5, 6, 9, 10, 11, 13};

//Define spectrum variables
int freq_amp;
int Frequencies_One[7];
int Frequencies_Two[7];
int i;

/********************Setup Loop*************************/
void setup() {
  Serial.begin(9600);
  //Set LED pin configurations
  for (i = 0; i < 7; i++)
  {
    pinMode(LED[i], OUTPUT);
    digitalWrite(LED[i], LOW);
  }

  //Set Spectrum Shield pin configurations
  pinMode(STROBE, OUTPUT);
  pinMode(RESET, OUTPUT);
  pinMode(DC_One, INPUT);
  pinMode(DC_Two, INPUT);
  digitalWrite(STROBE, HIGH);
  digitalWrite(RESET, HIGH);

  //Initialize Spectrum Analyzers
  digitalWrite(STROBE, LOW);
  delay(1);
  digitalWrite(RESET, HIGH);
  delay(1);
  digitalWrite(STROBE, HIGH);
  delay(1);
  digitalWrite(STROBE, LOW);
  delay(1);
  digitalWrite(RESET, LOW);
}


/**************************Main Function Loop*****************************/
void loop() {

  Read_Frequencies();
  Graph_Frequencies();
  //delay(50);

}


/*******************Pull frequencies from Spectrum Shield********************/
void Read_Frequencies() {
  String output;
  //Read frequencies for each band
  for (freq_amp = 0; freq_amp < 7; freq_amp++)
  {
    Frequencies_One[freq_amp] = analogRead(DC_One);
    output = output + Frequencies_One[freq_amp] + '\t';
    Frequencies_Two[freq_amp] = analogRead(DC_Two);
    output = output + Frequencies_Two[freq_amp] + '\t';
    digitalWrite(STROBE, HIGH);
    digitalWrite(STROBE, LOW);
  }
  Serial.println(output);
}

/*******************Light LEDs based on frequencies*****************************/
void Graph_Frequencies() {
  int interval = map(analogRead(INTERVAL_PIN), 0, 1024, 0, 256);
  //Serial.println(interval);
  delay(interval);
  for ( i = 0; i < 7; i++)
  {
    if (Frequencies_Two[i] > Frequencies_One[i]) {
      int brightness = map(Frequencies_Two[i], SIGNAL_LOW, SIGNAL_HIGH, BRIGHTNESS_LOW, BRIGHTNESS_HIGH);
      analogWrite(LED[i], brightness);
    }
    else {
      int brightness = map(Frequencies_One[i], SIGNAL_LOW, SIGNAL_HIGH, BRIGHTNESS_LOW, BRIGHTNESS_HIGH);
      analogWrite(LED[i], brightness);
    }
  }
}
