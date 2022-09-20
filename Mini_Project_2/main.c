#include <util/delay.h>
#include <avr/interrupt.h>
#include "Timer1.h"
#include "EXTI.h"
#include "Seven_Segment.h"

#define SETALARM	0

typedef struct
{
	unsigned char hour ;
	unsigned char min ;
	unsigned char sec ;

}TIME;

TIME Time = {0,0,0} ; // Initialize the time with zeros

#if	(SETALARM == 1)

TIME Alarm,*ptr = &Alarm;

unsigned char count = 0, AlarmOnFlag = 0;

void SetAlarm(unsigned char Hour,unsigned char Min,unsigned char Sec)
{
	ptr->hour = Hour;
	ptr->min = Min;
	ptr->sec = Sec;
}

#endif

ISR(TIMER1_COMPB_vect) // Interrupt service routine to control the watch time
{
	Time.sec++;
	if(Time.sec > 59)
	{
		Time.min++;
		Time.sec = 0;
		if(Time.min > 59)
			{
				Time.hour++;
				Time.min = 0;
				if(Time.hour > 23)
					{
						Time.hour = 0;
					}
			}
	}
	#if	(SETALARM == 1)
	if((Alarm.hour == Time.hour) && (Alarm.min == Time.min) && (Alarm.sec == Time.sec))
	{
		PORTC |= (1<<6);
		AlarmOnFlag = 1;
	}

	if(AlarmOnFlag)
	{
		count++;
		if(count == 5)
		{
			PORTC &= ~(1<<6);
			AlarmOnFlag = 0;
			count = 0; // reset the counter so the alarm can goes off after 24 hours " in the next day "
		}
	}
	#endif
}

ISR(INT0_vect) //Reset the time
{
	Time.sec = 0;
	Time.min = 0;
	Time.hour = 0;
}

ISR(INT1_vect)
{
	TIMER1_STOP();
}

ISR(INT2_vect)
{
	TIMER1_RESUME();
}

int main(void)
{
	DDRD &= ~(1<<2) & ~(1<<3) ; // INT0 and INT1 as input
	PORTD |= (1<<2) ; // Internal Pull-up Resistor for INT0

	DDRB &= ~(1<<2) ; // INT2
	PORTB |= (1<<2) ; // Internal Pull-up Resistor for INT2

	DDRA |= (0x3F) ; // Enable pins for the 6 seven segments
	PORTA &= ~(0x3F) ;

	DDRC |= (0x0F) ; // Seven Segments Pins
	PORTC &= ~(0x0F) ; //Disable All of them at the start

	SREG |= (1<<7) ; // Global interrupt enable

	INT0_INIT(); //External interrupts initialization
	INT1_INIT();
	INT2_INIT();

	TIMER1_INIT();//Timer1 initialization

	#if	(SETALARM == 1)
	DDRC |= (1<<6);
	PORTC &= ~(1<<6);
	SetAlarm(0, 0, 5);
	#endif

	while(1)
	{
		/* Display using multiplexing method */
		SevSeg_WriteNumber(Time.sec%10);
		SevSeg_Sec1_Enable();
		_delay_ms(2);
		SevSeg_Sec1_Disable();

		SevSeg_WriteNumber(Time.sec/10);
		SevSeg_Sec2_Enable();
		_delay_ms(2);
		SevSeg_Sec2_Disable();

		SevSeg_WriteNumber(Time.min%10);
		SevSeg_Min1_Enable();
		_delay_ms(2);
		SevSeg_Min1_Disable();

		SevSeg_WriteNumber(Time.min/10);
		SevSeg_Min2_Enable();
		_delay_ms(2);
		SevSeg_Min2_Disable();

		SevSeg_WriteNumber(Time.hour%10);
		SevSeg_Hour1_Enable();
		_delay_ms(2);
		SevSeg_Hour1_Disable();

		SevSeg_WriteNumber(Time.hour/10);
		SevSeg_Hour2_Enable();
		_delay_ms(2);
		SevSeg_Hour2_Disable();
	}
}

