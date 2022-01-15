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

#include "NVIC_interface.h"
#include "NVIC_private.h"


void MNVIC_voidEnableInterrupt(NVIC_InterruptID_t Interrupt){
	if(Interrupt > NVIC_INTERRUPT_DMA2_CH4_5)
		return;
	NVIC_REG->ISER[Interrupt/32] = (1<<(Interrupt %32));
}

void MNVIC_voidDisableInterrupt(NVIC_InterruptID_t Interrupt){
	if(Interrupt > NVIC_INTERRUPT_DMA2_CH4_5)
		return;
	NVIC_REG->ICER[Interrupt/32] = (1<<(Interrupt %32));
}

void MNVIC_voidSetPendingFlag(NVIC_InterruptID_t Interrupt){
	if(Interrupt > NVIC_INTERRUPT_DMA2_CH4_5)
		return;
	NVIC_REG->ISPR[Interrupt/32] = (1<<(Interrupt %32));
}

void MNVIC_voidClearPendingFlag(NVIC_InterruptID_t Interrupt){
	if(Interrupt > NVIC_INTERRUPT_DMA2_CH4_5)
		return;
	NVIC_REG->ICPR[Interrupt/32] = (1<<(Interrupt %32));
}

u8 MNVIC_u8GetPendingFlag(NVIC_InterruptID_t Interrupt){
	if(Interrupt > NVIC_INTERRUPT_DMA2_CH4_5)
		return 0;
	return GET_BIT(NVIC_REG->ISPR[Interrupt/32],(Interrupt %32));
}

u8 MNVIC_u8GetActiveFlag(NVIC_InterruptID_t Interrupt){
	if(Interrupt > NVIC_INTERRUPT_DMA2_CH4_5)
		return 0;
	return GET_BIT(NVIC_REG->IABR[Interrupt/32],(Interrupt %32));
}

void MNVIC_voidSetInterruptPriority(NVIC_InterruptID_t Interrupt, NVIC_GroupPriority_t Group, NVIC_SubPriority_t Sub ){
	u8 Local_u8PriorityField = (Group<<(PNVIC_GroupingConfig) | Sub) & 0xF;
	Local_u8PriorityField <<= 4;
	NVIC_REG->IPR[Interrupt/4] &= ~(0xFF << ((Interrupt % 4)*8));
	NVIC_REG->IPR[Interrupt/4] |= (Local_u8PriorityField << ((Interrupt % 4)*8));
}


void MNVIC_voidInit(NVIC_Config_t Config){
	PNVIC_GroupingConfig = Config;
}
