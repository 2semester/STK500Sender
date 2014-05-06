/*
 * GccApplication1.c
 *
 * Created: 5/5/2014 16:58:09
 *  Author: Kris
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "State.h"
#include "Commands.h"


void main(void)	
{
	// initilize 
	init();
	// Globlal Variables
	int trigger=0;
	int i=0, n=0;
	char Hex[3];
	char sendCommand, sendAddress;
	char *comPtr, *addPtr;
    while(true)
    {
        switch ( true ) 
				{
		        case state:
			        case firstState() : nextState()
						break; 
					case secondState() : nextState()
						break; 
			        case thirdState() : nextState()
						break;
			        case forthState() : nextState()
						break;
					case sendData() : nextState
						break;
				}
    }
}