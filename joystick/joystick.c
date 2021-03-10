/*
 * final_project.c
 *
 * Created: 11/20/2020 6:25:04 AM
 * Author : chen
 */ 

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "USART.h"
#define F_CPU 16000000UL
#define BAUD_RATE 9600
#define BAUD_PRESCALER (((F_CPU / (BAUD_RATE * 16UL))) - 1)
char str_print[20];
void initialize(){
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
ISR (ADC_vect){
	//Print ADC value
	sprintf(str_print,"%d\n",ADC*5/1024);
	USART_print(str_print);
}
int main(){
	initialize();
	USART_int(BAUD_PRESCALER);
	while(1){
		//sprintf(str_print,"%d\n",ADC*5/1024);
		//USART_print(str_print);
		}
}