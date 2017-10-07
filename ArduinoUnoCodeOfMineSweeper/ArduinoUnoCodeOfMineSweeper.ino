#include "nrf.h"

char go;
char come;

void setup() {  
  Serial.begin(9600);
  nrf_init();
}

void loop (){
  if(Serial.available()>0){
    go=Serial.read();
    trans(go);
    Serial.print("Sending: ");
    Serial.println(go);
  }
  come = rec();
  if(come != ' '){
    Serial.print("Receiving: ");
    Serial.println(come);
  }
}
