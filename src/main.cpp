#include <Arduino.h>
#include <Wire.h>
#include <QTRSensors.h>

QTRSensors qtr;
constexpr uint8_t SensorCount = 7;
uint16_t sensorValues[SensorCount];
constexpr uint8_t QTRPins[SensorCount] = {A0, A1, A2, A3, A4, A5, A6};


void setup() {
  Wire.begin();
  Wire.setClock(400000); //400khz clock
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  qtr.setTypeAnalog();
  qtr.setSensorPins(QTRPins, SensorCount);


}

void loop() {
  qtr.read(sensorValues, QTRReadMode::Manual);

  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  Serial.println();

}
