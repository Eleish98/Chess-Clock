/************************************************/
/*	Author		:		Mohamed G. ELeish		*/
/*	Date		:		8 September 2021		*/
/*	Version		:		V01						*/
/************************************************/

/************************************************/
/************************************************/
/*****					LOG					*****/
/*	8/9/2021:	File Created					*/
/************************************************/
/************************************************/

#ifndef SEVENSEGMENT_INTERFACE_H_INCLUDED
#define SEVENSEGMENT_INTERFACE_H_INCLUDED

typedef enum{
	SEVENSEGMENT_TYPE_COMMON_ANODE,
	SEVENSEGMENT_TYPE_COMMON_CATHODE
}SEVENSEGMENT_Type_t;

typedef struct{
	SEVENSEGMENT_Type_t Type;
	GPIO_Port_t Ports[7];
	GPIO_Pin_t Pins[7];
}SEVENSEGMENT_t;

void HSEVENSEGMENT_voidInit(SEVENSEGMENT_t* SS);

void HSEVENSEGMENT_voidDisplay(SEVENSEGMENT_t* SS, u8 Copy_u8Number);

void HSEVENSEGMENT_voidTurnOff(SEVENSEGMENT_t* SS);

#endif

