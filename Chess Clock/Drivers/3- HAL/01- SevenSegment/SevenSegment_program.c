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



#include "1- LIB/STD_TYPES.h"
#include "1- LIB/BIT_MATH.h"

#include "2- MCAL/ST/05- GPIO/GPIO_interface.h"

#include "SevenSegment_interface.h"
#include "SevenSegment_private.h"

void HSEVENSEGMENT_voidInit(SEVENSEGMENT_t* SS){
	void (*PSevenSegment_voidClear)(GPIO_Port_t, GPIO_Pin_t) = (SS->Type == SEVENSEGMENT_TYPE_COMMON_ANODE)?	MGPIO_voidSetPin:MGPIO_voidClearPin;
	for(u8 i = 0; i < 7; i++){
		MGPIO_voidSetPinDirection(SS->Ports[i],SS->Pins[i],GPIO_DIR_OUTPUT_PUSH_PULL);
		PSevenSegment_voidClear(SS->Ports[i],SS->Pins[i]);
	}
}

void HSEVENSEGMENT_voidDisplay(SEVENSEGMENT_t* SS, u8 Copy_u8Number){

	if(Copy_u8Number > 9){
		HSEVENSEGMENT_voidTurnOff(SS);
		return;
	}
	Copy_u8Number = PSEVENSEGMENT_u8PtrCommonCathodeDigits[Copy_u8Number];
	if (SS->Type == SEVENSEGMENT_TYPE_COMMON_ANODE)
		Copy_u8Number = ~Copy_u8Number;
	for(u8 i = 0; i < 7; i++)
		MGPIO_voidSetPinValue(SS->Ports[i],SS->Pins[i],GET_BIT(Copy_u8Number,i));

}

void HSEVENSEGMENT_voidTurnOff(SEVENSEGMENT_t* SS){
	void (*PSevenSegment_voidClear)(GPIO_Port_t, GPIO_Pin_t) = (SS->Type == SEVENSEGMENT_TYPE_COMMON_ANODE)?	MGPIO_voidSetPin:MGPIO_voidClearPin;
	for(u8 i = 0; i < 7; i++){
		PSevenSegment_voidClear(SS->Ports[i],SS->Pins[i]);
	}
}


