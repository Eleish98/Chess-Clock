/************************************************/
/*	Author		:		Mohamed G. ELeish		*/
/*	Date		:		4 September 2021		*/
/*	Version		:		V01						*/
/************************************************/

/************************************************/
/************************************************/
/*****					LOG					*****/
/*	4/9/2021:	File Created					*/
/************************************************/
/************************************************/
#include "1- LIB/STD_TYPES.h"
#include "1- LIB/BIT_MATH.h"

#include "RCC_interface.h"
#include "RCC_private.h"
#include "RCC_config.h"

void MRCC_voidInitClock(void){
	/**** Set CPU Clock Source ****/
	#if RCC_SYSETEM_CLOCK == RCC_CLOCK_HSE
		//wait for the HSE Clock to be stable
		while(!CHK_BIT((RCC_REG->CR),17));
		#if RCC_HSE_SOURCE == RCC_HSE_CRYSTAL
			//Enable CSS, HSEON, Disable HSEBYP
			RCC_REG->CR = 0x00090000;
		#else
			//Enable CSS, HSEON, HSEBYP
			RCC_REG->CR = 0x000D0000;
		#endif
		//Switch to HSE
		RCC_REG->CFGR = 1;
	#elif RCC_SYSETEM_CLOCK == RCC_CLOCK_PLL
		
		#if RCC_PLL_CLOCK_SOURCE == RCC_HSI_DIV_2
			//wait for the HSI Clock to be stable
			while(!CHK_BIT((RCC_REG->CR),1));
			//Enable HSI
			RCC_REG->CR = 0x00000001;
			//Switch to HSI
			RCC_REG->CFGR &= ~3;
			//Disable PLL
			CLR_BIT(RCC_REG->CR,24);
			//Set PLL source
			CLR_BIT(RCC_REG->CFGR,16);
		#else
			//wait for the HSE Clock to be stable
			while(!CHK_BIT((RCC_REG->CR),17));
			#if RCC_HSE_SOURCE == RCC_HSE_CRYSTAL
			//Enable CSS, HSEON, Disable HSEBYP
			RCC_REG->CR = 0x00090000;
			#else
			//Enable CSS, HSEON, HSEBYP
			RCC_REG->CR = 0x000D0000;
			#endif
		//Switch to HSE
		RCC_REG->CFGR &= ~3;
		SET_BIT(RCC_REG->CR,0);
		//Disable PLL
		CLR_BIT(RCC_REG->CR,24);

		//Set PLL source
		SET_BIT(RCC_REG->CFGR,16);
		#if RCC_PLL_CLOCK_SOURCE == RCC_HSE_DIV_2
		SET_BIT((RCC_REG->CFGR),17);
		#endif
		//Set PLL Multiplier
		RCC_REG->CFGR &= ~(0xF << 18);
		RCC_REG->CFGR |= (RCC_PLL_MULIPLIER<<18);
		//Enable PLL
		SET_BIT(RCC_REG->CR,24);
		//Wait for PLL Clock to be Stable
		while(!CHK_BIT((RCC_REG->CR),25));
		//Switch to PLL
		RCC_REG->CFGR &= ~3;
		RCC_REG->CFGR |= 2;
		#endif
	#elif RCC_SYSETEM_CLOCK == RCC_CLOCK_HSI
		//wait for the HSI Clock to be stable
		while(!CHK_BIT((RCC_REG->CR),1));
		//Enable HSI
		RCC_REG->CR = 0x00000001;
		//Switch to HSI
		RCC_REG->CFGR = 0;
	#endif
	

	/***	Set RTC Clock Source	***/

	/*****	Set Buses and Peripherals Prescalars' ****/
	//Clear All Prescalar Bits
	RCC_REG->CFGR &= ~((1<<2)|(3<<14)|(0x3FF << 4));

	//Set All Prescalar at once
	RCC_REG->CFGR |= (RCC_USB_PRESCALAR << 22) |(RCC_AHB_PRESCALAR << 4)
					| (RCC_APB1_PRESCALAR << 8) | (RCC_APB2_PRESCALAR << 11)
					| (RCC_ADC_PRESCALAR << 14);

}

