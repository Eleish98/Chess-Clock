/*
 * ADVANCED_TIMERS_program.c
 *
 *  Created on: Oct 14, 2021
 *      Author: MohammedGamalEleish
 */


#include "1- LIB/STD_TYPES.h"
#include "1- LIB/BIT_MATH.h"

#include "TIM_interface.h"
#include "TIM_private.h"


/*					TIM Functions Definitions					*/

void MTIM_voidInit(TIM_ID_t Tim, TIM_Direction_t Direction, TIM_ClockMode_t ClockMode, u16 Prescalar, u16 AutoReloadValue, u16 RepetitionCounter, TIM_AutoReloadUpdate_t AutoReloadMode){

	if(Tim >= TIM_MAX_COUNT)
		return;
	//Error Checking
	else if (Direction > TIM_DIRECTION_COUNT_UP_DOWN || ClockMode > TIM_CLOCK_MODE_ENCODER || RepetitionCounter > 255 || AutoReloadMode > TIM_AUTORELOAD_UPDATE_ON_NEXT_CYCLE)
		return;
	else if (Tim >= ADV_TIM_MAX_COUNT)
		GNRL_TIM_voidInit(Tim - ADV_TIM_MAX_COUNT, Direction, ClockMode, Prescalar, AutoReloadValue,AutoReloadMode);
	else
		ADV_TIM_voidInit(Tim, Direction, ClockMode, Prescalar, AutoReloadValue, RepetitionCounter, AutoReloadMode);
}

void MTIM_voidConfigureExternalMode1(TIM_ID_t Tim, TIM_ExternalMode1_t ExternalMode1){

	if(Tim >= TIM_MAX_COUNT)
		return;
	else if (Tim >= ADV_TIM_MAX_COUNT)
		GNRL_TIM_voidConfigureExternalMode1(Tim - ADV_TIM_MAX_COUNT, ExternalMode1);
	else
		ADV_TIM_voidConfigureExternalMode1(Tim, ExternalMode1);
}

void MTIM_voidStartTimer(TIM_ID_t Tim){
	if(Tim >= TIM_MAX_COUNT)
		return;
	else if (Tim >= ADV_TIM_MAX_COUNT)
		GNRL_TIM_voidStartTimer(Tim - ADV_TIM_MAX_COUNT);
	else
		ADV_TIM_voidStartTimer(Tim);
}

void MTIM_voidStopTimer(TIM_ID_t Tim){
	if(Tim >= TIM_MAX_COUNT)
		return;
	else if (Tim >= ADV_TIM_MAX_COUNT)
		GNRL_TIM_voidStopTimer(Tim - ADV_TIM_MAX_COUNT);
	else
		ADV_TIM_voidStopTimer(Tim);
}

void MTIM_voidStartTimeMeasure(TIM_ID_t Tim){
	if(Tim >= TIM_MAX_COUNT)
		return;
	else if (Tim >= ADV_TIM_MAX_COUNT)
		GNRL_TIM_voidStartTimeMeasure(Tim - ADV_TIM_MAX_COUNT);
	else
		ADV_TIM_voidStartTimeMeasure(Tim);
}

u16 MTIM_u16GetElapsedTicks(TIM_ID_t Tim){
	u16 Local_u16ElapsedMS = 0;

	if(Tim >= TIM_MAX_COUNT)
		Local_u16ElapsedMS = 0;
	else if (Tim >= ADV_TIM_MAX_COUNT)
		Local_u16ElapsedMS = GNRL_TIM_u16GetElapsedTicks(Tim - ADV_TIM_MAX_COUNT);
	else
		Local_u16ElapsedMS = ADV_TIM_u16GetElapsedTicks(Tim);

	return Local_u16ElapsedMS;
}


void MTIM_voidSetBysyWait(TIM_ID_t Tim, u32 Ticks){
	if(Tim >= TIM_MAX_COUNT)
		return ;
	else if (Tim >= ADV_TIM_MAX_COUNT)
		GNRL_TIM_voidSetBysyWait(Tim, Ticks);
	else
		ADV_TIM_voidSetBysyWait(Tim, Ticks);
}



//=========================================================================================================================================================
/*		General Purpose Timer Function Definitions 		*/
static void GNRL_TIM_voidInit(TIM_ID_t TIM, TIM_Direction_t Direction, TIM_ClockMode_t ClockMode, u16 Prescalar, u16 AutoReloadValue, TIM_AutoReloadUpdate_t AutoReloadMode){


}

