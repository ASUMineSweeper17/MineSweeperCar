#ifndef MPU_H
#define MPU_H

#include <Wire.h>
#include <Arduino.h>

void setup_mpu_6050_registers();
void read_gyro_6050_data();
void read_acc_6050_data();
void gyro_error();
void initial_angles();
void processing();
void integration();













#endif
