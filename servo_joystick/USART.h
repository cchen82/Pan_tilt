/*
 * USART.h
 *
 * Created: 10/21/2020 6:45:57 PM
 *  Author: chen
 */ 


#ifndef USART_H_
#define USART_H_
void USART_int(int BAUD_PRESCALER);
void USART_Transmit(unsigned char data);
void USART_print(char* StringPtr);


#endif /* USART_H_ */