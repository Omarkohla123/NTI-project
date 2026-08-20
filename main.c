#define F_CPU 8000000UL

#include <stdio.h>
#include <util/delay.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "7_Segment_Interface.h"
#include "DIO_Interface.h"
#include "LED_Interface.h"
#include "Push_Button_Interface.h"
#include "LCD_Interface.h"
#include "EXT_Interface.h"
#include "GIE_Interface.h"
#include "ADC_Interface.h"
#include "UART_Interface.h"

/********************** Functions prototypes ***********************/

void FIRE_OR_GAS(void);



//***************************************************************************************************************

int main(void)
{
	LCD_voidInit(); 
	ADC_INIT();
	
	USART_Init(9600);
	USART_Transmit('K');   // Transmit Line as an indicator for the functionality of the connection
	
	/******************  ALARM SYSTEM  *******************/
	EXT_voidSetCallBack(FIRE_OR_GAS, EXT0);
	EXT_voidInit(EXT0, RISING_EDGE);
	GIE_Enable();
	
	LED_INIT(PORTD_ID, PIN3);  // RED LED
	LED_INIT(PORTD_ID, PIN4);  // Buzzer
	LED_INIT(PORTD_ID, PIN5);  // Green LED (normal case)
	
	DIO_voidSetPinDirection(PORTD_ID, PIN6, PIN_INPUT);  // Rain Sensor Pin
	
	
	/*****************  GRADUAL FAN   ********************/

	
	u16 adcValue;              //0 -> 1023
	u16 temperature;
	
	Lcd_Goto_Row_Column(1, 0);
	Lcd_DisplayStr("Temp =   C");
	
	DIO_voidSetPortDirection(PORTB_ID, ALL_PORT_OUTPUT);
	
	
	/********  AC LAMP CONTROL ************/
	
	u32 LDR_Digital_Value;
	 
	DIO_voidSetPinDirection(PORTA_ID, PIN2, PIN_OUTPUT);  // LAMP Control Pin A2
	DIO_voidSetPinDirection(PORTA_ID, PIN3, PIN_INPUT);   // Automatic Control Select Pin A3 
	DIO_voidSetPinDirection(PORTA_ID, PIN4, PIN_INPUT);   // Manual Control Select Pin A4
	DIO_voidSetPinDirection(PORTA_ID, PIN5, PIN_INPUT);   // Wireless Control Select Pin A5
	DIO_voidSetPinDirection(PORTA_ID, PIN6, PIN_INPUT);   // Manual switch Pin A6
	  
	Lcd_Goto_Row_Column(3, 0);
	Lcd_DisplayStr("Time: ");
	
		
	
	
	
	while (1)
	{
	/***************** ALARM SYSTEM  ******************/
		LED_ON(PORTD_ID, PIN5);  // Green ON (Alarm normal case)
		
		if (DIO_voidGetBitValue(PORTD_ID, PIN6))      // if it is raining
		{
			Lcd_Goto_Row_Column(2, 0);
			Lcd_DisplayStr("It's raining outside");
			_delay_ms(100);   // to prevent the LCD from flickering
		}
		else
		{
			Lcd_Goto_Row_Column(2, 0);
			Lcd_DisplayStr("                    ");  // to erase the raining alarm
		}
		
	/***********************  GRADUAL FAN   *******************************/
		
		ADC_CHANNEL_SELECT(ADC_CHANNEL0);
		adcValue = ADC_Read_value(ADC_CHANNEL0);  // LM35 A0

		temperature = (u16)(((u32)adcValue * 500UL + 512UL) / 1024UL);		
		Lcd_Goto_Row_Column(1, 7);
		Lcd_Displaynum(temperature);
		_delay_ms(150);

		if (temperature < 30)
		{
			DIO_voidSetPinValue(PORTB_ID,PIN0,PIN_LOW);
			DIO_voidSetPinValue(PORTB_ID,PIN1,PIN_LOW);
			DIO_voidSetPinValue(PORTB_ID,PIN2,PIN_LOW);
			DIO_voidSetPinValue(PORTB_ID,PIN3,PIN_LOW);
			DIO_voidSetPinValue(PORTB_ID,PIN4,PIN_LOW);
			DIO_voidSetPinValue(PORTB_ID,PIN5,PIN_LOW);
			DIO_voidSetPinValue(PORTB_ID,PIN6,PIN_LOW);   // 0b 00000000
			DIO_voidSetPinValue(PORTB_ID,PIN7,PIN_LOW);
		}
		else if (temperature >= 30 && temperature < 40)
		{
			DIO_voidSetPinValue(PORTB_ID,PIN0,PIN_LOW);
			DIO_voidSetPinValue(PORTB_ID,PIN1,PIN_LOW);
			DIO_voidSetPinValue(PORTB_ID,PIN2,PIN_LOW);
			DIO_voidSetPinValue(PORTB_ID,PIN3,PIN_LOW);
			DIO_voidSetPinValue(PORTB_ID,PIN4,PIN_LOW);
			DIO_voidSetPinValue(PORTB_ID,PIN5,PIN_LOW);
			DIO_voidSetPinValue(PORTB_ID,PIN6,PIN_HIGH);  // 0b01000000 -> 64  ----> 1.25V
			DIO_voidSetPinValue(PORTB_ID,PIN7,PIN_LOW);

		}
		else if (temperature >= 40 && temperature < 50)
		{
			DIO_voidSetPinValue(PORTB_ID,PIN0,PIN_LOW);
			DIO_voidSetPinValue(PORTB_ID,PIN1,PIN_LOW);
			DIO_voidSetPinValue(PORTB_ID,PIN2,PIN_LOW);
			DIO_voidSetPinValue(PORTB_ID,PIN3,PIN_LOW);
			DIO_voidSetPinValue(PORTB_ID,PIN4,PIN_LOW);
			DIO_voidSetPinValue(PORTB_ID,PIN5,PIN_LOW);  // 0b10000000  -> 128     ------> 2.5V
			DIO_voidSetPinValue(PORTB_ID,PIN6,PIN_LOW);
			DIO_voidSetPinValue(PORTB_ID,PIN7,PIN_HIGH);
		}
		else if (temperature >= 50 && temperature < 60)
		{
			DIO_voidSetPinValue(PORTB_ID,PIN0,PIN_LOW);
			DIO_voidSetPinValue(PORTB_ID,PIN1,PIN_LOW);
			DIO_voidSetPinValue(PORTB_ID,PIN2,PIN_LOW);
			DIO_voidSetPinValue(PORTB_ID,PIN3,PIN_LOW);
			DIO_voidSetPinValue(PORTB_ID,PIN4,PIN_LOW);
			DIO_voidSetPinValue(PORTB_ID,PIN5,PIN_LOW);
			DIO_voidSetPinValue(PORTB_ID,PIN6,PIN_HIGH);  // 0b11000000  -> 192   -------> 3.75V
			DIO_voidSetPinValue(PORTB_ID,PIN7,PIN_HIGH);
		}
		else
		{
			DIO_voidSetPinValue(PORTB_ID,PIN0,PIN_HIGH);
			DIO_voidSetPinValue(PORTB_ID,PIN1,PIN_HIGH);
			DIO_voidSetPinValue(PORTB_ID,PIN2,PIN_HIGH);
			DIO_voidSetPinValue(PORTB_ID,PIN3,PIN_HIGH);
			DIO_voidSetPinValue(PORTB_ID,PIN4,PIN_HIGH);
			DIO_voidSetPinValue(PORTB_ID,PIN5,PIN_HIGH);
			DIO_voidSetPinValue(PORTB_ID,PIN6,PIN_HIGH);   //0b11111111
			DIO_voidSetPinValue(PORTB_ID,PIN7,PIN_HIGH);

		}
		
		
	/********************* AC LAMP  *****************************/

		ADC_CHANNEL_SELECT(ADC_CHANNEL1);
		LDR_Digital_Value = ADC_Read_value(ADC_CHANNEL1);   //0 -> 1023
		
		u8 Wireless_received_data = 0;
		if(USART_Available()){              // if there is data to be received 
			Wireless_received_data=USART_Receive();
		}
			
		if (LDR_Digital_Value > 500 )
		{
			Lcd_Goto_Row_Column(3, 6);
			Lcd_DisplayStr("     ");     // clear 5 places
			
			Lcd_Goto_Row_Column(3, 6);
			Lcd_DisplayStr("Day");
			_delay_ms(150);
		}
		else if (LDR_Digital_Value <= 500)
		{
			Lcd_Goto_Row_Column(3, 6);
			Lcd_DisplayStr("     ");     // clear 5 places
			
			Lcd_Goto_Row_Column(3, 6);
			Lcd_DisplayStr("Night");
			_delay_ms(150);
		}
		
		if(LDR_Digital_Value > 500 && DIO_voidGetBitValue(PORTA_ID,PIN3)==PIN_HIGH)  //Day, Selected Automatic Control
		{
			
			DIO_voidSetPinValue(PORTA_ID, PIN2, PIN_LOW);  // Turn the Lamp OFF
			
		}
		else if(LDR_Digital_Value <= 500 && DIO_voidGetBitValue(PORTA_ID,PIN3)==PIN_HIGH)  //Night, Selected Automatic Control
		{
			
			DIO_voidSetPinValue(PORTA_ID, PIN2, PIN_HIGH);  // Turn the Lamp ON
			
		}
		
		else if(DIO_voidGetBitValue(PORTA_ID,PIN6)==PIN_HIGH && DIO_voidGetBitValue(PORTA_ID,PIN4)==PIN_HIGH){   //Switch ON, Selected Manual Control
			
			DIO_voidSetPinValue(PORTA_ID, PIN2, PIN_HIGH);  
			
		}
		else if(DIO_voidGetBitValue(PORTA_ID,PIN6)==PIN_LOW && DIO_voidGetBitValue(PORTA_ID,PIN4)==PIN_HIGH)  //Switch OFF, Selected Manual Control
		{
			
			DIO_voidSetPinValue(PORTA_ID, PIN2, PIN_LOW);
		
		}
		
		else if (Wireless_received_data == 'H' && DIO_voidGetBitValue(PORTA_ID, PIN5) == 1)  // High received, Selected Wireless Control 
		{
			DIO_voidSetPinValue(PORTA_ID, PIN2, PIN_HIGH);
		}
		else if (Wireless_received_data == 'L' && DIO_voidGetBitValue(PORTA_ID, PIN5) == 1)  // Low received, Selected Wireless Control
		{
			DIO_voidSetPinValue(PORTA_ID, PIN2, PIN_LOW);
		}
		
	}

	}

	


//*****************************************************************************************************************



/********************** Functions Implementations ***********************/

void FIRE_OR_GAS(void) 
{
	LED_ON(PORTD_ID, PIN3);  // RED ON  D3
	LED_ON(PORTD_ID, PIN4);  // Buzzer ON  D4
	LED_OFF(PORTD_ID, PIN5);  // Green OFF  D5
	
	/*  wait until the alarm signal is gone */
	while (DIO_voidGetBitValue(PORTD_ID, PIN2))
	{
		Lcd_Goto_Row_Column(0, 3);
		Lcd_DisplayStr("WARNING");
		_delay_ms(275);
		
		Lcd_Goto_Row_Column(0, 3);
		Lcd_DisplayStr("       ");
		_delay_ms(35);
	}
	_delay_ms(10);           // small delay for debouncing
	
	/*  Return to normal state  */
	LED_OFF(PORTD_ID, PIN3);   // RED OFF
	LED_OFF(PORTD_ID, PIN4);   // Buzzer OFF
	LED_ON(PORTD_ID, PIN5);    // Green ON
}