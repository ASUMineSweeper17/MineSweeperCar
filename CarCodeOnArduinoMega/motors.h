#ifndef MOTORS_H
#define MOTORS_H

#include <Arduino.h>
#include "MPU.h"
#include "TimerOne.h"

#define PWM1F   24      //forward right
#define DIR1F   25
#define DIR2F   22      //forward left
#define PWM2F   23


#define PWM1B   51       //backword left
#define DIR1B   50
#define DIR2B   52      //backword right
#define PWM2B   53

#define encoder_pin 0                              //0 interrupt is pin number 2 in mega, 2 is 2 in due 

void motors_init();                               //Make sure that motor pins are output
void forward(int Speed);
void backward(int Speed);
void turnRight(int Speed);
void turnLeft(int Speed);
void stopp();

extern void encoderPlus();
extern void encoderMinus();
extern void integration();

#endif
