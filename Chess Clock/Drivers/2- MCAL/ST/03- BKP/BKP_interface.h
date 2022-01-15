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

#ifndef BKP_INTERFACE_H_INCLUDED
#define BKP_INTERFACE_H_INCLUDED

/* This enum is used with:
*
* 1- void MBKP_voidStore 
* 2- u16 MBKP_u16Retrieve
*
*/
typedef enum{
	BKP_REGISTER_1,
	BKP_REGISTER_2,
	BKP_REGISTER_3,
	BKP_REGISTER_4,
	BKP_REGISTER_5,
	BKP_REGISTER_6,
	BKP_REGISTER_7,
	BKP_REGISTER_8,
	BKP_REGISTER_9,
	BKP_REGISTER_10,
}BKP_Register_t;

/* This enum is used with:
*
* 1- void MBKP_voidSetTamperConfiguration
*
*/
typedef enum{
	BKP_TAMPER_RESET_ON_HIGH_LEVEL,
	BKP_TAMPER_RESET_ON_LOW_LEVEL
}BKP_Tamper_Config_t;

/* This enum is used with:
*
* 1- void MBKP_voidSetRTCCalibration
*
*/
typedef enum{
	BKP_RTC_OFF,
	BKP_RTC_ALARM,
	BKP_RTC_SECOND_PULSE
}BKP_RTC_Config_t;

/*	Stores a 16-Bit Value in one Backup register	*/
void MBKP_voidStore (BKP_Register_t Copy_Register, u16 Copy_u16Value);
/*	Retrieves 1 16-bit Value from one Backup register	*/
u16 MBKP_u16Retrieve(BKP_Register_t Copy_Register);
/*	Returns RTC Calibration value	*/
u8 MBKP_u8GetRTCCalibrationValue(void);
/*	Enable th output of RTC on the Tamper Pin	*/
/*	MBKP_voidSetRTCCalibration must be called first	*/
void MBKP_voidEnableRTCOutputOnTamperPin(void);
/*	Sets The RTC Calibration Mode	*/
void MBKP_voidSetRTCCalibration(BKP_RTC_Config_t Copy_Config);
/*	Sets the Tamper Pin Configuration	*/
void MBKP_voidSetTamperConfiguration(BKP_Tamper_Config_t Copy_Config);
/*	Enable Tamper Pin	*/
void MBKP_voidEnableTamperPin(void);
/*	Disables Tamper Pin	*/
void MBKP_voidDisableTamperPin(void);
/*	Enables Tamper Interrupt	*/
void MBKP_voidEnableTamperInterrupt(void);
/*	Disables Tamper Interrupt	*/
void MBKP_voidDisableTamperInterrupt(void);
/*	Retruns the State of a Tamper Event	*/
/*	
*	1	=>	Tamper Event Occured
*	0	=>	Tamper Event Hasn't Occured
*/
u8 	MBKP_u8GetTamperEventState(void);
/*	Retruns the State of a Tamper Interrupt	*/
/*	
*	1	=>	Tamper Interrupt Occured
*	0	=>	Tamper Interrupt Hasn't Occured
*/
u8	MBKP_u8GetTamperInterruptState(void);
/*	Clears Tamper Event Flag	*/
void MBKP_voidClearTamperEvent(void);
/*	Clears Tamper Interrupt Flag	*/
void MBKP_voidClearTamperInterrupt(void);
/*	Sets Tamper Interrupt CallBack Function	*/
void MBKP_voidSetTamperCallBack(void(*CallBack)(void));


#endif

