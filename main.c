#include <avr/io.h> // std input output lib
#include <avr/interrupt.h> // interrupt enable
#include "uart_int.h"
#include "main.h"
#include "X10send.h"
#include "uart_test.h"
/*--------------------------------------------------------------------5w-
når der kommer et zero crossing interrupt
flag tælles 1 op
der checkes for om ny data er modtaget
hvis den sidst har sendt et 1 er failsafe 1 og den sættes til 0 så vi kan sende et 0 denne gang (dette bruges for at vi ikke sender både 1 og 0 i en cycel og derved laver et falsk data burst.) 
der checkes for om det er en 1 eller 0 cycel
hvis det er et 0 cycel og en 0 bit. og failsafe = 0 sendes der et burst ellers sker der ingenting 
hvis det er et 1 cycel og en 1 bit. sendes der et burst ellers sker der ingenting 
når der er sent et burst tælles send counteren en op og vi kikker på den næste plads
når 5 bit er sent sættes ready til 0 samt '\0' sendes for indikere at vi har en tom databuffer så vi stopper med at sende.
----------------------------------------------------------------------*/
ISR(INT2_vect)
{
	if(ready == 1)
	{
		if(readycheck == 2){
			flag++;
			if(flag % 2 == 1)  // foerste cycel
			{
				if (DataBuffer[sendcounter] == '1')
				{
					Burst();
					SendString("1");
				}
				else
				{
				    //nothing
					SendString("0");
				}
			}

			if(flag % 2 == 0) // anden cycel
			{
				if (DataBuffer[sendcounter] == '0')
				{
					Burst();
					SendString("1");
				}
				else
				{
					//nothing
					SendString("0");
				}
				sendcounter++;
			}
		}
		if(readycheck == 0){
			Burst();
			SendString("1");
			SendString("readycheck 1 ");
			readycheck = 1;
		}
		if(readycheck == 1){
			Burst();
			SendString("1");
			SendString("readycheck 2 ");
			readycheck = 2;
		}
		if (sendcounter == 20)
		{
			sendcounter = 0;
			SendString("done sending stuff");
			ready = 0;
			DataBuffer[0] = '\0';
			readycheck = 0;
		}		
	}
}
 
 
 /*
 der laves et lokalt array som bliver fyldt med data fra usart.
 hvis den første char er ! eller ? 
 checkes der for om der skal tændes eller slukkes for lys
 derefter senden den et binær array til databuffern som skal sendes via zero crossing interrupts
 */
