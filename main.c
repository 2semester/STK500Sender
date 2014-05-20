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
         
         /* todo måske hvis jeg ikke sender et stort array
         ready = 0 ?/!
         ready = 1 unit
         ready = 2 on/off
         ready = 3 carriage return
         */
         if(DataBuffer != temp && ready = 0)
         {
                 for(int i = 0;i < 4; i++)
				 {
					 DataBuffer[32];
					 itoa(DataBuffer, Buffer[i], 2)
					 DataBuffer = DataBuffer >> 8;
				 }
				 
                 ready = 1;
         }
         
         if (ready = 1)
         {
         
                 if(flag % 2 == 0)
                 {
                         if (DataBuffer ^ 0b00000001)
                         {
                                 Burst();
                                 Failsafe = 1;
                                 sendcycel++;
                         }
                                 
                 }
                 
                 if(flag % 2 == 1)
                 {
                        if(DataBuffer & 0b00000001)
                        {
                                if (failsafe != 1)
                                {
                                Burst();
                                sendcycel++;
                                DataBuffer = DataBuffer >> 1;
								}								
						}
                 }
				 if (failsafe = 1)
				 {
					 DataBuffer = DataBuffer >> 1;
					 failsafe = 0;
				 }
		 }
         
         if (sendcycel = 8)
         {
                 ready = 0;
         }
         
         
       
 }
ISR (USART_RXC_vect){
	char buffer[4];
	
	
	ReadString(&buffer,ARRAY);
	if (buffer[0]== '!' || buffer[0]=='?')
	{
		if (buffer[2] == '0')
		{
			// set ready og send buffer 1 og ledon
			//convertToBinary(buffer[1]);
			//taendlys(buffer[1]);
			//SendString("Lol\r\n");
		}
		else if (buffer[2]== 'f')
		{
			// set ready og send buffer 1 og ledoff
			//sluklys(buffer[1]);
		}
	}

}



int main(){
	char * Buffer;
	
	// Initialize USART (with RX interrupt enable)
	InitUART(9600, 8, 1);
	InitAtmel()
	// Global interrupt enable
	sei();
	// Initialize LED port
	initLEDport();
	while (1)
	{
		// Her kunne man lave noget "fornuftigt"
	}

}