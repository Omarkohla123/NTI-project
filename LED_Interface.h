#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

#include "BIT_MATH.h"
#include "STD_TYPES.h"

void LED_INIT(u8 Copy_u8PortID,u8 Copy_u8PinID);

void LED_ON(u8 Copy_u8PortID,u8 Copy_u8PinID);
void LED_OFF(u8 Copy_u8PortID,u8 Copy_u8PinID);



#endif /* LED_INTERFACE_H_ */