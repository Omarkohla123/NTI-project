/*
 * _7_Segment_Config.h
 *
 * Created: 7/18/2023 7:05:33 PM
 *  Author: Rizk
 */ 


#ifndef SEGMENT_CONFIG_H_
#define SEGMENT_CONFIG_H_


#include "BIT_MATH.h"
#include "STD_TYPES.h"

/*********************************************/
/*                                           */
/*           7_Segment Decoder PINS          */
/*                                           */
/*********************************************/
#define SEGMANTA_PORT   PORTC_ID 
#define SEGMANTA_PIN    PIN0

#define SEGMANTB_PORT   PORTC_ID
#define SEGMANTB_PIN    PIN1

#define SEGMANTC_PORT   PORTC_ID
#define SEGMANTC_PIN    PIN2

#define SEGMANTD_PORT   PORTC_ID
#define SEGMANTD_PIN    PIN3

#define SEGMANTE_PORT   PORTC_ID
#define SEGMANTE_PIN    PIN4

#define SEGMANTF_PORT   PORTC_ID
#define SEGMANTF_PIN    PIN5

#define SEGMANTG_PORT   PORTC_ID
#define SEGMANTG_PIN    PIN6


#endif /* 7_SEGMENT_CONFIG_H_ */