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
void initialize_adc_joystick(){
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
//servo with joystick is on PD5
void initialize_pwm_joyservo (){
	cli();//disable all interrupts
	DDRD |= (1<<DDD5);	/* Make OC1A pin (~D9) OC1B (~D10) as output */
	//Use Timer 0 for joystick to servo
	//prescale of 1024 (101)
	TCCR0B |= (1<<CS02);
	TCCR0B &= ~(1<<CS01);
	TCCR0B |= (1<<CS00);
	
	//Fast PWM mode
	TCCR0A |= (1<<WGM00);
	TCCR0A |= (1<<WGM01);
	TCCR0B |= (1<<WGM02);
	
	//OCR0A sets frequency
	//OCR0B sets duty cycle
	OCR0A=255;
	OCR0B=OCR0A/2;
	
	//Non-inverting mode
	//Clear on compare match
	TCCR0A |= (1<<COM1B1);
	sei(); //Enable global interrupts
	
}
int main(void)
{
	USART_int(BAUD_PRESCALER);
	initialize_pwm_joyservo();
	initialize_adc_joystick();
	while (1)
	{
		if(OCR0B>10&&OCR0B<40){
			if ((ADC*5/1024)==0){
				OCR0B--;
			}
			else if ((ADC*5/1024)==4){
				OCR0B++;

			}
		}
		else if (OCR0B<=10){
			OCR0B=11;
		}
		else if (OCR0B>=40){
			OCR0B=39;
		}
		_delay_ms(25);

	}
}