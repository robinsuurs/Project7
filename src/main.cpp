#include <Arduino.h>
#include <Wire.h>
#include <QTRSensors.h>

QTRSensors qtr;
constexpr uint8_t SensorCount = 7;
uint16_t sensorValues[SensorCount];
constexpr uint8_t QTRPins[SensorCount] = {A0, A1, A2, A3, A4, A5, A6};


void setup() {

  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  qtr.setTypeAnalog();
  qtr.setSensorPins(QTRPins, SensorCount);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // turn on Arduino's LED to indicate we are in calibration mode

  // analogRead() takes about 0.1 ms on an AVR.
  // 0.1 ms per sensor * 4 samples per sensor read (default) * 7 sensors
  // * 10 reads per calibrate() call = ~28 ms per calibrate() call.
  // Call calibrate() 200 times to make calibration take about 5 seconds.
  for (uint8_t i = 0; i < 200; i++)
  {
    qtr.calibrate();
  }
  digitalWrite(LED_BUILTIN, LOW); // turn off Arduino's LED to indicate we are through with calibration

  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(qtr.calibrationOn.minimum[i]);
    Serial.print(' ');
  }
  Serial.println();

  // print the calibration maximum values measured when emitters were on
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(qtr.calibrationOn.maximum[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();
  delay(1000);

}

void loop() {

  // read calibrated sensor values and obtain a measure of the line position
  // from 0 to 7000
  qtr.readLineBlack(sensorValues, QTRReadMode::On);

  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  Serial.println();

}
