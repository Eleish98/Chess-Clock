/************************************************/
/*	Author		:		Mohamed G. ELeish		*/
/*	Date		:		6 September 2021		*/
/*	Version		:		V01						*/
/************************************************/

/************************************************/
/************************************************/
/*****					LOG					*****/
/*	6/9/2021:	File Created					*/
/************************************************/
/************************************************/

#include "1- LIB/STD_TYPES.h"
#include "1- LIB/BIT_MATH.h"

#include "2- MCAL/ARM _CORTEX_M3/02- SCB/SCB_interface.h"

#include "PWR_interface.h"
#include "PWR_private.h"

void MPWR_voidEnableBackupDomainWrite(void){
	/*	Sets DBP bit in CR Register	*/
	SET_BIT(PWR_REG->CR,8);
}

void MPWR_voidDisableBackupDomainWrite(void){
	/*	Clears DBP bit in CR Register	*/
	CLR_BIT(PWR_REG->CR,8);
}

void MPWR_voidSetPowerVoltageDetectorLevel(PWR_PVD_Level_t Copy_Level){
	/*	Clears PVD level bit field then write new value	*/
	PWR_REG->CR &= ~(7<<5);
	PWR_REG->CR |= Copy_Level&7;
}

void MPWR_voidEnablePowerVoltageDetector(void){
	/*	Sets PVDE bit in CR register */
	SET_BIT(PWR_REG->CR,4);
}

void MPWR_voidDisablePowerVoltageDetector(void){
	/*	Clears PVDE bit in CR register */
	CLR_BIT(PWR_REG->CR,4);
}

void MPWR_voidClearStandByFlag(void){
	/*	Sets CSBF Bit in CR register, Clearing the flag	*/
	SET_BIT(PWR_REG->CR,3);
}

void MPWR_voidClearWakeUpFlag(void){
	/*	Sets CWUF Bit in CR register, Clearing the flag	*/
	SET_BIT(PWR_REG->CR,2);
}

void MPWR_voidSetRegulatorMode(PWR_Regulator_Mode_t Copy_Mode){
	/*	Clears regulatror mode Bit (LPDS) and sets it to the selected value	*/
	CLR_BIT(PWR_REG->CR,0);
	PWR_REG->CR |= Copy_Mode&1;
}

void MPWR_voidEnableWakeUpPin(void){
	/*	Sets EWUP bit in CSR register	*/
	SET_BIT(PWR_REG->CSR,8);
}

void MPWR_voidDisableWakeUpPin(void){
	/*	Clears EWUP bit in CSR register	*/
	CLR_BIT(PWR_REG->CSR,8);
}

PWR_PVD_Output_t MPWR_u8GetPoerVoltageDetectorLevel(void){
	/*	Returns PVDO bit from CSR register	*/
	return GET_BIT(PWR_REG->CSR,2);
}

u8 MPWR_u8GetStandByStatus(void){
	/*	Returns SBF bit from CSR Register	*/
	return GET_BIT(PWR_REG->CSR,1);
}

u8 MPWR_voidGetWakeUpStatus(void){
	/*	Returns WUF bit from CSR Register	*/
	return GET_BIT(PWR_REG->CSR,0);
}

void MPWR_voidSleep(PWR_Sleep_t Copy_SleepMode, PWR_Wakeup_Mode_t Copy_WakeupMode){
	/*		Sleep Modes  
	* Normal Mode:
	*	Sleep Now 	=> 	DEEPSLEEP = 0
	*				=>	SLEEPONEXIT = 0
	*	Sleep On Exit	=>	SLEEPDEEP = 0
	*					=>	SLEEPONEXIT = 0
	* Stop Mode:
	*					=>	SLEEPDEEP = 1
	*					=>	PDDS = 0
	* StandBy Mode:
	*					=> SLEEPDEEP = 1
	*					=> PDDS  1
	*					=> WUF is cleared
	*/
	switch(Copy_SleepMode){
		case PWR_SLEEP_NORMAL_NOW:
			MSCB_voidEnableSleepNow();
			break;
		case PWR_SLEEP_NORMAL_ON_EXIT:
			MSCB_voidDisableSleepNow();
			break;
		case PWR_SLEEP_STOP:
			MSCB_voidEnableDeepSleep();
			CLR_BIT(PWR_REG->CR,1);
			break;
		case PWR_SLEEP_STAND_BY:
			MSCB_voidEnableDeepSleep();
			CLR_BIT(PWR_REG->CR,1);
			CLR_BIT(PWR_REG->CSR,0);
			break;
		default:
			break;
	}
	if(Copy_WakeupMode == PWR_WAKEUP_ON_INTERRUPT)
		asm("WFI");
	else if(Copy_WakeupMode == PWR_WAKEUP_ON_EVENT)
		asm("WFE");
}

void MPWR_voidSetWakeupEvent(PWR_Wakeup_Event_t Copy_Event){
	MSCB_voidSetEventOnPendingInterrupt(Copy_Event);
}

