#ifndef  MAIN_H
#define MAIN_H

#define ARRAY 4
volatile uint8_t flag = 1; // den første interrupt er et 1 bit. 
int failsafe = 0;
int sendcounter = 0;
int ready = 0;
char Buffer[4] = {'\0'};
char DataBuffer[6] = {'\0'};
#endif 