static void GNRL_TIM_voidConfigureExternalMode1(TIM_ID_t Tim, TIM_ExternalMode1_t ExternalMode1){

}

static void GNRL_TIM_voidStartTimer(TIM_ID_t Tim){

}

static void GNRL_TIM_voidStopTimer(TIM_ID_t Tim){

}

static void GNRL_TIM_voidStartTimeMeasure(TIM_ID_t Tim){

}

static u16 GNRL_TIM_u16GetElapsedTicks(TIM_ID_t Tim){
	u16 Local_u16GnrlTimElapsedTicks = 0;





	return Local_u16GnrlTimElapsedTicks;
}

static void GNRL_TIM_voidSetBysyWait(TIM_ID_t TIM, u32 Ticks){


}
//=========================================================================================================================================================

/*		Advanced Control Timer Function Definitions		*/
static void ADV_TIM_voidInit(TIM_ID_t Tim, TIM_Direction_t Direction, TIM_ClockMode_t ClockMode, u16 Prescalar, u16 AutoReloadValue, u16 RepetitionCounter, TIM_AutoReloadUpdate_t AutoReloadMode){

	volatile REG_ADV_TIM_t* REG = ADV_TIM_REGs[Tim];

	/*	Direction	*/
	CLR_BIT(REG->CR[0],4);
	REG->CR[1] |= (Direction & 1) << 4;

	/*	Clock Source  */
	//Disable Slave Mode Controller
	REG->SMCR &= ~7;

	if(ClockMode == TIM_CLOCK_MODE_EXTERNAL_MODE1){
		//External Mode 1
		//Disable ECE
		CLR_BIT(REG->SMCR,14);
	}
	else if (ClockMode == TIM_CLOCK_MODE_EXTERNAL_MODE2){
		//External Mode 2
		//Enable ECE
		SET_BIT(REG->SMCR, 14);
	}
	else if (ClockMode == TIM_CLOCK_MODE_ENCODER){
		//Encoder Mode

	}
	else {
		//Internal Clock
	}

	/*	Prescalar	*/
	REG->PSC = Prescalar;

	/*	AutoReloadValue	*/
	REG->ARR = AutoReloadValue;

	/*	RepetitionCounter	*/
	REG->RCR = RepetitionCounter;

	/*	AutoReload Preload	*/
	CLR_BIT(REG->CR[0],7);
	REG->CR[1] |= ((AutoReloadMode & 1) << 7);

}

static void ADV_TIM_voidConfigureExternalMode1(TIM_ID_t Tim, TIM_ExternalMode1_t ExternalMode1){

	volatile REG_ADV_TIM_t* REG = ADV_TIM_REGs[Tim];

	REG->SMCR &= ~(7 << 4);
	REG->SMCR |= (ExternalMode1<<4);
}

static void ADV_TIM_voidStartTimer(TIM_ID_t Tim){

	volatile REG_ADV_TIM_t* REG = ADV_TIM_REGs[Tim];

	SET_BIT(REG->CR[0], 0);
}

static void ADV_TIM_voidStopTimer(TIM_ID_t Tim){
	volatile REG_ADV_TIM_t* REG = ADV_TIM_REGs[Tim];

	CLR_BIT(REG->CR[1], 0);
}

static void ADV_TIM_voidStartTimeMeasure(TIM_ID_t Tim){

	volatile REG_ADV_TIM_t* REG = ADV_TIM_REGs[Tim];
	REG->CNT = 0;

	SET_BIT(REG->CR[0], 0);

}

static u16 ADV_TIM_u16GetElapsedTicks(TIM_ID_t Tim){

	volatile REG_ADV_TIM_t* REG = ADV_TIM_REGs[Tim];

	 u16 Local_u16AdvTimElapsedTicks = REG->CNT;

	return Local_u16AdvTimElapsedTicks;

}

static void ADV_TIM_voidSetBysyWait(TIM_ID_t TIM, u32 Ticks){

	u16 Local_u16WantedCounterVal = ADV_TIM_REGs[TIM]->CNT+Ticks;

	if (Local_u16WantedCounterVal > 65535)
		Local_u16WantedCounterVal -= 65536;

	while(ADV_TIM_REGs[TIM]->CNT != Local_u16WantedCounterVal);

}
