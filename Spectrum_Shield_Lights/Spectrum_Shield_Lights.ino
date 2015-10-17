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
This code is beerware; if you see me (or any other SparkFun employee)
at the local, and you've found our code helpful, please buy us a round!
Distributed as-is; no warranty is given.
*********************************************************************************/

//Declare Spectrum Shield pin connections
#define STROBE 4
#define RESET 6
#define DC_One A0
#define DC_Two A1

//Define LED connections on the shield
//int LED[] = {3, 5, 6, 9, 10, 11};
//int LED[] = {3, 5, 7, 9, 10, 11};
int LED[] = {2, 3, 5, 7, 8, 9, 10};
int freqs[] = {0, 1, 2, 3, 4, 5, 6};

//Define spectrum variables
int freq_amp;
int Frequencies_One[7];
int Frequencies_Two[7];
int i;
int offset = 85;
int delayMicros = 0;
int buttonPin = 11;
int ledState = 0;
int buttonState = 0;

/********************Setup Loop*************************/

void setup() {
  //Serial.begin(9600);
  //Set LED pin configurations
  pinMode(buttonPin, INPUT);
  for (i = 0; i < 7; i++)
  {
    pinMode(LED[i], OUTPUT);
    digitalWrite(LED[i], LOW);
  }
  for (i = 0; i < 7; i++)
  {
    digitalWrite(LED[i], HIGH);
    delay(100);
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
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    if (ledState == 0) { 
      ledState = 1; 
    }
    else { 
      ledState = 0; 
    }
  }
  Get_Delay();
  switch (ledState) {
    case 0:
      Read_Frequencies();
      Graph_Frequencies();
      delay(delayMicros);
      break;
    case 1:
      Theatre_Chase();
      break;
  }
}

void Get_Delay() {
  delayMicros = map(analogRead(5), 0, 1024, 0, 128);
}

/*******************Pull frequencies from Spectrum Shield********************/
void Read_Frequencies() {
  String output;
  //Read frequencies for each band
  for (freq_amp = 0; freq_amp < 7; freq_amp++)
  {
    Frequencies_One[freq_amp] = analogRead(DC_One);
    //output = output + Frequencies_One[freq_amp] + '\t';
    Frequencies_Two[freq_amp] = analogRead(DC_Two);
    //output = output + Frequencies_Two[freq_amp] + '\t';
    digitalWrite(STROBE, HIGH);
    digitalWrite(STROBE, LOW);
  }
  //Serial.println(output);
}

/*******************Light LEDs based on frequencies*****************************/
void Graph_Frequencies() {
  int brightness = 0;
  for ( i = 0; i < 7; i++)
  {
    if (Frequencies_Two[freqs[i]] > Frequencies_One[freqs[i]]) {
      if (Frequencies_Two[freqs[i]] < offset) {
        brightness = 0;
      }
      else {
        brightness = map(Frequencies_Two[freqs[i]], 0, 1023, 0, 255);
      }
      analogWrite(LED[i], brightness);
    }
    else {
      if (Frequencies_One[freqs[i]] < offset) {
        brightness = 0;
      }
      else {
        brightness = map(Frequencies_One[freqs[i]], 0, 1023, 0, 255);
      }
      analogWrite(LED[i], brightness);
    }
  }
}

void Theatre_Chase() {
  for (int q = 0; q < 3; q++) {
    for (int j = 0; j < 7; j += 3) {
      analogWrite(LED[j + q], 128);
    }
    delay(delayMicros);
    for (int j = 0; j < 7; j += 3) {
      analogWrite(LED[j + q], 16);
    }
  }
}
