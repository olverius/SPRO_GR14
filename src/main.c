#define F_CPU 16000000UL //needs to be defined for the delay functions to work.

#include <avr/io.h> //used for pins input/output
#include <util/delay.h> //here the delay functions are found
#include <stdio.h> //used for printf function.
#include "usart.h"//for uart output to pc. Debugging purposes
#include <avr/interrupt.h>
#define PI (3.141592653589793)


double dutyCycle = 0;
int first_dist,sec_dist,first_time,sec_time,shown_dist_gen;
int TIME, PPR; 
double velocity,coef;
float Ang_V,voltage;

void PWM_speed_1()
{
    dutyCycle = (first_dist/first_time)*coef;  
}
void PWM_speed_2()
{
    dutyCycle = (sec_dist/sec_time)*coef;
}

int main(void)
{   
    uart_init(); 
	io_redirect();
    DDRB = 0x00; //output
    PORTB = 0x01; //pin 1-i
    //Setup timer/counter as pure ticks counter, counting //clock ticks with 1024 prescaling ir. no interrupts
    TCCR1A = 0X00;
    TCCR1B = 0xC5;
    //Input capturee on positive edge ICP1 (PBO)
    //Filter is enabled 1024 clock prescaler
    DDRB &= ~0x01;//pin1 as input for ICP1 use 
    PORTB |= 0x01; //enable pullups
    TCNT1=0;
    //check ICR1 (which is a register) page.110
    //Take a look at registers in big file 
    DDRD = (1 << PORTD6);
    
    TCCR0A = (1 << COM0A1) | (1 << WGM00) | (1 << WGM01);
    TIMSK0 = (1 << TOIE0);
    
    OCR0A = (dutyCycle/100.0)*255.0;

    sei();
    
    TCCR0B = (1 << CS00) | (1 << CS02);
    char readBuffer[100];
    printf("page 0%c%c%c",255,255,255);//init at 9600 baud.
	_delay_ms(20);
	uint32_t readValue = 0;
    if(voltage=1){
     while (1) 
    {
      
		scanf("%c", readBuffer[i]);
		for(int i = 0 ; i<7 ; i++)
		{
			scanf("%c", readBuffer[i]);
			if(readBuffer[0] ==0x65 && readBuffer[2] == 0x07 && readBuffer[4] == 0xFF && readBuffer[5] == 0xFF && readBuffer[6] == 0xFF )
			{
				printf("get page0.n0.val%c%c%c",0xFF,0xFF,0xFF); //getting the value of the first distance
				
	
				for(int i = 0; i<8;i++)
				{
					scanf("%c", &readBuffer[i]);
					if(readBuffer[i] == 0x71)//Expect number string
					{
						
						readBuffer[0] = 0x71;//Move indicator to front, just to keep the nice format
						break;
					}
				}
				if(readBuffer[0] = 0x71)
				{
					for(int i = 1; i<8; i++)
					{
						scanf("%c", &readBuffer[i]);
					}

					if(readBuffer[0] ==(char)0x71 && readBuffer[5] == (char)0xFF && readBuffer[6] ==(char) 0xFF && readBuffer[7] == (char)0xFF)//This is a complete number return
					{
						first_dist = readBuffer[1] | (readBuffer[2] << 8) | (readBuffer[3] << 16)| (readBuffer[4] << 24);
					}
				}
		
				break;
			}
			else
			{
				printf("get pag0.n1.val%c%c%c",0xFF,0xFF,0xFF); // getting the value of the first time
				for(int i = 0; i<8;i++)
				{
					scanf("%c", &readBuffer[i]);
					if(readBuffer[i] == 0x71)//Expect number string
					{
						
						readBuffer[0] = 0x71;//Move indicator to front, just to keep the nice format
						break;
					}
				}
				if(readBuffer[0] = 0x71)
				{
					for(int i = 1; i<8; i++)
					{
						scanf("%c", &readBuffer[i]);
					}

					if(readBuffer[0] ==(char)0x71 && readBuffer[5] == (char)0xFF && readBuffer[6] ==(char) 0xFF && readBuffer[7] == (char)0xFF)//This is a complete number return
					{
						first_time = readBuffer[1] | (readBuffer[2] << 8) | (readBuffer[3] << 16)| (readBuffer[4] << 24);
					}
				}
				break;
			}
			break;
		    scanf("%c" &readBuffer[i]);
			if(readBuffer[0] == 0x65 && readBuffer[1] == 0x02 && readBuffer[2] == 0x01 && readBuffer[4] == 0xFF && readBuffer[5] == 0xFF && readBuffer[6] == 0xFF)
			{
				// run engine code + 
				unsigned int batteryvalue;
				if ((float)batteryvalue < 6.8)
				{
					printf("page warning%c%c%c",255,255,255);//init at 9600 baud. if the voltage of the battery is bellow 6.8 diplay shows warning page
                    dutyCycle = 0;
                }
				else
				{
					printf("play.x0.val=%d%c%c%c",(float)batteryvalue , 0xFF, 0xFF, 0xFF);// if the voltage is above that number in the play page the voltage will be visible 
                    PWM_speed_1();
                    while( (TIFR1 & 1<<5) == (1<<5))
                    { //Make sure 5th slot is recording data
                    TIME = ICR1 * (64.0/1000); //Time diff between holes -> time is recorded
                    PPR = TIME * 20; //number of holes in encoder wheel
                    Ang_V = 2*PI/PPR;
                    velocity = Ang_V*11.5; //diameter of wheel * pi / rotational period;
                    TCNT1 = 0;
                    TIFR1 |= (1<<5);

                    TCNT1 = 0;
                    TIFR1 |=(1<<5); 
                    }
                    TIME * velocity = shown_dist_gen;
                    if(shown_dist_gen == first_dist )
                    {
                        PWM_speed_2();
                    }
                    if(shown_dist_gen == first_dist + sec_dist)
                    {
                        dutyCycle=0;
                    }
				}
			}
		}
        
        
	}
}  
else
{
    
	printf("page warning%c%c%c",255,255,255);//init at 9600 baud. if the voltage of the battery is bellow 6.8 diplay shows warning page
    dutyCycle = 0;
    
}
}




//int main
 
ISR(TIMER0_OVF_vect)
{
    OCR0A = (dutyCycle/100.0)*255;
}


