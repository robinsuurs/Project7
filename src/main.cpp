#include <Arduino.h>
#include <Wire.h>
#include "FastIMU.h"



#define IMU_ADDRESS 0x68    //Change to the address of the IMU
#define PERFORM_CALIBRATION //Comment to disable startup calibration
MPU6886 IMU;               //Change to the name of any supported IMU!

calData calib = { 0 };  //Calibration data
AccelData accelData;    //Sensor data
GyroData gyroData;
MagData magData;

void setup() {
  Wire.begin();
  Wire.setClock(400000); //400khz clock
  Serial.begin(9600);
  while (!Serial) {
    ;
  }

  int err = IMU.init(calib, IMU_ADDRESS);
  if (err != 0) {
    Serial.print("Error initializing IMU: ");
    Serial.println(err);
    while (true) {
      ;
    }
  }

#ifdef PERFORM_CALIBRATION
  Serial.println("FastIMU calibration & data example");

  delay(5000);
  Serial.println("Keep IMU level.");
  delay(5000);
  IMU.calibrateAccelGyro(&calib);
  Serial.println("Calibration done!");
  Serial.println("Accel biases X/Y/Z: ");
  Serial.print(calib.accelBias[0]);
  Serial.print(", ");
  Serial.print(calib.accelBias[1]);
  Serial.print(", ");
  Serial.println(calib.accelBias[2]);
  Serial.println("Gyro biases X/Y/Z: ");
  Serial.print(calib.gyroBias[0]);
  Serial.print(", ");
  Serial.print(calib.gyroBias[1]);
  Serial.print(", ");
  Serial.println(calib.gyroBias[2]);

  delay(5000);
  IMU.init(calib, IMU_ADDRESS);
#endif

  err = IMU.setGyroRange(500);      //USE THESE TO SET THE RANGE, IF AN INVALID RANGE IS SET IT WILL RETURN -1
  err = IMU.setAccelRange(2);       //THESE TWO SET THE GYRO RANGE TO ±500 DPS AND THE ACCELEROMETER RANGE TO ±2g

  if (err != 0) {
    Serial.print("Error Setting range: ");
    Serial.println(err);
    while (true) {
      ;
    }
  }
}

void loop() {

  IMU.update();                     //Read IMU data from I2C bus save in -> this->accel this->gyro

  IMU.getAccel(&accelData);         //Write IMU.accel to accelData

  ///Print accel data
  Serial.print(accelData.accelX);
  Serial.print("\t");
  Serial.print(accelData.accelY);
  Serial.print("\t");
  Serial.print(accelData.accelZ);
  Serial.print("\t");


  IMU.getGyro(&gyroData);           //Write IMU.gyro to gyroData

  ///Print gyro data
  Serial.print(gyroData.gyroX);
  Serial.print("\t");
  Serial.print(gyroData.gyroY);
  Serial.print("\t");
  Serial.print(gyroData.gyroZ);

  if (IMU.hasTemperature()) {
	  Serial.print("\t");
	  Serial.println(IMU.getTemp());
  }

  delay(50);
}