void MRCC_voidEnablePeripheral(RCC_PeripheralID_t Copy_Peripheral){

	if(Copy_Peripheral >= RCC_PER_DMA1 && Copy_Peripheral <= RCC_PER_SDIO){
		SET_BIT(RCC_REG->AHBENR,(Copy_Peripheral - RCC_PER_DMA1));
	}
	else if (Copy_Peripheral >= RCC_PER_AFIO){
		SET_BIT(RCC_REG->APB2ENR,(Copy_Peripheral - RCC_PER_AFIO));
	}
	else if(Copy_Peripheral >= RCC_PER_TIM2){
		SET_BIT(RCC_REG->APB1ENR,Copy_Peripheral);
	}

}

void MRCC_voidDisablePeripheral(RCC_PeripheralID_t Copy_Peripheral){

	if(Copy_Peripheral >= RCC_PER_DMA1 && Copy_Peripheral <= RCC_PER_SDIO){
		CLR_BIT(RCC_REG->AHBENR,(Copy_Peripheral - RCC_PER_DMA1));
	}
	else if (Copy_Peripheral >= RCC_PER_AFIO){
		CLR_BIT(RCC_REG->APB2ENR,(Copy_Peripheral - RCC_PER_AFIO));
	}
	else if(Copy_Peripheral >= RCC_PER_TIM2){
		CLR_BIT(RCC_REG->APB1ENR,Copy_Peripheral);
	}
}

void MRCC_voidResetPeripheral(RCC_PeripheralID_t Copy_Peripheral){

	if(Copy_Peripheral >= RCC_PER_DMA1 && Copy_Peripheral <= RCC_PER_SDIO){
		CLR_BIT(RCC_REG->AHBENR,(Copy_Peripheral - RCC_PER_DMA1));
		SET_BIT(RCC_REG->AHBENR,(Copy_Peripheral - RCC_PER_DMA1));
	}
	else if (Copy_Peripheral >= RCC_PER_AFIO){
		RCC_REG->APB2RSTR |= 1<<(Copy_Peripheral - RCC_PER_AFIO);
		RCC_REG->APB2RSTR = 0;
	}
	else if(Copy_Peripheral >= RCC_PER_TIM2){
		RCC_REG->APB1RSTR |= 1<<(Copy_Peripheral);
		RCC_REG->APB1RSTR = 0;
	}

}

void MRCC_voidEnableMCO(RCC_MCO_Source_t Copy_Source){

	RCC_REG->CFGR &= ~(3<<24);
	RCC_REG->CFGR |= Copy_Source<<24;
}

void MRCC_voidDisableMCO(void){
	RCC_REG->CFGR &= ~(3<<24);
}


void MRCC_voidSetCallBack(RCC_Interrupt_t Interrupt, void(*Callback)(void)){
	if(Interrupt > RCC_INTERRUPT_PLL_READY)
		return;
	PRCC_voidCallBacks[Interrupt] = Callback;

}

void MRCC_voidEnableInterrupt(RCC_Interrupt_t Interrupt){

	SET_BIT(RCC_REG->CIR,(Interrupt+8));
}

void MRCC_voidDisableInterrupt(RCC_Interrupt_t Interrupt){

	CLR_BIT(RCC_REG->CIR,(Interrupt+8));

}

u8 MRCC_u8GetIneterruptStatus(RCC_Interrupt_t Interrupt){
	return GET_BIT(RCC_REG->CIR,Interrupt);
}

void MRCC_voidClearInterrupt(RCC_Interrupt_t Interrupt){
	SET_BIT(RCC_REG->CIR,(Interrupt+16));
}