ISR (USART_RXC_vect)
{ 
	char Buffer[4];
	ReadString(&Buffer,ARRAY);
	SendString(Buffer);
	if (Buffer[0] == '!' || Buffer[0] == '?')
	{
		switch (Buffer[0])
		{
			case '!' ://DataBuffer[5] = {0,0,0,0,1};
			DataBuffer[0] = '0';
			DataBuffer[1] = '0';
			DataBuffer[2] = '0';
			DataBuffer[3] = '0';
			DataBuffer[4] = '1';
			DataBuffer[5] = '\0';
			break;
			
			case '?' ://DataBuffer[5] = {0,0,0,0,0};
			DataBuffer[0] = '0';
			DataBuffer[1] = '0';
			DataBuffer[2] = '0';
			DataBuffer[3] = '0';
			DataBuffer[4] = '0';
			DataBuffer[5] = '\0';
			break;
		}
		switch (Buffer[1])
		{
			case '0' ://DataBuffer[5] = {0,0,0,1,1};
			DataBuffer[5] = '0';
			DataBuffer[6] = '0';
			DataBuffer[7] = '0';
			DataBuffer[8] = '1';
			DataBuffer[9] = '0';
			DataBuffer[10] = '\0';
			break;
			
			case '1' ://DataBuffer[5] = {0,0,0,1,1};
			DataBuffer[5] = '0';
			DataBuffer[6] = '0';
			DataBuffer[7] = '0';
			DataBuffer[8] = '1';
			DataBuffer[9] = '1';
			DataBuffer[10] = '\0';
			break;

			case '2' ://DataBuffer[5] = {0,0,1,0,1};
			DataBuffer[5] = '0';
			DataBuffer[6] = '0';
			DataBuffer[7] = '1';
			DataBuffer[8] = '0';
			DataBuffer[9] = '0';
			DataBuffer[10] = '\0';
			break;

			case '3' ://DataBuffer[5] = {0,0,1,1,1};
			DataBuffer[5] = '0';
			DataBuffer[6] = '0';
			DataBuffer[7] = '1';
			DataBuffer[8] = '0';
			DataBuffer[9] = '1';
			DataBuffer[10] = '\0';
			break;

			case '4' ://DataBuffer[5] = {0,1,0,0,1};
			DataBuffer[5] = '0';
			DataBuffer[6] = '0';
			DataBuffer[7] = '1';
			DataBuffer[8] = '1';
			DataBuffer[9] = '0';
			DataBuffer[10] = '\0';
			break;

			case '5' ://DataBuffer[5] = {0,1,0,1,1};
			DataBuffer[5] = '0';
			DataBuffer[6] = '0';
			DataBuffer[7] = '1';
			DataBuffer[8] = '1';
			DataBuffer[9] = '1';
			DataBuffer[10] = '\0';
			break;

			case '6' ://DataBuffer[5] = {0,1,1,0,1};
			DataBuffer[5] = '0';
			DataBuffer[6] = '1';
			DataBuffer[7] = '0';
			DataBuffer[8] = '0';
			DataBuffer[9] = '0';
			DataBuffer[10] = '\0';
			break;

			case '7' ://DataBuffer[5] = {0,1,1,1,1};
			DataBuffer[5] = '0';
			DataBuffer[6] = '1';
			DataBuffer[7] = '0';
			DataBuffer[8] = '0';
			DataBuffer[9] = '1';
			DataBuffer[10] = '\0';
			break;

			case '8' :// DataBuffer[5] = {1,0,0,0,1};
			DataBuffer[5] = '0';
			DataBuffer[6] = '1';
			DataBuffer[7] = '0';
			DataBuffer[8] = '1';
			DataBuffer[9] = '0';
			DataBuffer[10] = '\0';
			break;

			case '9' ://DataBuffer[5] = {1,0,0,1,1};
			DataBuffer[5] = '0';
			DataBuffer[6] = '1';
			DataBuffer[7] = '0';
			DataBuffer[8] = '1';
			DataBuffer[9] = '1';
			DataBuffer[10] = '\0';
			break;

			case 'a' ://DataBuffer[5] = {1,0,1,0,1};
			DataBuffer[5] = '0';
			DataBuffer[6] = '1';
			DataBuffer[7] = '1';
			DataBuffer[8] = '0';
			DataBuffer[9] = '0';
			DataBuffer[10] = '\0';
			break;

			case 'b' ://DataBuffer[5] = {1,0,1,1,1};
			DataBuffer[5] = '0';
			DataBuffer[6] = '1';
			DataBuffer[7] = '1';
			DataBuffer[8] = '0';
			DataBuffer[9] = '1';
			DataBuffer[10] = '\0';
			break;

			case 'c' ://DataBuffer[5] = {1,1,0,0,1};
			DataBuffer[5] = '0';
			DataBuffer[6] = '1';
			DataBuffer[7] = '1';
			DataBuffer[8] = '1';
			DataBuffer[9] = '0';
			DataBuffer[10] = '\0';
			break;

			case 'd' ://DataBuffer[5] = {1,1,0,1,1};
			
			DataBuffer[5] = '0';
			DataBuffer[6] = '1';
			DataBuffer[7] = '1';
			DataBuffer[8] = '1';
			DataBuffer[9] = '1';
			DataBuffer[10] = '\0';
			break;

			case 'e' :// DataBuffer[5] = {1,1,1,0,1};
			DataBuffer[5] = '1';
			DataBuffer[6] = '0';
			DataBuffer[7] = '0';
			DataBuffer[8] = '0';
			DataBuffer[9] = '0';
			DataBuffer[10] = '\0';
			break;
		}
		switch (Buffer[2])
		{
			case '0' ://DataBuffer[5] = {0,0,0,0,1};
			DataBuffer[10] = '0';
			DataBuffer[11] = '0';
			DataBuffer[12] = '0';
			DataBuffer[13] = '1';
			DataBuffer[14] = '0';
			DataBuffer[15] = '\0';
			break;
			
			case 'f' ://DataBuffer[5] = {0,0,0,0,0};
			DataBuffer[10] = '1';
			DataBuffer[11] = '0';
			DataBuffer[12] = '0';
			DataBuffer[13] = '0';
			DataBuffer[14] = '1';
			DataBuffer[15] = '\0';
			break;
		}
		DataBuffer[15] = '1';
		DataBuffer[16] = '0';
		DataBuffer[17] = '0';
		DataBuffer[18] = '1';
		DataBuffer[19] = '1';
		DataBuffer[20] = '\0';
		
		//SendString(DataBuffer);
		ready = 1;
	}

}


int main()
{
	// Initialize USART (with RX interrupt enable)
	InitUART(9600, 8, 1);
	// Initialize CTC 
	InitAtmel();
	// Global interrupt enable
	sei();
	SendString("init done");
	
	while (1)
	{
		//endless nothing
	}
}