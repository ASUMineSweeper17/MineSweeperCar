#include "encoder.h"

volatile double x_distance = 0, y_distance = 0;
extern volatile float angle_yaw;
void encoderPlus(){
  if(angle_yaw > -10 && angle_yaw < 10)
    x_distance += arcLength;

  else if(angle_yaw > 80 && angle_yaw < 110)
    y_distance += arcLength;

  else if(angle_yaw > 170 && angle_yaw < 190)
    x_distance -= arcLength;

  
}  
  
void encoderMinus(){
  if(angle_yaw > -10 && angle_yaw < 10)
    x_distance -= arcLength;

  else if(angle_yaw > 80 && angle_yaw < 110)
    y_distance -= arcLength;

  else if(angle_yaw > 170 && angle_yaw < 190)
    x_distance += arcLength;
  }
