#ifndef NRF_H
#define NRF_H

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define ce 8
#define csn 53

void nrf_init();
void trans (String n);
char rec ();

#endif
