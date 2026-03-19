#include <Arduino.h>
#include <Wire.h>

#include "I2C_MPU6886.h"


I2C_MPU6886 imu(I2C_MPU6886_DEFAULT_ADDRESS, Wire);

void setup() {
// write your initialization code here

    Serial.begin(115200);
    delay(1000);

    Wire.begin();
    imu.begin();


}

void loop() {
// write your code here
    float ax;
    float ay;
    float az;
    float gx;
    float gy;
    float gz;
    float t;

    imu.getAccel(&ax, &ay, &az);
    imu.getGyro(&gx, &gy, &gz);
    imu.getTemp(&t);

    Serial.print("ax: ");
    Serial.print(ax);
    Serial.print(" ");
    Serial.print("ay: ");
    Serial.print(ay);
    Serial.print(" ");
    Serial.print("az: ");
    Serial.print(az);
    Serial.println(" ");
    Serial.print("gx: ");
    Serial.print(gx);
    Serial.print(" ");
    Serial.print("gy: ");
    Serial.print(gy);
    Serial.print(" ");
    Serial.print("gz: ");
    Serial.print(gz);
    Serial.print(" ");
    Serial.print("t: ");
    Serial.print(t);
    Serial.println(" ");


    delay(100);
}