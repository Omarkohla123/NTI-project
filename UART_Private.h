/*
 * UART_Private.h
 *
 * Created: 6/27/2023 1:33:49 PM
 *  Author: Rizk
 */ 


#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_

#include "BIT_MATH.h"
#include "STD_TYPES.h"


#define UCSRA      *((volatile u8 * )0X2B)
#define UCSRB	   *((volatile u8 * )0X2A)
#define UCSRC	   *((volatile u8 * )0X40)
#define UBRRH      *((volatile u8 * )0X40)
#define UDR		   *((volatile u8 * )0X2C)
#define UBRRL      *((volatile u8 * )0X29)

#endif /* UART_PRIVATE_H_ */