u32 MRCC_u32GetSystemClock(void){
	u8 Local_u8ClockSource = (RCC_REG->CFGR>>2) & 3;
	u8 Local_u8PLLSource = (RCC_REG->CFGR>>16) & 3;
	u8 Local_u8PLLMultiplier = (RCC_REG->CFGR>>18) & 7;
	Local_u8PLLMultiplier = (Local_u8PLLMultiplier == 15)?	16:Local_u8PLLMultiplier+2;
	u32 Local_u32SystemClock = 0;
	switch(Local_u8ClockSource){
		case 0:	//HSI
			Local_u32SystemClock = 8000000UL;
			break;
		case 1:	//HSE
			Local_u32SystemClock = RCC_HSE_VALUE;
			break;
		case 2:	//PLL
			switch(Local_u8PLLSource){
				case 0:		//HSI/2
					Local_u32SystemClock = 4000000UL;
					break;
				case 1:		//HSE
					Local_u32SystemClock = RCC_HSE_VALUE;
					break;
				case 2:		//HSI/2
					Local_u32SystemClock = 4000000UL;
					break;
				case 3:		//HSE/2
					Local_u32SystemClock = RCC_HSE_VALUE/2;
					break;

				default:
					Local_u32SystemClock = 0;
			}
			Local_u32SystemClock *= Local_u8PLLMultiplier;
			break;
		default:
			Local_u32SystemClock = 0;
		break;
	}
	return Local_u32SystemClock;
}

u32 MRCC_u32GetBusClock(RCC_BUS_t Copy_Bus){
	u32 Local_u32BusClock = 0;
	u32 Local_u32SystemClock = MRCC_u32GetSystemClock();
	u16 Local_u16Division = 1;
	u8 Local_u8Index = 0;
	switch(Copy_Bus){
		case RCC_BUS_AHB:
		    Local_u8Index = (((RCC_REG->CFGR>>4)&7) < 8)?	0:((RCC_REG->CFGR>>4)&7)-8;
			Local_u16Division = PRCC_u16AHBPrescalars[Local_u8Index];
			break;
		case RCC_BUS_APB1:
			Local_u8Index = (((RCC_REG->CFGR >> 8) & 3) < 4)?	0:((RCC_REG->CFGR >> 8) & 3)-4;
			Local_u16Division = PRCC_u16APBPescalars[Local_u8Index];
			break;
		case RCC_BUS_APB2:
			Local_u8Index = (((RCC_REG->CFGR >> 11) & 3) < 4)?	0:((RCC_REG->CFGR >> 11) & 3)-4;
			Local_u16Division = PRCC_u16APBPescalars[Local_u8Index];
			break;
		default:
			break;

	}
	Local_u32BusClock = Local_u32SystemClock/Local_u16Division;
	return Local_u32BusClock;
}


void RCC_IRQHandler(void){
	if(CHK_BIT(RCC_REG->CIR,RCC_INTERRUPT_LSI_READY)){
		if (PRCC_voidCallBacks[0] != 0)
			PRCC_voidCallBacks[0]();
		SET_BIT(RCC_REG->CIR,16);
	}

	if(CHK_BIT(RCC_REG->CIR,RCC_INTERRUPT_LSE_READY)){
		if (PRCC_voidCallBacks[1] != 0)
			PRCC_voidCallBacks[1]();
		SET_BIT(RCC_REG->CIR,17);
	}

	if(CHK_BIT(RCC_REG->CIR,RCC_INTERRUPT_HSI_READY)){
			if (PRCC_voidCallBacks[2] != 0)
				PRCC_voidCallBacks[2]();
			SET_BIT(RCC_REG->CIR,18);
		}

	if(CHK_BIT(RCC_REG->CIR,RCC_INTERRUPT_LSE_READY)){
			if (PRCC_voidCallBacks[3] != 0)
				PRCC_voidCallBacks[3]();
			SET_BIT(RCC_REG->CIR,19);
		}

	if(CHK_BIT(RCC_REG->CIR,RCC_INTERRUPT_PLL_READY)){
			if (PRCC_voidCallBacks[4] != 0)
				PRCC_voidCallBacks[4]();
			SET_BIT(RCC_REG->CIR,20);
		}
}
