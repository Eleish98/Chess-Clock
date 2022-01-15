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

#include "1- LIB/STD_TYPES.h"
#include "1- LIB/BIT_MATH.h"

#include "EXTI_interface.h"
#include "EXTI_private.h"



void MEXTI_voidConfigureLineTrigger(EXTI_LineID_t Line, EXTI_Trigger_t Trigger){
	if(Line > EXTI_LINE_18)
		return;
	if(Trigger == EXTI_TRIGGER_FALLING_EDGE){
		CLR_BIT(EXTI_REG->RTSR,Line);
		SET_BIT(EXTI_REG->FTSR,Line);
	}
	else if(Trigger == EXTI_TRIGGER_RISING_EDGE){
		CLR_BIT(EXTI_REG->FTSR,Line);
		SET_BIT(EXTI_REG->RTSR,Line);
	}
	else if(Trigger == EXTI_TRIGGER_ANY_CHANGE){
		SET_BIT(EXTI_REG->FTSR,Line);
		SET_BIT(EXTI_REG->RTSR,Line);
	}
}


void MEXTI_voidEnableInterrupt(EXTI_LineID_t Line){
	if(Line > EXTI_LINE_18)
		return;
	SET_BIT(EXTI_REG->IMR,Line);
}

void MEXTI_voidEnableEvent(EXTI_LineID_t Line){
	if(Line > EXTI_LINE_18)
		return;
	SET_BIT(EXTI_REG->EMR,Line);
}

void MEXTI_voidDisableInterrupt(EXTI_LineID_t Line){
	if(Line > EXTI_LINE_18)
		return;
	CLR_BIT(EXTI_REG->IMR,Line);
}

void MEXTI_voidDisableEvent(EXTI_LineID_t Line){
	if(Line > EXTI_LINE_18)
		return;
	CLR_BIT(EXTI_REG->EMR,Line);
}

void MEXTI_voidSetSoftwareTrigger(EXTI_LineID_t Line){
	if(Line > EXTI_LINE_18)
		return;
	SET_BIT(EXTI_REG->SWIER,Line);
}

void MEXTI_voidSetCallBack(EXTI_LineID_t Line, void(*CAllBack)(void)){
	if(Line > EXTI_LINE_18)
		return;
	PEXTI_CallBacks[Line] = CAllBack;
}


u8 MEXTI_u8GetPendingFlag(EXTI_LineID_t Line){
	if(Line > EXTI_LINE_18)
		return 0;
	return GET_BIT(EXTI_REG->PR,Line);
}

void MEXT_voidClearPendingFlag(EXTI_LineID_t Line){
	if(Line > EXTI_LINE_18)
		return;
	SET_BIT(EXTI_REG->PR,Line);
}


void EXTI0_IRQHandler(void){
	if(PEXTI_CallBacks[0] != 0)
		PEXTI_CallBacks[0]();
	SET_BIT(EXTI_REG->PR,0);
}

void EXTI1_IRQHandler(void){
	if(PEXTI_CallBacks[1] != 0)
		PEXTI_CallBacks[1]();
	SET_BIT(EXTI_REG->PR,1);
}

void EXTI2_IRQHandler(void){
	if(PEXTI_CallBacks[2] != 0)
		PEXTI_CallBacks[2]();
	SET_BIT(EXTI_REG->PR,2);
}

void EXTI3_IRQHandler(void){
	if(PEXTI_CallBacks[3] != 0)
		PEXTI_CallBacks[3]();
	SET_BIT(EXTI_REG->PR,3);
}

void EXTI4_IRQHandler(void){
	if(PEXTI_CallBacks[4] != 0)
		PEXTI_CallBacks[4]();
	SET_BIT(EXTI_REG->PR,4);
}

void EXTI9_5_IRQHandler(void){
	if(CHK_BIT(EXTI_REG->PR,5)){
		if(PEXTI_CallBacks[5] != 0)
			PEXTI_CallBacks[5]();
		SET_BIT(EXTI_REG->PR,5);
	}
	
	if(CHK_BIT(EXTI_REG->PR,6)){
		if(PEXTI_CallBacks[6] != 0)
			PEXTI_CallBacks[6]();
		SET_BIT(EXTI_REG->PR,6);
	}
	
	if(CHK_BIT(EXTI_REG->PR,7)){
		if(PEXTI_CallBacks[7] != 0)
			PEXTI_CallBacks[7]();
		SET_BIT(EXTI_REG->PR,7);
	}
	
	if(CHK_BIT(EXTI_REG->PR,8)){
		if(PEXTI_CallBacks[8] != 0)
			PEXTI_CallBacks[8]();
		SET_BIT(EXTI_REG->PR,8);
	}
	
	if(CHK_BIT(EXTI_REG->PR,9)){
		if(PEXTI_CallBacks[9] != 0)
			PEXTI_CallBacks[9]();
		SET_BIT(EXTI_REG->PR,9);
	}
	
}

void EXTI10_15IRQHandler(void){
	if(CHK_BIT(EXTI_REG->PR,10)){
		if(PEXTI_CallBacks[10] != 0)
			PEXTI_CallBacks[10]();
		SET_BIT(EXTI_REG->PR,10);
	}
	
	if(CHK_BIT(EXTI_REG->PR,11)){
		if(PEXTI_CallBacks[11] != 0)
			PEXTI_CallBacks[11]();
		SET_BIT(EXTI_REG->PR,11);
	}
	if(CHK_BIT(EXTI_REG->PR,12)){
		if(PEXTI_CallBacks[12] != 0)
			PEXTI_CallBacks[12]();
		SET_BIT(EXTI_REG->PR,12);
	}
	if(CHK_BIT(EXTI_REG->PR,13)){
		if(PEXTI_CallBacks[13] != 0)
			PEXTI_CallBacks[13]();
		SET_BIT(EXTI_REG->PR,13);
	}
	if(CHK_BIT(EXTI_REG->PR,14)){
		if(PEXTI_CallBacks[14] != 0)
			PEXTI_CallBacks[14]();
		SET_BIT(EXTI_REG->PR,14);
	}
	if(CHK_BIT(EXTI_REG->PR,15)){
		if(PEXTI_CallBacks[15] != 0)
			PEXTI_CallBacks[15]();
		SET_BIT(EXTI_REG->PR,15);
	}
}


void PVD_IRQHandler(void){
	if(CHK_BIT(EXTI_REG->PR,16)){
		if(PEXTI_CallBacks[16] != 0)
			PEXTI_CallBacks[16]();
		SET_BIT(EXTI_REG->PR,16);
	}
}


void RTCAlarm_IRQHandler(void){
	if(CHK_BIT(EXTI_REG->PR,17)){
		if(PEXTI_CallBacks[17] != 0)
			PEXTI_CallBacks[17]();
		SET_BIT(EXTI_REG->PR,17);
	}

}

void USBWakeUp_IRQHandler(void){
	if(CHK_BIT(EXTI_REG->PR,18)){
		if(PEXTI_CallBacks[18] != 0)
			PEXTI_CallBacks[18]();
		SET_BIT(EXTI_REG->PR,18);
	}
}

