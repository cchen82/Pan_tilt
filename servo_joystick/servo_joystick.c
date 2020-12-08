/*
 * servo.c
 *
 * Created: 11/24/2020 9:30:07 PM
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
void initialize_adc(){
	cli();
	//Power Reduction ADC on PRR bit 0
	PRR &= ~(1<<PRADC);
	//Reference Voltage to AVcc with external capacitor at AREF pin at AMUX (01)
	ADMUX |=(1<<REFS0);
	ADMUX &= ~(1<<REFS1);
	//ADC frequency pre-scaler, target between 50-200 KHz, pre-scaler of 128
	ADCSRA |=(1<<ADPS2);
	ADCSRA |=(1<<ADPS1);
	ADCSRA |=(1<<ADPS0);
	//set up Channel to read, use channel 0, ADMUX reg
	ADMUX &= ~(1<<MUX0);
	ADMUX &= ~(1<<MUX1);
	ADMUX &= ~(1<<MUX2);
	ADMUX &= ~(1<<MUX3);
	//set up trigger mode, auto trigger bit5 ADATE at ADCSRA
	ADCSRA|= (1<<ADATE);
	//set up free running 000 at ADCSRB
	ADCSRB &= ~(1<<ADTS0);
	ADCSRB &= ~(1<<ADTS0);
	ADCSRB &= ~(1<<ADTS0);
	//disable input buffer, ADC0D at DIDR0
	DIDR0 |= (1<<ADC0D);
	//Enable ADC, bit 7 ADEN:ADC Enable at ADCSRA
	ADCSRA |= (1<<ADEN);
	//Start Conversion, Bit 6 ADSC:ADC Start Conversion at ADCSRA
	ADCSRA |= (1<<ADSC);
	sei();
}
void initialize_pwm (){
	cli();//disable all interrupts
	DDRB |= (1<<DDB1)|(1<<DDB2);	/* Make OC1A pin (~D9) OC1B (~D10) as output */
	TCNT1 = 0;		/* Set timer1 count zero */
	ICR1 = 4999;		/* Set TOP count for timer1 in ICR1 register */
	/* Set Fast PWM, TOP in ICR1, Clear OC1A on compare match, clk/64 */
	//TCCR1A = (1<<WGM11)|(1<<COM1A1);
	//TCCR1B = (1<<WGM12)|(1<<WGM13)|(1<<CS10)|(1<<CS11);
	//clear OC1A/OC1B on compare match
	TCCR1A |= (1<<COM1A1);
	TCCR1A &= ~(1<<COM1A0);
//	TCCR1A |= (1<<COM1B1);
//	TCCR1A &= ~(1<<COM1B0);
	//Fast PWM Mode
	TCCR1A &= ~(1<<WGM10);
	TCCR1A |= (1<<WGM11);
	TCCR1B |= (1<<WGM12);
	TCCR1B |= (1<<WGM13);
	//Configure timer pre-scaler (011) /64
	TCCR1B |= (1<<CS10);
	TCCR1B |= (1<<CS11);
	TCCR1B &= ~(1<<CS12);
//	OCR1A=250;
	sei(); //Enable global interrupts
	
}
int main(void)
{
	USART_int(BAUD_PRESCALER);
	initialize_pwm();
	initialize_adc();
	while (1)
	{
		if(OCR1A>125&&OCR1A<625){
			if ((ADC*5/1024)==0){
				OCR1A--;

			}
			else if ((ADC*5/1024)==4){
				OCR1A++;

			}
		}
		else if (OCR1A<=125){
			OCR1A=126;
		}
		else if (OCR1A>=625){
			OCR1A=624;
		}
		_delay_ms(5);
		

	}
}