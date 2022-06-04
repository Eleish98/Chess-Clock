/*
 * Encoder_program.c
 *
 *  Created on: Jan 17, 2022
 *      Author: 20109
 */

#include "1- LIB/STD_TYPES.h"
#include "1- LIB/BIT_MATH.h"

#include "2- MCAL/ARM _CORTEX_M3/01- NVIC/NVIC_interface.h"
#include "2- MCAL/ST/05- GPIO/GPIO_interface.h"
#include "2- MCAL/ST/06- AFIO/AFIO_interface.h"
#include "2- MCAL/ST/07- EXTI/EXTI_interface.h"


#include "Encoder_interface.h"
#include "Encoder_private.h"
#include "Encoder_config.h"


void HENCODER_voidInit(void){

	//Set Channels and switch to Input with Pull resistors
	MGPIO_voidSetPinDirection(ENCODER_CHANNEL_A_PORT,ENCODER_CHANNEL_A_PIN,GPIO_DIR_INPUT_PULL_UP_DOWN);
	MGPIO_voidSetPinDirection(ENCODER_CHANNEL_B_PORT,ENCODER_CHANNEL_B_PIN,GPIO_DIR_INPUT_PULL_UP_DOWN);
	MGPIO_voidSetPinDirection(ENCODER_SWITCH_PORT,ENCODER_SWITCH_PIN,GPIO_DIR_INPUT_PULL_UP_DOWN);

	//Enable Pull Up Resistors
	MGPIO_voidSetPinPull(ENCODER_CHANNEL_A_PORT,ENCODER_CHANNEL_A_PIN,GPIO_PULL_UP);
	MGPIO_voidSetPinPull(ENCODER_CHANNEL_B_PORT,ENCODER_CHANNEL_B_PIN,GPIO_PULL_UP);
	MGPIO_voidSetPinPull(ENCODER_SWITCH_PORT,ENCODER_SWITCH_PIN,GPIO_PULL_UP);

	//Set Configuration of EXTI Line according to sent ports and pins
	MAFIO_voidSetEXTIConfiguration(ENCODER_CHANNEL_A_PIN,(AFIO_PORTID_t)ENCODER_CHANNEL_A_PORT);
	MAFIO_voidSetEXTIConfiguration(ENCODER_SWITCH_PIN,(AFIO_PORTID_t)ENCODER_SWITCH_PORT);

	//Configure Interrupt on Falling Edge
	MEXTI_voidConfigureLineTrigger(ENCODER_CHANNEL_A_PIN,EXTI_TRIGGER_RISING_EDGE);
	MEXTI_voidConfigureLineTrigger(ENCODER_SWITCH_PIN,EXTI_TRIGGER_FALLING_EDGE);

	//Set CallBack for each Encoder
	MEXTI_voidSetCallBack(ENCODER_CHANNEL_A_PIN,PENCODERChanged);
	MEXTI_voidSetCallBack(ENCODER_SWITCH_PIN,PENCODERSwitchCallBack);

	if(ENCODER_CHANNEL_A_PIN <= 4)
		MNVIC_voidEnableInterrupt(ENCODER_CHANNEL_A_PIN + NVIC_INTERRUPT_EXTI0);
	else if (ENCODER_CHANNEL_A_PIN <= 9)
		MNVIC_voidEnableInterrupt(NVIC_INTERRUPT_EXTI5_9);
	else if (ENCODER_CHANNEL_A_PIN <= 15)
		MNVIC_voidEnableInterrupt(NVIC_INTERRUPT_EXTI10_15);

	if(ENCODER_SWITCH_PIN <= 4)
		MNVIC_voidEnableInterrupt(ENCODER_SWITCH_PIN + NVIC_INTERRUPT_EXTI0);
	else if (ENCODER_SWITCH_PIN <= 9)
		MNVIC_voidEnableInterrupt(NVIC_INTERRUPT_EXTI5_9);
	else if (ENCODER_SWITCH_PIN <= 15)
		MNVIC_voidEnableInterrupt(NVIC_INTERRUPT_EXTI10_15);





}

void HENCODER_voidSetChangeCallBack(void (*ChangeCallBack)(EncoderChange_t)){
	PENCODERChangeCallBack = ChangeCallBack;
}

void HENCODER_voidSetSwitchCallBack(void (*SwitchCallBack)(void)){
	PENCODERSwitchCallBack = SwitchCallBack;
}

void HENCODER_voidEnableEncoder(void){

	MEXTI_voidEnableInterrupt(ENCODER_CHANNEL_A_PIN);
	MEXTI_voidEnableInterrupt(ENCODER_SWITCH_PIN);
}

void HENCODER_voidDisableEncoder(void){
	MEXTI_voidDisableInterrupt(ENCODER_CHANNEL_A_PIN);
}

EncoderSwitchState_t HENCODER_enuGetSwitchState(void){
	EncoderSwitchState_t SwitchState = ENCODER_SWITCH_RELEASED;
	if(MGPIO_u8GetPinValue(ENCODER_SWITCH_PORT,ENCODER_SWITCH_PIN) == 0)
		SwitchState = ENCODER_SWITCH_PRESSED;
	return SwitchState;
}

void PENCODERChanged(void){
	if (MGPIO_u8GetPinValue(ENCODER_CHANNEL_B_PORT,ENCODER_CHANNEL_B_PIN) == 1)
		PENCODERChangeCallBack(ENCODER_CHANGE_CLOCKWISE);
	else
		PENCODERChangeCallBack(ENCODER_CHANGE_COUNTER_CLOCKWISE);
}


