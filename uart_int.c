#include <avr/io.h>
#include <stdlib.h>
#include "uart_int.h"

// Constants
#define XTAL 3686400  

/*************************************************************************
USART initilization.
    Asyncronous mode.
	RX and TX enabled.
	No interrupts enabled.
	Number of Stop Bits = 1.
	No Parity.
	Baud rate = Parameter.
	Data bits = Parameter.
Parameters:
	BaudRate: Wanted Baud Rate.
	Databits: Wanted number of Data Bits.
*************************************************************************/
void InitUART(unsigned long BaudRate, unsigned char DataBit, unsigned char RX_int  )
{
unsigned int TempUBRR;

  if ((BaudRate >= 110) && (BaudRate <= 115200) && (DataBit >=5) && (DataBit <= 8))
  { 
    // "Normal" clock, no multiprocesser mode (= default)
    UCSRA = 0b00100000;
    // No interrupts enabled
    // Receiver enabled
    // Transmitter enabled
    // No 9 bit operation
    UCSRB = 0b00011000;
    // Enable RX interrupts if wanted
    if (RX_int)
      UCSRB |= 0b10000000;
    // Asynchronous operation, 1 stop bit, no parity
    // Bit7 always has to be 1
    // Bit 2 and bit 1 controlles the number of databits
    UCSRC = 0b10000000 | (DataBit-5)<<1;
    // Set Baud Rate according to the parameter BaudRate:
    // Select Baud Rate (first store "UBRRH--UBRRL" in local 16-bit variable,
    //                   then write the two 8-bit registers seperately):
    TempUBRR = XTAL/(16*BaudRate) - 1;
    // Write upper part of UBRR
    UBRRH = TempUBRR >> 8;
    // Write lower part of UBRR
    UBRRL = TempUBRR;
  }  
}

/*************************************************************************
	Awaits new character received.
	Then this character is returned.
*************************************************************************/
char ReadChar()
{
  // Wait for new character received
  while ( (UCSRA & (1<<7)) == 0 )
  {}                        
  // Then return it
  return UDR;
}
/*************************************************************************
ReadString tager en char bufferpointer,  og en maxLenght
først initeres den en char Nextchar og en stringLenght
derefter ligger den ReadChar in i NextChar 
så køre den et loop til den når carriage return og stringLenght er mindre end maxlenght
i loopet 
ligger den nextChar i +1 plads i bufferen 
tæller stringlenght en op
sætter ReadChar ind i NextChar 
og når den er færdig med loopet ligger den NULL ind i buffern
*************************************************************************/
void ReadString(char* Buffer, int MaxLenght)
{
	char NextChar;
	int StringLenght=0;
	
	NextChar = ReadChar();
	
	while (NextChar != '\r' && StringLenght < MaxLenght)
	{
		*Buffer++ = NextChar;
		StringLenght++;
		NextChar = ReadChar();
	}
	*Buffer = '\0';
}
