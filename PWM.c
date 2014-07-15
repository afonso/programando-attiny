#define F_CPU 1000000
#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>

int main(void) 
{ 
   DDRB = _BV(PB4); 
   PORTB = 0;
    
   TCCR1 = _BV(CS10); 
    
   GTCCR = _BV(PWM1B) | _BV(COM0B1);

   OCR1C = 255; 
   
   int i = 0;

   for(;;) 
   { 
      //  Fade LED on
        for(i = 0; i < 255; i++)
        {
            //  Load new value onto OCR0A register to change duty cycle
            OCR1B = i;
            _delay_ms(10);
        }
         
        //  Fade LED off
        for(i = 255; i >= 0; i--)
        {
            OCR1B = i;
            _delay_ms(10);
        }
   } 

   return 1;    
}