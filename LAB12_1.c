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
#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart_int.h"
#include "led.h"
#include "main.h"

ISR (USART_RXC_vect)
{
	char buffer[4];
	
	
	ReadString(&buffer,ARRAY);
	if (buffer[0]== '!' || buffer[0]=='?')
	{
		if (buffer[2] == '0')
		{
			taendlys(buffer[1]);
		}
		else if (buffer[2]== 'f')
		{
			sluklys(buffer[1]);
		}
	}

}

	

int main()
{
	char * Buffer;
	
	// Initialize USART (with RX interrupt enable)
	InitUART(9600, 8, 1);
	// Global interrupt enable
	sei();
	// Initialize LED port
	initLEDport();
	while (1)
	{
		// Her kunne man lave noget "fornuftigt"
	}

}

void taendlys(int ID){
	
	// Toggle aktuelle lysdiode
	turnOnLED(ID - '0');
	// Send streng "LED nummer x er toggled"
	SendString("LED nummer ");
	SendChar(ID);
	SendString(" er toggled\r\n");
	
}

void sluklys(int ID){
	
	// Toggle aktuelle lysdiode
	turnOffLED(ID - '0');
	// Send streng "LED nummer x er toggled"
	SendString("LED nummer ");
	SendChar(ID);
	SendString(" er toggled\r\n");
	
}