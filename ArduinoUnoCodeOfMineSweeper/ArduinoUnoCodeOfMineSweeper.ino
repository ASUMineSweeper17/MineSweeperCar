#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define ce 9
#define csn 10

/////////////////////////////////////////////////////////////////////////////////////////////
//a global variable which indicates whether the radio listening state is started or stopped
bool listenIndicator = true;
//global variables for the sent and received data:   
char go;
String come;
/////////////////////////////////////////////////////////////////////////////////////////////

const uint64_t CarPipe = 0xA2A2A2A2B4LL;
const uint64_t UnoPipe = 0xE5E5E5E5E5LL;

RF24 radio(ce,csn);

//////////////////////////////////////////////////////
//Declaring of the Transceveing Functions:
void trans (char n);
String rec ();
//////////////////////////////////////////////////////

void setup() {  
  Serial.begin(9600);
  radio.begin();
  radio.enableAckPayload();
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(UnoPipe);
  radio.openReadingPipe(1,CarPipe);
  radio.startListening();
}

void loop (){
  if(Serial.available()>0){
  go=Serial.read();
  trans(go);
  }
}


void trans (char n){
  if(listenIndicator==true){
    radio.stopListening();
    listenIndicator=false;
  }
  radio.write(&n,sizeof(n));
  /*
  bool done=false;
  while (!done){
    done = radio.write(&n,sizeof(n));
  }*/
}

String rec (){
  String n;
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
