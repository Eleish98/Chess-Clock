/************************************************/
/*	Author		:		Mohamed G. ELeish		*/
/*	Date		:		5 September 2021		*/
/*	Version		:		V01						*/
/************************************************/

/************************************************/
/************************************************/
/*****					LOG					*****/
/*	5/9/2021:	File Created					*/
/************************************************/
/************************************************/

#ifndef EXTI_INTERFACE_H_INCLUDED
#define EXTI_INTERFACE_H_INCLUDED

typedef enum{
	EXTI_LINE_0,
	EXTI_LINE_1,
	EXTI_LINE_2,
	EXTI_LINE_3,
	EXTI_LINE_4,
	EXTI_LINE_5,
	EXTI_LINE_6,
	EXTI_LINE_7,
	EXTI_LINE_8,
	EXTI_LINE_9,
	EXTI_LINE_10,
	EXTI_LINE_11,
	EXTI_LINE_12,
	EXTI_LINE_13,
	EXTI_LINE_14,
	EXTI_LINE_15,
	EXTI_LINE_16,
	EXTI_LINE_17,
	EXTI_LINE_18
	
}EXTI_LineID_t;

typedef enum{
	EXTI_TRIGGER_RISING_EDGE,
	EXTI_TRIGGER_FALLING_EDGE,
	EXTI_TRIGGER_ANY_CHANGE
}EXTI_Trigger_t;

void MEXTI_voidConfigureLineTrigger(EXTI_LineID_t Line, EXTI_Trigger_t Trigger);

void MEXTI_voidEnableInterrupt(EXTI_LineID_t Line);

void MEXTI_voidEnableEvent(EXTI_LineID_t Line);

void MEXTI_voidDisableInterrupt(EXTI_LineID_t Line);

void MEXTI_voidDisableEvent(EXTI_LineID_t Line);

void MEXTI_voidSetSoftwareTrigger(EXTI_LineID_t Line);

void MEXTI_voidSetCallBack(EXTI_LineID_t Line, void(*CAllBack)(void));

u8 MEXTI_u8GetPendingFlag(EXTI_LineID_t Line);

void MEXT_voidClearPendingFlag(EXTI_LineID_t Line);
#endif

