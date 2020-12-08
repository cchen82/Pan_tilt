/*
 * duty_cycle_servo.c
 *
 * Created: 12/8/2020 9:05:08 AM
 * Author : chen
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "USART.h"
#define BAUD_RATE 9600
#define BAUD_PRESCALER (((F_CPU / (BAUD_RATE * 16UL))) - 1)
char str_print[20];

void deg_to_servo (int deg){
	OCR1A=(deg*2.7778)+125;
}
int main(void)
{
	USART_int(BAUD_PRESCALER);
	DDRB |= (1<<DDB1)|(1<<DDB2);	/* Make OC1A pin (~D9) OC1B (~D10) as output */
	TCNT1 = 0;		/* Set timer1 count zero */
	ICR1 = 4999;		/* Set TOP count for timer1 in ICR1 register */
	/* Set Fast PWM, TOP in ICR1, Clear OC1A on compare match, clk/64 */
	//TCCR1A = (1<<WGM11)|(1<<COM1A1);
	//TCCR1B = (1<<WGM12)|(1<<WGM13)|(1<<CS10)|(1<<CS11);
	//clear OC1A/OC1B on compare match
	TCCR1A |= (1<<COM1A1);
	TCCR1A &= ~(1<<COM1A0);
	//Fast PWM Mode
	TCCR1A &= ~(1<<WGM10);
	TCCR1A |= (1<<WGM11);
	TCCR1B |= (1<<WGM12);
	TCCR1B |= (1<<WGM13);
	//Configure timer pre-scaler (011) /64
	TCCR1B |= (1<<CS10);
	TCCR1B |= (1<<CS11);
	TCCR1B &= ~(1<<CS12);
	while(1)
	{
		//OCR1A = 125;	/* Set servo shaft at 0° position */
		//_delay_ms(1500);
		//OCR1A = 250;	/* Set servo shaft at 45° position */
		//_delay_ms(1500);
		////OCR1A = 375;	/* Set servo at 90° position */
		////_delay_ms(1500);
		////OCR1A = 500;	/* Set servo at 135° position */
		////_delay_ms(1500);
		//OCR1A = 625;	/* Set servo at 180° position */
		//_delay_ms(1500);
		deg_to_servo(0);
		_delay_ms(1500);

		
		deg_to_servo(45);
		_delay_ms(1500);


		deg_to_servo(180);
		_delay_ms(1500);

	}
}