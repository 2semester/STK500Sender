/*
 * uart_test.c
 * *bruges ikke i f�rdig version men bruges til at teste om vi kan sende data
 * Created: 20-05-2014 21:38:28
 *  Author: kristoffer
 */ 
#include <avr/io.h>
#include <stdlib.h>
#include "uart_test.h"
#include "uart_int.h"
/*************************************************************************
Awaits transmitter-register ready.
Then it send the character.
Parameter :
	Tegn : Character for sending. 
*************************************************************************/
void SendChar(char Tegn)
{
  // Wait for transmitter register empty (ready for new character)
  while ( (UCSRA & (1<<5)) == 0 )
  {}
  // Then send the character
  UDR = Tegn;
}

/*************************************************************************
Sends 0-terminated string.
Parameter:
   Streng: Pointer to the string. 

*************************************************************************/
void SendString(char* Streng)
{
  // Repeat untill zero-termination
  while (*Streng != 0)
  {
    // Send the character pointed to by "Streng"
    SendChar(*Streng);
    // Advance the pointer one step
    Streng++;
  }
}
/*************************************************************************
  Returns 0 (FALSE), if the UART has NOT received a new character.
  Returns value <> 0 (TRUE), if the UART HAS received a new character.
  not in use!
*************************************************************************/
unsigned char CharReady()
{
   return UCSRA & (1<<7);
}