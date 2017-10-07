#ifndef NRF_H
#define NRF_H

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define ce 9
#define csn 10

void nrf_init();

void trans (char n);
char rec ();

#endif
