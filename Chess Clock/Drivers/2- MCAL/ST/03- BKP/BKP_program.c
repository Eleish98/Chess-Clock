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

#include "BKP_interface.h"
#include "BKP_private.h"


void MBKP_voidStore(BKP_Register_t Copy_Register, u16 Copy_u16Value){
	if(Copy_Register > BKP_REGISTER_10)
		return;
	BKP_REG->DR[Copy_Register] = Copy_u16Value;
}

u16 MBKP_u16Retrieve(BKP_Register_t Copy_Register){
	if(Copy_Register > BKP_REGISTER_10)
		return 0;
	return BKP_REG->DR[Copy_Register];
}


u8 MBKP_u8GetRTCCalibrationValue(void){
	
	return ((BKP_REG->RTCCR)&0x3F);
}

void MBKP_voidEnableRTCOutputOnTamperPin(void){
/*	Clear TPE bit in CR	*/
	CLR_BIT(BKP_REG->CR,0);
/*	Set CCO bit in RTCCR	*/
	SET_BIT(BKP_REG->RTCCR,7);
}

void MBKP_voidSetRTCCalibration(BKP_RTC_Config_t Copy_Config){
/*	Clear TPE bit in CR	*/	
	CLR_BIT(BKP_REG->CR,0);
/*	Clear RTC Config field in RTCCR then write new value */
	BKP_REG->RTCCR &= ~(3<<8);
	BKP_REG->RTCCR |= (Copy_Config << 8);
}


void MBKP_voidSetTamperConfiguration(BKP_Tamper_Config_t Copy_Config){
/*	Clear Tamper pin config bit field then write new value	*/
	CLR_BIT(BKP_REG->CR,1);
	BKP_REG->CR |= (Copy_Config<<1);
}

void MBKP_voidEnableTamperPin(void){
/*	Set TPE bit in CR	*/
	SET_BIT(BKP_REG->CR,0);
}

void MBKP_voidDisableTamperPin(void){
/*	Clear TPE bit in CR	*/
	CLR_BIT(BKP_REG->CR,0);
}

void MBKP_voidEnableTamperInterrupt(void){
/*	Set TPIE bit in CSR	*/
	SET_BIT(BKP_REG->CSR,2);
}

void MBKP_voidDisableTamperInterrupt(void){
/*	Clear TPIE bit in CSR	*/	
	CLR_BIT(BKP_REG->CSR,2);
}

u8 	MBKP_u8GetTamperEventState(void){
/*	Returns TEF bit	*/
	return GET_BIT(BKP_REG->CSR,8);
}

u8	MBKP_u8GetTamperInterruptState(void){
/*	Returns TIF bit	*/
	return GET_BIT(BKP_REG->CSR,9);
}

void MBKP_voidClearTamperEvent(void){
/*	Sets CTE bit in CSR	*/
	SET_BIT(BKP_REG->CSR,0);
}

void MBKP_voidClearTamperInterrupt(void){
/*	Sets CTI bit in CSR	*/
	SET_BIT(BKP_REG->CSR,1);
}

void MBKP_voidSetTamperCallBack(void(*CallBack)(void)){
	PBKP_voidCallBack = CallBack;
}


void TAMPER_IRQHandler(void){
	if(PBKP_voidCallBack != 0)
		PBKP_voidCallBack();
	
	SET_BIT(BKP_REG->CSR,1);
}
