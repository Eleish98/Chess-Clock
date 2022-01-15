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

#include "AFIO_interface.h"
#include "AFIO_private.h"


void MAFIO_voidSetEXTIConfiguration(AFIO_EXTIID_t EXTILine, AFIO_PORTID_t PortMap){
	if(EXTILine > AFIO_EXTI_LINE15)
		return;
	AFIO_REG->EXTICR[EXTILine/4] &= ~(0xF << (EXTILine%4));
	AFIO_REG->EXTICR[EXTILine/4] |= (PortMap << ((EXTILine%4)*4));
}

void MAFIO_voidEnableEventOutput(AFIO_PORTID_t Port, u8 Pin){
	AFIO_REG->EVCR = (1<<7)|(Port<<4)|Pin;
}

void MAFIO_voidDisableEventOutput(void){
	AFIO_REG->EVCR = 0;
}

void MAFIO_voidSetJTAGConfiguration(AFIO_JTAGMode_t Mode){
	AFIO_REG->MAPR &= ~(7<<24);
	AFIO_REG->MAPR |= (Mode << 24);
}


void MAFIO_voidRemapADC2RegularTrigger(AFIO_ADCRegularTrigger_t TriggerSource){
	CLR_BIT(AFIO_REG->MAPR,20);
	AFIO_REG->MAPR |= (TriggerSource & 1)<<20;
}

void MAFIO_voidRemapADC2InjectedTrigger(AFIO_ADCInjectedTrigger_t TriggerSource){
	CLR_BIT(AFIO_REG->MAPR,19);
	AFIO_REG->MAPR |= (TriggerSource & 1)<<19;
}

void MAFIO_voidRemapADC1RegularTrigger(AFIO_ADCRegularTrigger_t TriggerSource){
	CLR_BIT(AFIO_REG->MAPR,18);
	AFIO_REG->MAPR |= (TriggerSource & 1)<<18;
}

void MAFIO_voidRemapADC1InjectedTrigger(AFIO_ADCInjectedTrigger_t TriggerSource){
	CLR_BIT(AFIO_REG->MAPR,17);
	AFIO_REG->MAPR |= (TriggerSource & 1)<<17;
}

void MAFIO_RemapPD01(AFIO_PD01Mode_t Mode){
	CLR_BIT(AFIO_REG->MAPR,15);
	AFIO_REG->MAPR |= (Mode << 15);
}

void MAFIO_voidRemapCAN(AFIO_CANMode_t Mode){
	AFIO_REG->MAPR &= ~(3 << 13);
	AFIO_REG->MAPR |= (Mode << 13);
}

void MAFIO_voidRemapTIM4(AFIO_TIM4Mode_t Mode){
	CLR_BIT(AFIO_REG->MAPR,12);
	AFIO_REG->MAPR |= (Mode << 12);
}

void MAFIO_voidRemapTIM3(AFIO_TIM3Mode_t Mode){
	AFIO_REG->MAPR &= ~(3 << 10);
	AFIO_REG->MAPR |= (Mode << 10);
}

void MAFIO_voidRemapTIM2(AFIO_TIM2Mode_t Mode){
	AFIO_REG->MAPR &= ~(3 << 8);
	AFIO_REG->MAPR |= (Mode << 8);
}


void MAFIO_voidRemapTIM1(AFIO_TIM1Mode_t Mode){
	AFIO_REG->MAPR &= ~(3 << 6);
	AFIO_REG->MAPR |= (Mode << 6);
}


void MAFIO_voidRemapUSART3(AFIO_USART3Mode_t Mode){
	AFIO_REG->MAPR &= ~(3 << 4);
	AFIO_REG->MAPR |= (Mode << 4);
}


void MAFIO_voidRemapUSART2(AFIO_USART2Mode_t Mode){
	CLR_BIT(AFIO_REG->MAPR,3);
	AFIO_REG->MAPR |= (Mode << 3);
}


void MAFIO_voidRemapUSART1(AFIO_USART1Mode_t Mode){
	CLR_BIT(AFIO_REG->MAPR,2);
	AFIO_REG->MAPR |= (Mode << 2);
}


void MAFIO_voidRemapI2C1(AFIO_I2C1Mode_t Mode){
	CLR_BIT(AFIO_REG->MAPR,1);
	AFIO_REG->MAPR |= (Mode << 1);
}


void MAFIO_voidRemapSPI1(AFIO_SPI1Mode_t Mode){
	CLR_BIT(AFIO_REG->MAPR,0);
	AFIO_REG->MAPR |= (Mode << 0);
}


void MAFIO_voidRemapFSMC(AFIO_FSMCMode_t Mode){
	CLR_BIT(AFIO_REG->MAPR2,10);
	AFIO_REG->MAPR2 |= (Mode << 10);
}

void MAFIO_voidRemapTIM14(AFIO_TIM14Mode_t Mode){
	CLR_BIT(AFIO_REG->MAPR2,9);
	AFIO_REG->MAPR2 |= (Mode << 9);
}

void MAFIO_voidRemapTIM13(AFIO_TIM13Mode_t Mode){
	CLR_BIT(AFIO_REG->MAPR2,8);
	AFIO_REG->MAPR2 |= (Mode << 8);
}

void MAFIO_voidRemapTIM11(AFIO_TIM11Mode_t Mode){
	CLR_BIT(AFIO_REG->MAPR2,7);
	AFIO_REG->MAPR2 |= (Mode << 7);
}

void MAFIO_voidRemapTIM10(AFIO_TIM10Mode_t Mode){
	CLR_BIT(AFIO_REG->MAPR2,6);
	AFIO_REG->MAPR2 |= (Mode << 6);
}
void MAFIO_voidRemapTIM9(AFIO_TIM9Mode_t Mode){
	CLR_BIT(AFIO_REG->MAPR2,5);
	AFIO_REG->MAPR2 |= (Mode << 5);
}




