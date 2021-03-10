/*
 * USART.c
 *
 * Created: 10/21/2020 6:45:11 PM
 *  Author: chen
 */ 
#include "USART.h"
#include <avr/io.h>
void USART_int(int BAUD_PRESCALER){
	/*Set baud rate */
	UBRR0H = (unsigned char)(BAUD_PRESCALER>>8);
	UBRR0L = (unsigned char)BAUD_PRESCALER;
	/*Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}
void USART_Transmit(unsigned char data){
/* Wait for empty transmit buffer */
while (!(UCSR0A & (1<<UDRE0))){

}
/* Put data into buffer, sends the data */
UDR0 = data;
}
void USART_print(char* StringPtr){
while (*StringPtr!=0){
USART_Transmit(*StringPtr);
StringPtr++;
}
}