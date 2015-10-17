/*
  Soil Moisture Sensor Controller

  This sketch will use an Adafruit Trinket 5v to control a soil moisture
  sensor.

  1. Turn on the sensor by setting its power pin to HIGH
  2. Read value from the sensor. Hourly checks should be sufficient for this.
  3. Write sensor value to PWM pin.
  4. Turn off the sensor by setting its power pin to LOW

  Keeping the sensor turned off between reads should

  1. Conserve power.
  2. Give the sensor a longer lifetime.
*/

const int sensorDataPin = 2;  // analogRead from this pin to get sensor value
const int sensorPowerPin = 1; // digitalWrite to this pin to turn the sensor on/of
const int dataOutputPin = 0;  // analogWrite to this pin to report sensor value
const int triggerPin = 3;

const int sensorReadFrequency = 1000;  // frequency in milliseconds to read from
// the sensor. 3600000 = 1 hour;
const int sensorReadPause = 10; // milliseconds to wait for the sensor to wake up.
// This isn't absolutely necessary, just nice to have.

void setup() {
  // set up the pins for reading and writing
  pinMode(sensorDataPin, INPUT);    // read from this pin
  pinMode(sensorPowerPin, OUTPUT);  // write to this pin
  pinMode(dataOutputPin, OUTPUT);   // write to this pin
  pinMode(triggerPin, INPUT);
  digitalWrite (sensorPowerPin, LOW);
}

void loop() {
  if (digitalRead(triggerPin) == HIGH) {
    digitalWrite(sensorPowerPin, HIGH); // Turn on the sensor
    //delay(sensorReadPause); // wait for a beat to make sure the sensor is on
    //int sensorReading = analogRead(sensorDataPin); // Read value from sensor
    int sensorReading = map(analogRead(sensorDataPin), 0, 1023, 0, 255);
    analogWrite(dataOutputPin, sensorReading); // Write value from sensor
    digitalWrite(sensorPowerPin, LOW); // Turn off the sensor
    //delay(sensorReadFrequency); // Pause to until the next reading
  }
  else if (digitalRead(triggerPin) == LOW) {
    digitalWrite (sensorPowerPin, LOW);
  }
}

