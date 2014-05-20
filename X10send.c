#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint-gcc.h>
#include "X10send.h"
 
/*---------------------------------------------------------------------
template
----------------------------------------------------------------------*/
 
 
 
 
/*---------------------------------------------------------------------
sætter CTC til output i 3ms og sætter den så til input
----------------------------------------------------------------------*/

 
void Burst(void)
{
    DDRB |=(1<<PB3);
    _delay_ms(3);
	DDRB |=(0<<PB3);	   
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
INT2:Rising edge
Enable extern interrupts INT2
CTC - Mode 2 - No prescale
CTC - couter initial value
CTC - counter compare interrupt
---------------------------------------------------------------------*/
 void InitAtmel(void)
 {
	 DDRB |= (0<<PB2) | (0<<PB0);
	 MCUCSR = 0b01000000;
	 GICR |= 0b00100000;
	 TCCR0 = 0b01101001;
	 TCNT0 = 0;
	 TIMSK |=(1<<OCIE0);
 }
 
 
 