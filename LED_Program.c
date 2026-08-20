#include "7_Segment_Interface.h"
#include "DIO_Interface.h"
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "LED_Config.h"
#include "LED_Interface.h"
#include "LED_Private.h"


void LED_INIT(u8 Copy_u8PortID,u8 Copy_u8PinID)
{
	DIO_voidSetPinDirection(Copy_u8PortID, Copy_u8PinID, PIN_OUTPUT);
}

void LED_ON (u8 Copy_u8PortID,u8 Copy_u8PinID)
{
	DIO_voidSetPinValue(Copy_u8PortID, Copy_u8PinID, PIN_HIGH);
}

void LED_OFF (u8 Copy_u8PortID,u8 Copy_u8PinID)
{
	DIO_voidSetPinValue(Copy_u8PortID, Copy_u8PinID, PIN_LOW);
}