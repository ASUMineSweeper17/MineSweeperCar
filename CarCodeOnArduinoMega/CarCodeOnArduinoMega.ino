#include "motors.h"
#include "encoder.h"
#include "MPU.h"
#include "Mapping.h"
//////////////////////////////////////////////////////
//communication
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define ce 7
#define csn 8

bool listenIndicator =true;
String go;
char come='3';

void trans (String n);
char rec ();

const uint64_t CarPipe = 0xA2A2A2A2B4LL;
const uint64_t UnoPipe = 0xE5E5E5E5E5LL;

RF24 radio(ce,csn);
///////////////////////////////////////////////////////

extern double x_distance;
extern double y_distance;
extern volatile float angle_yaw;

uint16_t Speed = 150; 

void setup() {

///////////////////////////////////////////////////////
//Communication Setup
  radio.begin();
  radio.enableAckPayload();
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(CarPipe);
  radio.openReadingPipe(1,UnoPipe);
  radio.startListening();
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

    Serial.print(x_distance);
    Serial.print("   ");
    Serial.print(y_distance);
    Serial.print("       ");
    Serial.println(angle_yaw);
    delay(50);
}

////////////////////////////////////////////
//Communication Functions:
void trans (String n){
  if(listenIndicator==true){
    radio.stopListening();
    listenIndicator=false;
  }
radio.write(&n,sizeof(n));
  bool done=false;
  while (!done){
    done = radio.write(&n,sizeof(n));
  }
}

char rec (){
  char n;
  if(listenIndicator==false){
    radio.startListening();
    listenIndicator=true;
  }
  if(radio.available()){
    bool done=false;
    while(!done){
      done=radio.read(&n,sizeof(n));
    }
    return n;
  }
}
////////////////////////////////////////////
