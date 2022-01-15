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

#include "STK_interface.h"
#include "STK_private.h"



void MSTK_voidInit(STK_ClockSource_t Copy_ClockSource, u32 Copy_u32AHBClockFrequency){
	CLR_BIT(STK_REG->CTRL,2);
	STK_REG->CTRL |= (Copy_ClockSource << 2);
	if (Copy_ClockSource == STK_CLOCK_AHB_DIV_8)
		PSTK_u32TicksPerMicroSeconds = Copy_u32AHBClockFrequency/8000000;
	else
		PSTK_u32TicksPerMicroSeconds = Copy_u32AHBClockFrequency/1000000;
}

void MSTK_voidStop(void){
	CLR_BIT(STK_REG->CTRL, 0);
	CLR_BIT(STK_REG->CTRL,1);
}

void MSTK_voidSetBusyWaitUS(u32 Copy_u32MicroSec){
	STK_REG->LOAD = PSTK_u32TicksPerMicroSeconds*Copy_u32MicroSec;
	SET_BIT(STK_REG->CTRL, 0);
	while(!CHK_BIT(STK_REG->CTRL,16));
	CLR_BIT(STK_REG->CTRL, 0);
}

void MSTK_voidSetPeriodicInterval(u32 Copy_u32MicroSec, void(*CallBack)(void)){
	PSTK_voidUnderFlowCallBack = CallBack;
	STK_REG->LOAD = PSTK_u32TicksPerMicroSeconds*Copy_u32MicroSec-1;
	PSTK_u8SingleInterruptFlag = 0;
	SET_BIT(STK_REG->CTRL,1);
	SET_BIT(STK_REG->CTRL, 0);

}

void MSTK_voidSetSingleInterval(u32 Copy_u32MicroSec, void(*CallBack)(void)){
	PSTK_voidUnderFlowCallBack = CallBack;
	STK_REG->LOAD = PSTK_u32TicksPerMicroSeconds*Copy_u32MicroSec;
	PSTK_u8SingleInterruptFlag = 1;
	SET_BIT(STK_REG->CTRL,1);
	SET_BIT(STK_REG->CTRL, 0);
}

u32 MSTK_u32GetElapsedTime(void){
	return ((STK_REG->LOAD - STK_REG->VAL)/PSTK_u32TicksPerMicroSeconds);
}

u32 MSTK_u32GetRemainingTime(void){
	return (STK_REG->VAL/PSTK_u32TicksPerMicroSeconds);
}

void MSTK_voidClibrate(void){
	
}


void SysTick_Handler(void){
	if(PSTK_voidUnderFlowCallBack != 0)
		PSTK_voidUnderFlowCallBack();
	STK_REG->CTRL;
	if(PSTK_u8SingleInterruptFlag == 1)
		CLR_BIT(STK_REG->CTRL,1);
}


