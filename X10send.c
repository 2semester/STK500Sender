#include <avr/io.h>
#include <avr/interrupt.h>
#include "X10send.h"
#include <util/delay.h>
#include <stdint-gcc.h>

 /*---------------------------------------------------------------------
toggle 3ms burst
sætter CTC til output i 3ms og sætter den så til input
----------------------------------------------------------------------*/

 
void Burst(void)
{
    DDRD |=(1<<PD7);
    _delay_ms(3);
	DDRD &= ~(1<<PD7);	   
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
#define OCR2_VALUE 14
 /*
 ISR(TIMER2_COMP_vect)
 {
         OCR2 = (uint8_t)OCR2_VALUE;
 }
 
 */
 
 
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
	 DDRB |= (0<<PB2);
	 DDRD |= (0<<PD7);
	 MCUCSR = 0b01000000;
	 GICR |= 0b00100000;
	 TCCR2 = 0b00011001;
	 TCNT2 = 0;
	 TIMSK |=(1<<OCIE0);
	 OCR2 = (uint8_t)OCR2_VALUE;
 }
 
 
 