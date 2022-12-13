#define F_CPU 16000000UL //needs to be defined for the delay functions to work.

#include <avr/io.h> //used for pins input/output
#include <util/delay.h> //here the delay functions are found
#include <stdio.h> //used for printf function.
#include "usart.h"//for uart output to pc. Debugging purposes
#include <avr/interrupt.h>
#define PI (3.141592653589793)


double dutyCycle = 0;
int first_dist,sec_dist;
void PWM_speeds()
{
      while(1)
    {
	        switch (first_dist){
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
        switch (sec_dist){
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
    char readBuffer[100];
     while (1) 
    {
		
		int dist1,time1,dist2,time2;
		for(int i = 0 ; i<7 ; i++)
		{
			scanf("%c", readBuffer[i]);
			if(readBuffer[0] ==0x65 && readBuffer[2] == 0x07 && readBuffer[4] == 0xFF && readBuffer[5] == 0xFF && readBuffer[6] == 0xFF )
			{
				printf("get page0.n0.val%c%c%c",0xFF,0xFF,0xFF); //getting the value of the first distance
				int typeExpected = 0;
    
            for(int i = 0; i<8;i++)
            {
                scanf("%c", &readBuffer[i]);
            }
            if(readBuffer[0] = 0x71)
            {
                for(int i = 1; i<8; i++)
                {
                    scanf("%c", &readBuffer[i]);
                }
 
                if(readBuffer[0] ==(char)0x71 && readBuffer[5] == (char)0xFF && readBuffer[6] ==(char) 0xFF && readBuffer[7] == (char)0xFF)//This is a complete number return
                {
                    dist1 = readBuffer[1] | (readBuffer[2] << 8) | (readBuffer[3] << 16)| (readBuffer[4] << 24);
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
                }
                if(readBuffer[0] = 0x71)
                {
                    for(int i = 1; i<8; i++)
                    {
                        scanf("%c", &readBuffer[i]);
                    }
    
                    if(readBuffer[0] ==(char)0x71 && readBuffer[5] == (char)0xFF && readBuffer[6] ==(char) 0xFF && readBuffer[7] == (char)0xFF)//This is a complete number return
                    {
                        time1 = readBuffer[1] | (readBuffer[2] << 8) | (readBuffer[3] << 16)| (readBuffer[4] << 24);
                    }
				break;
			}
			break;
		}
      
        for(int i = 0 ; i<7 ; i++)
		{
			scanf("%c", readBuffer[i]);
			if(readBuffer[0] ==0x65 && readBuffer[2] == 0x07 && readBuffer[4] == 0xFF && readBuffer[5] == 0xFF && readBuffer[6] == 0xFF )
			{
				printf("get page1.n0.val%c%c%c",0xFF,0xFF,0xFF); //getting the value of the first distance
				
    
            for(int i = 0; i<8;i++)
            {
                scanf("%c", &readBuffer[i]);
            }
            if(readBuffer[0] = 0x71)
            {
                for(int i = 1; i<8; i++)
                {
                    scanf("%c", &readBuffer[i]);
                }
 
                if(readBuffer[0] ==(char)0x71 && readBuffer[5] == (char)0xFF && readBuffer[6] ==(char) 0xFF && readBuffer[7] == (char)0xFF)//This is a complete number return
                {
                    dist2 = readBuffer[1] | (readBuffer[2] << 8) | (readBuffer[3] << 16)| (readBuffer[4] << 24);
                }
            }
                break;
			}
			else
			{
				printf("get page1.n1.val%c%c%c",0xFF,0xFF,0xFF); // getting the value of the first time
                
    
            for(int i = 0; i<8;i++)
            {
                scanf("%c", &readBuffer[i]);
            }
            if(readBuffer[0] = 0x71)
            {
                for(int i = 1; i<8; i++)
                {
                    scanf("%c", &readBuffer[i]);
                }
 
                if(readBuffer[0] ==(char)0x71 && readBuffer[5] == (char)0xFF && readBuffer[6] ==(char) 0xFF && readBuffer[7] == (char)0xFF)//This is a complete number return
                {
                    time2 = readBuffer[1] | (readBuffer[2] << 8) | (readBuffer[3] << 16)| (readBuffer[4] << 24);
                }
				break;
			}
			break;
            
		}

    }  
} 
        first_dist = dist1/time1;//calculations for speed
        sec_dist = dist2/time2;//calculations for speed
// start button
		for( int i = 0; i < 7; i++)
		{
			scanf("%c" &readBuffer[i]);
			if(readBuffer[0] == 0x65 && readBuffer[1] == 0x02 && readBuffer[2] == 0x01 && readBuffer[4] == 0xFF && readBuffer[5] == 0xFF && readBuffer[6] == 0xFF)
			{

				PWM_speeds();//update motor

			}
		}

 //update motor

/*Here put update for the speed and current state of the car(distance voltage)*/





}//while(1)




}//int main
 
ISR(TIMER0_OVF_vect)
{
    OCR0A = (dutyCycle/100.0)*255;
}


