
/*
 * CFile1.c
 *
 * Created: 6/13/2023 7:49:25 PM
 *  Author: Rizk
 */ 

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "ADC_Private.h"
#include "ADC_Interface.h"
#include "ADC_Config.h"


#define  NULL ((void*)0)



static void (*ptr_ArrCallBack[2])(void) = {NULL,NULL};

void ADC_INIT (void)
{
	/*  Select VCC as ref  */
		SET_BIT(ADMUX,6);
		CLR_BIT(ADMUX,7);
		
	/*  Right Adjust mode   */
	    CLR_BIT(ADMUX,5);	
		
	/*   Prescaller Select  */
        SET_BIT(ADCSRA,0);
        SET_BIT(ADCSRA,1);
        SET_BIT(ADCSRA,2);			
	
	/* Disable ADC Module */
	    CLR_BIT(ADCSRA,7);

	/* Disable ADC Interrupt PIE */
	    CLR_BIT(ADCSRA,3);

	/* Clear  Interrupt flag PIF */
	   SET_BIT(ADCSRA,4);
	
	/* Enable ADC Module */
	   SET_BIT(ADCSRA,7);

}

void ADC_CHANNEL_SELECT (u8 copy_adc_channel)
{
		/*CLEAR CHANNEL BITS IN ADMUX REGISTER*/
		ADMUX &= ADC_CHANNEL_MASK ;

		/*SELECT ADC CHANNEL      */
		ADMUX |= copy_adc_channel ;
		
}

void ADC_START_CONVERSION (void)
{
	/*   Start Conversion     */
	    SET_BIT(ADCSRA,6);	
}

u16 ADC_Read_value (u8 copy_adc_channel )
{
	ADC_CHANNEL_SELECT(copy_adc_channel);
	
	ADC_START_CONVERSION();

    /*   POLLING ON THE FLAG  */	
	   while((GET_BIT(ADCSRA,4))==0);
	
	/* Clear  Interrupt flag PIF */
	   SET_BIT(ADCSRA,4);
	
	return ADC ;
}











void ADC_INTEERUPT_INIT (void)
{
	/*  Select VCC as ref  */
	SET_BIT(ADMUX,6);
	CLR_BIT(ADMUX,7);
	
	/*  Right Adjust mode   */
	CLR_BIT(ADMUX,5);
	
	/*   Prescaller Select  */
	SET_BIT(ADCSRA,0);
	SET_BIT(ADCSRA,1);
	SET_BIT(ADCSRA,2);
	
	/* Disable ADC Module */
	CLR_BIT(ADCSRA,7);

	/* Enable ADC Interrupt PIE */
	SET_BIT(ADCSRA,3);

	/* Clear  Interrupt flag PIF */
	SET_BIT(ADCSRA,4);
	
	/* Enable ADC Module */
	SET_BIT(ADCSRA,7);

}


void ADC_INT_voidSetCallBack(void (*ptr_adc)(void))
{

	if(ptr_adc!=NULL)
	{
	
	 ptr_ArrCallBack[0]= ptr_adc;

	}
}



void  __vector_16() __attribute__((signal)) ;
void __vector_16 ()
{
	/* Clear  Interrupt flag PIF */
	SET_BIT(ADCSRA,4);

	/*CALLBACK FUNCTION*/
	ptr_ArrCallBack[0]();


}





void ADC_INTEERUPT_EXT0_INIT (void)
{
	/*  Select VCC as ref  */
	SET_BIT(ADMUX,6);
	CLR_BIT(ADMUX,7);
	
	/*  Right Adjust mode   */
	CLR_BIT(ADMUX,5);
	
	/*   Prescaller Select  */
	SET_BIT(ADCSRA,0);
	SET_BIT(ADCSRA,1);
	SET_BIT(ADCSRA,2);
	
	/* Disable ADC Module */
	CLR_BIT(ADCSRA,7);

	/* Enable ADC Interrupt PIE */
	SET_BIT(ADCSRA,3);
	
	/* Enable ADC  Auto trigger */
	SET_BIT(ADCSRA,5);
	
	
	/* Select EXT0 to Auto trigger ADC */
	CLR_BIT(SFIOR,5);
	SET_BIT(SFIOR,6);		
	CLR_BIT(SFIOR,7);	

	/* Clear  Interrupt flag PIF */
	SET_BIT(ADCSRA,4);
	
	/* Enable ADC Module */
	SET_BIT(ADCSRA,7);

}

