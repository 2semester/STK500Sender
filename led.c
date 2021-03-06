#include <avr/io.h>

#define MAX_LED_NR 7

void initLEDport()
{
  // S�t alle PORTC's ben til at v�re udgange 
  DDRC = 0b11111111;
  // Sluk alle lysdioderne
  PORTC = 0xFF;     
}

void writeAllLEDs(unsigned char pattern)
{
  // Hent parameteren, vend alle bit, og skriv til lysdioderne
  // Bittene skal vendes, da HW er indrettet, 
  // s� et 0 vil t�nde en lysdiode
  PORTC = ~pattern;   
}

void turnOffLED(unsigned char led_nr)
{
// Lokal variabel
unsigned char mask;
  // Vi skal kun lave noget, hvis led_nr < 8
  if (led_nr <= MAX_LED_NR)
  {
    // Dan maske p� basis af parameteren (led_nr)
    mask = ~(0b00000001 << led_nr);
    // T�nd den aktuelle lysdiode (de andre �ndres ikke)
   
   
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
    // Dan maske p� basis af parameteren (led_nr)
    mask = 0b00000001 << led_nr;
    // Sluk den aktuelle lysdiode (de andre �ndres ikke)
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
    // Dan maske p� basis af parameteren (led_nr)
    mask = 0b00000001 << led_nr;
    // Toggle den aktuelle lysdiode (de andre �ndres ikke)
    PORTC = PORTC ^ mask;
  }  
}