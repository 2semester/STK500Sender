/*
 * CFile2.c
 *
 * Created: 5/6/2014 08:45:50
 *  Author: Kris
 */ 

char sendData()
{
	
}

char sendCommand()
{
	
}

char binaryToHex()
{
	
}

char hexToBinary()
{
	
}

void init(void)
{
	
	// læs op på hvad vi skal bruge
	    DDRA = 0x07; //PORTA pins 0,1,2 set as outputs
	    //  DDRD = 0x02; //PORTD pin 1 is output (TX) and pin 0 is input (RX)

	    //Timer SETUP
	    TCCR1A = 0x80; //OCR1A enable in CTC mode
	    TCCR1B = 0x0C; //CTC mode, 256 prescale
	    TIMSK = 0x10; //CTC on OCR1A enabled, overflow disabled
	    OCR1A = 2000; //OCR value set to get an interrupt every 1 second (15624)

		//USART SETUP
		UCSRA = 0x00; //no Frame Error, no parity error, no Data OverRun
		UCSRB = 0xD8; //receiver enable, transmitter enable (0x18)
		UCSRC = 0x86; //Asynchronous USART mode, no parity, 1 stop bit, 8-bit character size, Data transmitted on rising edge and received on falling edge of the clock
		UBRRL = 51; //Baud rate of 9600bps (8MHz clock?)
		UBRRH = 0;

	    sei(); //Global interrupt enable
}