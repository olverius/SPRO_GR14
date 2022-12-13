#define F_CPU 16000000UL //needs to be defined for the delay functions to work.

#include <avr/io.h> //used for pins input/output
#include <util/delay.h> //here the delay functions are found
#include <stdio.h> //used for printf function.
#include "usart.h"//for uart output to pc. Debugging purposes
#include <avr/interrupt.h>



double dutyCycle = 0;
int change;
int main(void)
{   
    uart_init(); 
	io_redirect(); 
    DDRD = (1 << PORTD6);
    
    TCCR0A = (1 << COM0A1) | (1 << WGM00) | (1 << WGM01);
    TIMSK0 = (1 << TOIE0);
    
    OCR0A = (dutyCycle/100.0)*255.0;
    
    sei();
    
    TCCR0B = (1 << CS00) | (1 << CS02);
    
    while(1)
    {
		_delay_ms(100);
		printf("Instert speed wruuum\n");
		scanf("%d",&change);
        switch (change){
            case 1:
            dutyCycle = 10;
            break;
             case 2:
            dutyCycle = 20;
            break;
             case 3:
            dutyCycle = 30;
            break;
             case 4:
            dutyCycle = 40;
            break;
             case 5:
            dutyCycle = 50;
            break;
             case 6:
            dutyCycle = 60;
            break;
             case 7:
            dutyCycle = 70;
            break;
             case 8:
            dutyCycle = 80;
            break;
             case 9:
            dutyCycle = 90;
            break;
             case 10:
            dutyCycle = 100;
            break;    
			default:
			dutyCycle = 0;       
        }   
}
}
 
ISR(TIMER0_OVF_vect)
{
    OCR0A = (dutyCycle/100.0)*255;
}


