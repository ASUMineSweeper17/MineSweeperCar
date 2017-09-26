#include "motors.h"



extern volatile int16_t gyro_x, gyro_y, gyro_z;
extern volatile float angle_yaw;

//volatile uint64_t timer;


void motors_init(){
  pinMode(PWM1F, OUTPUT);
  pinMode(DIR1F, OUTPUT);
  pinMode(PWM2F, OUTPUT);
  pinMode(DIR2F, OUTPUT);
  pinMode(PWM1B, OUTPUT);
  pinMode(DIR1B, OUTPUT);
  pinMode(PWM2B, OUTPUT);
  pinMode(DIR2B, OUTPUT);
}



void forward(int Speed){  
  attachInterrupt(encoder_pin, encoderPlus, FALLING);
  analogWrite(PWM1F, Speed);
  analogWrite(PWM2F, Speed);
  analogWrite(PWM1B, Speed);
  analogWrite(PWM2B, Speed); 
  digitalWrite(DIR1F, HIGH);
  digitalWrite(DIR2F, HIGH);
  digitalWrite(DIR1B, HIGH);
  digitalWrite(DIR2B, HIGH);
 
  
  }


void backward(int Speed){
  attachInterrupt(encoder_pin, encoderMinus, FALLING);
  analogWrite(PWM1F, Speed);
  analogWrite(PWM2F, Speed);
  analogWrite(PWM1B, Speed);
  analogWrite(PWM2B, Speed); 
  digitalWrite(DIR1F, LOW);
  digitalWrite(DIR2F, LOW);
  digitalWrite(DIR1B, LOW);
  digitalWrite(DIR2B, LOW);

  }


void turnRight(int Speed){
  
  //detachInterrupt(encoder_pin);
  Timer1.attachInterrupt(integration, 10000);
  
  analogWrite(PWM1F, Speed);
  analogWrite(PWM2F, Speed);
  analogWrite(PWM1B, Speed);
  analogWrite(PWM2B, Speed); 
  digitalWrite(DIR1F, LOW);
  digitalWrite(DIR2F, HIGH);
  digitalWrite(DIR2B, LOW);
  digitalWrite(DIR1B, HIGH);
  
   }


void turnLeft(int Speed){
  
  //detachInterrupt(encoder_pin);
  Timer1.attachInterrupt(integration, 10000);
  
  analogWrite(PWM1F, Speed);
  analogWrite(PWM2F, Speed);
  analogWrite(PWM1B, Speed);
  analogWrite(PWM2B, Speed); 
  digitalWrite(DIR1F, HIGH);
  digitalWrite(DIR2F, LOW);
  digitalWrite(DIR2B, HIGH);
  digitalWrite(DIR1B, LOW);

  }


void stopp(){
  
  detachInterrupt(encoder_pin);
  Timer1.detachInterrupt();
  
  digitalWrite(PWM1F, LOW);
  digitalWrite(PWM1B, LOW);
  digitalWrite(PWM2F, LOW);
  digitalWrite(PWM2B, LOW);
  }
