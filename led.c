/*************************************************
* "LED.C":                                       *
* Implementation file for the STK500 LED driver. *
* The LEDs are connected to PC pins.             *
* Henning Hargaard, 27/9 2011                    *
**************************************************/
#include <avr/io.h>

#define MAX_LED_NR 7

void initLEDport()
{
  // Sæt alle PORTC's ben til at være udgange 
  DDRC = 0b11111111;
  // Sluk alle lysdioderne
  PORTC = 0xFF;     
}

void writeAllLEDs(unsigned char pattern)
{
  // Hent parameteren, vend alle bit, og skriv til lysdioderne
  // Bittene skal vendes, da HW er indrettet, 
  // så et 0 vil tænde en lysdiode
  PORTC = ~pattern;   
}

void turnOffLED(unsigned char led_nr)
{
// Lokal variabel
unsigned char mask;
  // Vi skal kun lave noget, hvis led_nr < 8
  if (led_nr <= MAX_LED_NR)
  {
    // Dan maske på basis af parameteren (led_nr)
    mask = ~(0b00000001 << led_nr);
    // Tænd den aktuelle lysdiode (de andre ændres ikke)
   
   
    PORTC = PORTC & mask;
  }   
}

void turnOnLED(unsigned char led_nr)
{
// Lokal variabel
unsigned char mask;
  // Vi skal kun lave noget, hvis led_nr < 8
  if (led_nr <= MAX_LED_NR)
  {
    // Dan maske på basis af parameteren (led_nr)
    mask = 0b00000001 << led_nr;
    // Sluk den aktuelle lysdiode (de andre ændres ikke)
    PORTC = PORTC | mask;
  }  
}

void toggleLED(unsigned char led_nr)
{
// Lokal variabel
unsigned char mask;
  // Vi skal kun lave noget, hvis led_nr < 8
  if (led_nr <= MAX_LED_NR)
  {
    // Dan maske på basis af parameteren (led_nr)
    mask = 0b00000001 << led_nr;
    // Toggle den aktuelle lysdiode (de andre ændres ikke)
    PORTC = PORTC ^ mask;
  }  
}