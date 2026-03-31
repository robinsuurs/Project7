#include <Arduino.h>
#include <Wire.h>
#include "FastIMU.h"



#define IMU1_ADDRESS 0x68    //Change to the address of the IMU
#define IMU2_ADDRESS 0x69
#define PERFORM_CALIBRATION //Comment to disable startup calibration
MPU6886 IMU1;               //Change to the name of any supported IMU!
MPU6886 IMU2;
calData calib1 = { 0 };  //Calibration data
calData calib2 = { 0 };
AccelData accelData1;    //Sensor data
AccelData accelData2;
GyroData gyroData1;
GyroData gyroData2;


void setup() {
  Wire.begin();
  Wire.setClock(400000); //400khz clock
  Serial.begin(9600);
  while (!Serial) {
    ;
  }

  int err = IMU1.init(calib1, IMU1_ADDRESS);
  err = IMU2.init(calib2, IMU2_ADDRESS);

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

  IMU1.calibrateAccelGyro(&calib1);
  IMU2.calibrateAccelGyro(&calib2);

  Serial.println("Calibration done!");
  Serial.println("Accel biases X/Y/Z: ");
  Serial.print(calib1.accelBias[0]);
  Serial.print(", ");
  Serial.print(calib1.accelBias[1]);
  Serial.print(", ");
  Serial.println(calib1.accelBias[2]);

  Serial.print(calib2.accelBias[0]);
  Serial.print(", ");
  Serial.print(calib2.accelBias[1]);
  Serial.print(", ");
  Serial.println(calib2.accelBias[2]);

  Serial.println("Gyro biases X/Y/Z: ");
  Serial.print(calib1.gyroBias[0]);
  Serial.print(", ");
  Serial.print(calib1.gyroBias[1]);
  Serial.print(", ");
  Serial.println(calib1.gyroBias[2]);

  Serial.print(calib2.gyroBias[0]);
  Serial.print(", ");
  Serial.print(calib2.gyroBias[1]);
  Serial.print(", ");
  Serial.println(calib2.gyroBias[2]);

  delay(5000);
  IMU1.init(calib1, IMU1_ADDRESS);
  IMU2.init(calib2, IMU2_ADDRESS);
#endif

  err = IMU1.setGyroRange(500);      //USE THESE TO SET THE RANGE, IF AN INVALID RANGE IS SET IT WILL RETURN -1
  err = IMU1.setAccelRange(2);       //THESE TWO SET THE GYRO RANGE TO ±500 DPS AND THE ACCELEROMETER RANGE TO ±2g
  err = IMU2.setGyroRange(500);
  err = IMU2.setAccelRange(2);

  if (err != 0) {
    Serial.print("Error Setting range: ");
    Serial.println(err);
    while (true) {
      ;
    }
  }
}

void loop() {

  IMU1.update();                     //Read IMU data from I2C bus save in -> this->accel this->gyro
  IMU2.update();

  IMU1.getAccel(&accelData1);         //Write IMU.accel to accelData
  IMU2.getAccel(&accelData2);

  ///Print accel data
  Serial.println("");
  Serial.print(accelData1.accelX);
  Serial.print("\t");
  Serial.print(accelData1.accelY);
  Serial.print("\t");
  Serial.print(accelData1.accelZ);
  Serial.print("\t");

//  Serial.println("Accel2: ");
  Serial.print(accelData2.accelX);
  Serial.print("\t");
  Serial.print(accelData2.accelY);
  Serial.print("\t");
  Serial.print(accelData2.accelZ);
  Serial.print("\t");


/*
  IMU1.getGyro(&gyroData1);           //Write IMU.gyro to gyroData
  IMU2.getGyro(&gyroData2);

  ///Print gyro data
  Serial.print(gyroData1.gyroX);
  Serial.print("\t");
  Serial.print(gyroData1.gyroY);
  Serial.print("\t");
  Serial.print(gyroData1.gyroZ);
  Serial.print("\t");
  Serial.print(gyroData2.gyroX);
  Serial.print("\t");
  Serial.print(gyroData2.gyroY);
  Serial.print("\t");
  Serial.print(gyroData2.gyroZ);
*/

}
