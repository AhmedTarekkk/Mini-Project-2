/*
 * Timer1.c
 *
 *  Created on: Sep 16, 2022
 *      Author: Ahmed
 */

#include "Timer1.h"

void TIMER1_INIT(void)
{
	/* Configure the timer to CTC mode with pre-scaler = clk/1024 ,start counting from 0 and the compare value
	  in the OCR =  1000 and enable compare mode interrupt so it can generate interrupt every 1 second after
	  after enabling the I-bit in SREG "General interrupt enable bit" */
	TCCR1A = (1<<FOC1B) ;
	TCCR1B = (1<<WGM12) | (1<<WGM13) | (1<<CS12) | (1<<CS10) ;
	TCNT1 = 0;
	/*	OCR1A = 1000 if we consider F = 1Mhz = 1 * 1024 * 10^3
	 * 	OCR1A = 1024 if we consider F = 1Mhz = 1 * 1024 * 1024
	 *	OCR1A = 975 if we consider F = 1Mhz = 1 * 10^6
	 *	i found the last option is more accurate on Porteus
	 */
	ICR1 = 975;
	TIMSK |= (1<<OCIE1B) ;
}

void TIMER1_STOP(void)
{
	/* Configure the clock to be 0 by clearing CS1x bits so it will stop counting */
	TCCR1B &= (0xF8);
}

void TIMER1_RESUME(void)
{
	/* Configure the clock again to be clk/1024 so it can resume counting */
	TCCR1B |= (1<<CS12) | (1<<CS10) ;
}
