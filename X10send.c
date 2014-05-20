#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint-gcc.h>
#include "X10send.h"
 
/*---------------------------------------------------------------------
template
----------------------------------------------------------------------*/
 
 
 
 
/*---------------------------------------------------------------------
skifter hendholdvis mellem 1 og 0 for at simulere 10 = 1 og 01 = 0.
checker om modtaget data = 0 p� en 0 cycle eller 1 p� en 1 cycel og sender s� burst
s�tter skifter 1 ind p� dataen og s�tter data cyclen +1 for at se om vi er f�rdige.
flag s�ttes til volitile da den skifter uden at vi bruger den i koden.
og initieret til 1 pga vi starter p� 10 = 1 burst.
----------------------------------------------------------------------*/
volatile int currentBitPattern = 0;
volatile uint8_t flag = 1;
volatile int sendcycel = 0;
volatile int ready = 0;
int temp[9] = 0;
int failsafe = 0;
int DataBuffer[33];
 
 
void Burst(void)
{
       
}
 
 
/*---------------------------------------------------------------------
udregning for 120khz ctc signal
 
 ((((3686400/2)/1)/120000)-1)
 
 3686400
 -------
    2
 ------- -1 = 14,36 maxcount afrundet til 14 = (118916.1310 Hz)
    1
 -------
 1200005
 
---------------------------------------------------------------------*/
#define OCR0_VALUE 14
 ISR(TIMER0_COMP_vect)
 {
         OCR0 = (uint8_t)OCR0_VALUE;
 }
 
 
 
/*---------------------------------------------------------------------
linje for linje
 
Input for INT2 on PB2 & CTC PB0
Output for LEDs
INT2:Rising edge
Enable extern interrupts INT2
CTC - Mode 2 - No prescale
CTC - couter initial value
CTC - counter compare interrupt
enable global interrupts
---------------------------------------------------------------------*/
 void InitAtmel(void)
 {
	 DDRB |= (0<<PB2) | (0<<PB0);
	 DDRC = 0xff;
	 MCUCSR = 0b01000000;
	 GICR |= 0b00100000;
	 TCCR0 = 0b01101001;
	 TCNT0 = 0;
	 TIMSK |=(1<<OCIE0);
	 sei();
 }
 
 
 
/*---------------------------------------------------------------------
toggler via XOR PORTC
 
 if(TCNT0 >= OCR0_VALUE)
 {
         CTCBurst();
 }
----------------------------------------------------------------------*/
 
 void switchSetCTC(void)
 {
         DDRB |=(1<<PB3);
         _delay_ms(1);
         PORTC = 0b01111111;
         _delay_ms(500);
         DDRB |=(0<<PB3);
 }
 
 
