#include "MPU.h"

volatile int16_t gyro_x, gyro_y, gyro_z;
int32_t gyro_z_cal = 0;

volatile float angle_yaw = 0;




void setup_mpu_6050_registers(){
  Wire.begin();
  
  Wire.beginTransmission(0x68);                                        //Start communicating with the MPU-6050
  
  Wire.write(0x6B);                                                    //Send the requested starting register
  Wire.write(0x00);                                                    //Set the requested starting register
  
  Wire.endTransmission();                                              //End the transmission
  //Configure the accelerometer (+/-8g)
  Wire.beginTransmission(0x68);                                        //Start communicating with the MPU-6050
  Wire.write(0x1C);                                                    //Send the requested starting register
  Wire.write(0x10);                                                    //Set the requested starting register
  Wire.endTransmission();                                              //End the transmission
  //Configure the gyro (500dps full scale)
  Wire.beginTransmission(0x68);                                        //Start communicating with the MPU-6050
  Wire.write(0x1B);                                                    //Send the requested starting register
  Wire.write(0x08);                                                    //Set the requested starting register
  Wire.endTransmission();
}


void read_gyro_6050_data(){                                            //Subroutine for reading the raw gyro and accelerometer data
  Wire.beginTransmission(0x68);                                        //Start communicating with the MPU-6050
  Wire.write(0x43);                                                    //Send the requested starting register
  Wire.endTransmission();                                              //End the transmission
  Wire.requestFrom(0x68,6);                                           //Request 14 bytes from the MPU-6050
  while(Wire.available() < 6);                                        //Wait until all the bytes are received
  gyro_x = Wire.read()<<8|Wire.read();                                 //Add the low and high byte to the gyro_x variable
  gyro_y = Wire.read()<<8|Wire.read();                                 //Add the low and high byte to the gyro_y variable
  gyro_z = Wire.read()<<8|Wire.read();                                 //Add the low and high byte to the gyro_z variable

}




void gyro_error(){

  for (int cal_int = 0; cal_int < 500 ; cal_int ++){                  //Run this code 2000 times
    read_gyro_6050_data();                                              //Read the raw acc and gyro data from the MPU-6050
  
    gyro_z_cal += gyro_z;                                              //Add the gyro z-axis offset to the gyro_z_cal variable
    delay(3);                                                         //Delay 3ms to simulate the 250Hz program loop

  }
  gyro_z_cal /= 500;
}

void processing(){
  read_gyro_6050_data();
  gyro_z -= gyro_z_cal;

  }

void integration(){
  processing();
  if(abs(gyro_z) > 50)
    angle_yaw += (gyro_z * 0.0001526);
}
