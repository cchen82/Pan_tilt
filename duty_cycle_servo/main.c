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
//servo1 is on PB1
void deg_to_servo1 (int deg){
	OCR1A=(deg*2.7778)+125;
}
//servo2 is on PB2
void deg_to_servo2 (int deg){
	OCR1B=(deg*2.7778)+125;
}
void initialize_pwm_2servos (){
	cli();
	DDRB |= (1<<DDB1)|(1<<DDB2);	/* Make OC1A pin (~D9) OC1B (~D10) as output */
	TCNT1 = 0;		/* Set timer1 count zero */
	ICR1 = 4999;		/* Set TOP count for timer1 in ICR1 register */
	/* Set Fast PWM, TOP in ICR1, Clear OC1A on compare match, clk/64 */
	//TCCR1A = (1<<WGM11)|(1<<COM1A1);
	//TCCR1B = (1<<WGM12)|(1<<WGM13)|(1<<CS10)|(1<<CS11);
	//clear OC1A/OC1B on compare match
	//for servo1
	TCCR1A |= (1<<COM1A1);
	TCCR1A &= ~(1<<COM1A0);
	//for servo2
	TCCR1A |= (1<<COM1B1);
	TCCR1A &= ~(1<<COM1B0);
	//Fast PWM Mode
	TCCR1A &= ~(1<<WGM10);
	TCCR1A |= (1<<WGM11);
	TCCR1B |= (1<<WGM12);
	TCCR1B |= (1<<WGM13);
	//Configure timer pre-scaler (011) /64
	TCCR1B |= (1<<CS10);
	TCCR1B |= (1<<CS11);
	TCCR1B &= ~(1<<CS12);
	sei();
}
int main(void)
{
initialize_pwm_2servos();
	while(1)
	{
		deg_to_servo1(0);
		deg_to_servo2(180);
		_delay_ms(1500);

		
		deg_to_servo1(45);
		deg_to_servo2(0);
		_delay_ms(1500);


		deg_to_servo1(180);
		deg_to_servo2(45);
		_delay_ms(1500);
		

	}
}