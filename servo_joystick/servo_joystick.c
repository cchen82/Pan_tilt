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
	//PD5 as output
	DDRD |= (1<<DDD5);
	
	//Configure timer mode to Phase Correct PWM (101)
	//(101) TOP vale is OCRA instead of set value of 0XFF
	TCCR0A |= (1<<WGM00);
	TCCR0A &= ~(1<<WGM01);
	TCCR0B |= (1<<WGM02);
	
	//Configure timer pre-scaler (100) /256
	TCCR0B &= ~(1<<CS00);
	TCCR0B &= ~(1<<CS01);
	TCCR0B |= (1<<CS02);

	//Configure Output Compare Register A/B
	OCR0A=80;
	OCR0B=OCR0A/2;
	//Non-inverting mode
	//Clear on compare match
	TCCR0A |= (1<<COM0B1);
	sei(); //Enable global interrupts
	
}
int main(void)
{
	USART_int(BAUD_PRESCALER);
	initialize_pwm();
	initialize_adc();
	while (1)
	{
		//int i=30;
		if(OCR0A>30&&OCR0A<160){
			if ((ADC*5/1024)==0){
				OCR0A--;
				OCR0B=OCR0A/2;
				sprintf(str_print,"%d\n",OCR0A);
				USART_print(str_print);
			}
			else if ((ADC*5/1024)==4){
				OCR0A++;
				OCR0B=OCR0A/2;
				sprintf(str_print,"%d\n",OCR0A);
				USART_print(str_print);
			}
		}
		else if (OCR0A<=30){
			OCR0A=31;
			OCR0B=OCR0A/2;
		}
		else if (OCR0A>=160){
			OCR0A=159;
			OCR0B=OCR0A/2;
		}
		_delay_ms(10);
		
		//for (int i=0;i<180;i++){
			//OCR0A=i;
			//OCR0B=i/2;
			//_delay_ms(10);
		//}
		//OCR0A = 65;	/* Set servo shaft at -90° position */
		//OCR0B=OCR0A/2;
		//_delay_ms(1500);
		//
		//OCR0A = 175;	/* Set servo shaft at 0° position */
		//OCR0B=OCR0A/2;
		//_delay_ms(1500);

	}
}