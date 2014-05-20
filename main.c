/********************************************
* MSYS, LAB 12                              *
* Test program for Interrupt driven UART    *
* driver.                                   *
*                                           *
* STK500 setup:                             *
* Header "RS232 spare" connected to RXD/TXD *
*   RXD = PORTD, bit0                       *
*   TXD = PORTD, bit1                       *
*                                           *
* Henning Hargaard 27/11 2013               *
*********************************************/
#include <avr/io.h> // std input output lib
#include <avr/interrupt.h> // interrupt enableta
#include <stdlib.h>  // itoa
#include "uart_int.h"
#include "main.h"
#include "X10send.h"


ISR(INT2_vect) //INT2 til 'flag'
 {
         flag++;
         /* todo list
         skal måske lave en if sætning til når flag skifter fra 255 til 0 så dan starter på 2
         import af data og sætte ready = 1
         
         todo måske hvis jeg ikke sender et stort array
         ready = 0 ?/!
         ready = 1 unit
         ready = 2 on/off
         ready = 3 carriage return
         */
         
         if(ready == 1)
         {
         
                 if(flag % 2 == 0)
                 {
                        if (DataBuffer[sendcounter] == 0)
                        {
							//nothing
                        }
						else
						{
							Burst();
						}
                                 
                 }
                 
                 if(flag % 2 == 1)
                 {
					if (DataBuffer[sendcounter] == 0)
					{
						Burst();
					}
					else
					{
						//nothing
					}
					sendcounter++;
					flag = 0;
				 }
		 }
         
         if (sendcounter == 32)
         {
                 ready = 0;
         }    
 }
ISR (USART_RXC_vect){
	char Buffer[4];
	
	
	ReadString(&Buffer,ARRAY);
	if (Buffer[0] == '!' || Buffer[0] == '?')
	{
		for(int i = 0;i < 4; i++)
		{
			char tmpBuffer[9];
			// konverter char i Buffer til binaer i tmpBuffer
			// Fyld tmpBuffer i DataBuffer
			SendString("lol");
			SendString(DataBuffer);
		}
	ready = 1;
	}

}



int main(){

	// Initialize USART (with RX interrupt enable)
	InitUART(9600, 8, 1);
	InitAtmel();
	// Global interrupt enable
	sei();
	while (1)
	{
		// Her kunne man lave noget "fornuftigt"
	}

}