#include "nrf.h"

bool listenIndicator =true;

const uint64_t CarPipe = 0xA2A2A2A2B4LL;
const uint64_t UnoPipe = 0xE5E5E5E5E5LL;

RF24 radio(ce,csn);

void nrf_init(){
  radio.begin();
  radio.setChannel(125);
  radio.openWritingPipe(UnoPipe);
  radio.openReadingPipe(1,CarPipe);
  radio.enableAckPayload();
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();
}

void trans (char n){
  if(listenIndicator==true){
    radio.stopListening();
    listenIndicator=false;
  }
  radio.write(&n,sizeof(n));
  /*bool done=false;
    while(!done){
      done= radio.write(&n,sizeof(n));
    }*/
}

char rec (){
  char n=' ';
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
  else {
    return n;
  }
}
