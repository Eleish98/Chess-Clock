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

#ifndef PWR_INTERFACE_H_INCLUDED
#define PWR_INTERFACE_H_INCLUDED

/*This enum is used with:
*
* 1- void MPWR_voidSetPowerVoltageDetectorLevel
* 
*/
typedef enum{
	PWR_PVD_2_2V,
	PWR_PVD_2_3V,
	PWR_PVD_2_4V,
	PWR_PVD_2_5V,
	PWR_PVD_2_6V,
	PWR_PVD_2_7V,
	PWR_PVD_2_8V,
	PWR_PVD_2_9V
}PWR_PVD_Level_t;

/* This enum is used with: 
*
* 1- MPWR_voidSetRegulatorMode
* 
*/
typedef enum{
	PWR_REGULATOR_ON,
	PWR_REGULATOR_LOW_POWER,
}PWR_Regulator_Mode_t;

/*This enum is used with:
*
* 1- MPWR_u8GetPoerVoltageDetectorLevel
*
*/
typedef enum{
	PWR_PVD_VDD_HIGHER_THAN_THRESHOLD,
	PWR_PVD_VDD_LOWER_THAN_THRESHOLD,
}PWR_PVD_Output_t;

/*This enum is used with:
*
* 1- void MPWR_voidSleep
*
*/
typedef enum{
	PWR_SLEEP_NORMAL_NOW,
	PWR_SLEEP_NORMAL_ON_EXIT,
	PWR_SLEEP_STOP,
	PWR_SLEEP_STAND_BY
}PWR_Sleep_t;

/*This enum is used with:
*
* 1- void MPWR_voidSleep
*
*/
typedef enum{
	PWR_WAKEUP_ON_INTERRUPT,
	PWR_WAKEUP_ON_EVENT
}PWR_Wakeup_Mode_t;

/*This enum is used with:
*
* 1- void MPWR_voidSetWakeupEvent
*
*/

typedef enum{
	PWR_WAKEUP_EVENT_ENABLED_INTERRUPTS,
	PWR_WAKEUP_EVENT_DISABLED_INTERRUPTS
}PWR_Wakeup_Event_t;

/*	Enables the Ability to write in Backup Domain	*/
void MPWR_voidEnableBackupDomainWrite(void);
/*	Disables the Ability to write in Backup Domain	*/
void MPWR_voidDisableBackupDomainWrite(void);
/*	
*	Sets the Power Voltage detector, which can be used with EXTI to 
*	trigger PVD Interrupt when power voltage gets lower/higher than
*	PVD Threshold set by this function
*/
void MPWR_voidSetPowerVoltageDetectorLevel(PWR_PVD_Level_t Copy_Level);
/*	Enables Power Voltage Detector	*/
void MPWR_voidEnablePowerVoltageDetector(void);
/*	Disables Power Voltage Detector	*/
void MPWR_voidDisablePowerVoltageDetector(void);
/*	Clears Standby Flag, Must be called upon waking up from Standby sleep mode	*/
void MPWR_voidClearStandByFlag(void);
/*	Clears Standby Flag, Must be called upon waking up from Stop sleep mode	*/
void MPWR_voidClearWakeUpFlag(void);
/*	Sets Power Regulator mode when enterring sleep modes, helps reduces power	*/
void MPWR_voidSetRegulatorMode(PWR_Regulator_Mode_t Copy_Mode);
/*	Enables WakeUp pin allowing for wakeup using this pin	*/
void MPWR_voidEnableWakeUpPin(void);
/*	Disables WakeUp pin	*/
void MPWR_voidDisableWakeUpPin(void);
/*	Returns the PowerVoltage Detector Level	*/ 
PWR_PVD_Output_t MPWR_u8GetPoerVoltageDetectorLevel(void);
/*	Returns wether the uC has been in StandBy sleep mode (1) or Not (0)	*/
u8 MPWR_u8GetStandByStatus(void);
/*	Returns wether the uC has been in Stop sleep mode (1) or Not (0)	*/
u8 MPWR_voidGetWakeUpStatus(void);
/*	Makes uC enters the Selected sleep mode, the uC wakes from sleep mode according the selected method	*/
void MPWR_voidSleep(PWR_Sleep_t Copy_SleepMode, PWR_Wakeup_Mode_t Copy_WakeupMode);
/*	Enables or disables the ability to wakeup using internal interrupts when no enabled by NVIC*/
void MPWR_voidSetWakeupEvent(PWR_Wakeup_Event_t Copy_Event);



#endif

