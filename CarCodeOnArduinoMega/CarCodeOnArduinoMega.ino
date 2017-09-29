#include "motors.h"
#include "encoder.h"
#include "MPU.h"
#include "Mapping.h"
#include "nrf.h"

//////////////////////////////////////////////////////
//communication
String go;
char come;
//////////////////////////////////////////////////////
    
extern double x_distance;
extern double y_distance;
extern volatile float angle_yaw;

uint16_t Speed = 150; 

void setup() {
//Communication Setup:
  nrf_init();
///////////////////////////////////////////////////////
  
  motors_init();

  setup_mpu_6050_registers();
  gyro_error();
}

void loop() {
  
    come=rec();
    
    switch (come){          
       case '1':{
         forward(Speed);
         break;
       }
       
       case '2':{
         turnRight(Speed);
         break;
       }
       
       case '4':{
         turnLeft(Speed);
         break;
       }
       
       case '5':{
         backward(Speed);
         break;
       }
       
       case '3':{
         stopp();
         break;   
       }
    }
}
