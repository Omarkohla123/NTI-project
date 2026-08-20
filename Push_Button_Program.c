
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_Interface.h"
#include "7_Segment_Interface.h"
#include "LED_Interface.h"
#include "Push_Button_Config.h"
#include "Push_Button_Interface.h"
#include "Push_Button_Private.h"


void PUSH_BUTTON_INIT(u8 Copy_u8PortID,u8 Copy_u8PinID) 
{
	DIO_voidSetPinDirection(Copy_u8PortID, Copy_u8PinID, PIN_INPUT);
}

u8 READ_PUSH_BUTTON (u8 Copy_u8PortID,u8 Copy_u8PinID)
{
	return	DIO_voidGetBitValue(Copy_u8PortID, Copy_u8PinID);
}