/*
 * ChessClock_program.c
 *
 *  Created on: Jan 16, 2022
 *      Author: 20109
 */
//Library Files Includes
#include "1- LIB/STD_TYPES.h"
#include "1- LIB/BIT_MATH.h"

//Core Peripherals Includes
#include "2- MCAL/ARM _CORTEX_M3/01- NVIC/NVIC_interface.h"
#include "2- MCAL/ARM _CORTEX_M3/03- STK/STK_interface.h"
#include "2- MCAL/ARM _CORTEX_M3/02- SCB/SCB_interface.h"

//MCAL Peripherals includes
#include "2- MCAL/ST/04- RCC/RCC_interface.h"
#include "2- MCAL/ST/05- GPIO/GPIO_interface.h"
#include "2- MCAL/ST/06- AFIO/AFIO_interface.h"
#include "2- MCAL/ST/07- EXTI/EXTI_interface.h"

//HAL Includes
#include "3- HAL/03- Char LCD/LCD_interface.h"
#include "3- HAL/04- Rotary Encoder/Encoder_interface.h"

//App Includes
#include "ChessClock_interface.h"
#include "ChessClock_private.h"


//HW Configuration Include
#include "ChessClock_HWConfig.h"


void ChessClock_voidInit(void){

	ChessClock_voidEnablePeripheralClock();

	ChessClock_voidSetPinsDirections();

	ChessClock_voidConfigureInterrupts();

	ChessClock_voidInitMCALModules();

	ChessClock_voidInitHALModules();
}

void ChessClock_voidRun(void){

}


void SM_ChessClockMain(void){

}


void SM_StoppedState(void){

}

void SM_SavedModeSelectedState(void){

}

void SM_ConfiguringTimeControlState(void){

}

void SM_StartingState(void){

}

void SM_PlayingState(void){

}


/*	Enables RCC Clock for All Used Peripherals	*/
static void ChessClock_voidEnablePeripheralClock(void){

	/*	Enable Clock Distribution for Used GPIO Ports*/
	MRCC_voidEnablePeripheral(RCC_PER_GPIOA + CHESS_CLOCK_LCD_RS_PORT);
	MRCC_voidEnablePeripheral(RCC_PER_GPIOA + CHESS_CLOCK_LCD_RW_PORT);
	MRCC_voidEnablePeripheral(RCC_PER_GPIOA + CHESS_CLOCK_LCD_E_PORT);
	MRCC_voidEnablePeripheral(RCC_PER_GPIOA + CHESS_CLOCK_LCD_D4_PORT);
	MRCC_voidEnablePeripheral(RCC_PER_GPIOA + CHESS_CLOCK_LCD_D5_PORT);
	MRCC_voidEnablePeripheral(RCC_PER_GPIOA + CHESS_CLOCK_LCD_D6_PORT);
	MRCC_voidEnablePeripheral(RCC_PER_GPIOA + CHESS_CLOCK_LCD_D7_PORT);
	MRCC_voidEnablePeripheral(RCC_PER_GPIOA + CHESS_CLOCK_ENCODER_CH_A_PORT);
	MRCC_voidEnablePeripheral(RCC_PER_GPIOA + CHESS_CLOCK_ENCODER_CH_B_PORT);
	MRCC_voidEnablePeripheral(RCC_PER_GPIOA + CHESS_CLOCK_ENCODER_SWITCH_PORT);
	MRCC_voidEnablePeripheral(RCC_PER_GPIOA + CHESS_CLOCK_PLAYER_1_SWITCH_PORT);
	MRCC_voidEnablePeripheral(RCC_PER_GPIOA + CHESS_CLOCK_PLAYER_2_SWITCH_PORT);

	/*	Enable Alternate Function Clock*/
	MRCC_voidEnablePeripheral(RCC_PER_AFIO);

}

/*	Configures Switches Used Pins	*/
static void ChessClock_voidSetPinsDirections(void){

	/*	Configure Switchs as Input PullUp*/
	MGPIO_voidSetPinDirection(CHESS_CLOCK_PLAYER_1_SWITCH_PORT,CHESS_CLOCK_PLAYER_1_SWITCH_PIN,GPIO_DIR_INPUT_PULL_UP_DOWN);
	MGPIO_voidSetPinDirection(CHESS_CLOCK_PLAYER_2_SWITCH_PORT,CHESS_CLOCK_PLAYER_2_SWITCH_PIN,GPIO_DIR_INPUT_PULL_UP_DOWN);

	MGPIO_voidSetPinPull(CHESS_CLOCK_PLAYER_1_SWITCH_PORT,CHESS_CLOCK_PLAYER_1_SWITCH_PIN,GPIO_PULL_UP);
	MGPIO_voidSetPinPull(CHESS_CLOCK_PLAYER_2_SWITCH_PORT,CHESS_CLOCK_PLAYER_2_SWITCH_PIN,GPIO_PULL_UP);
}

/*	Configures All Used Interrupts	*/
static void ChessClock_voidConfigureInterrupts(void){

	/*	Map Interrupts to Selected Ports	*/
	MAFIO_voidSetEXTIConfiguration(CHESS_CLOCK_PLAYER_1_SWITCH_PIN,CHESS_CLOCK_PLAYER_1_SWITCH_PORT);
	MAFIO_voidSetEXTIConfiguration(CHESS_CLOCK_PLAYER_2_SWITCH_PIN,CHESS_CLOCK_PLAYER_2_SWITCH_PORT);

	/*	Configure Trigger Signal for All Interrupts	*/
	MEXTI_voidConfigureLineTrigger(CHESS_CLOCK_PLAYER_1_SWITCH_PIN,EXTI_TRIGGER_FALLING_EDGE);
	MEXTI_voidConfigureLineTrigger(CHESS_CLOCK_PLAYER_2_SWITCH_PIN,EXTI_TRIGGER_FALLING_EDGE);

	MEXTI_voidSetCallBack(CHESS_CLOCK_PLAYER_1_SWITCH_PIN,ChessClock_voidPlayer1Pressed);
	MEXTI_voidSetCallBack(CHESS_CLOCK_PLAYER_2_SWITCH_PIN,ChessClock_voidPlayer2Pressed);

}

/*	Initializes LCD, Encoder	*/
static void ChessClock_voidInitHALModules(void){

	GPIO_Pin_t ChessLCDDataPins[] = {CHESS_CLOCK_LCD_D4_PIN,CHESS_CLOCK_LCD_D5_PIN,CHESS_CLOCK_LCD_D6_PIN,CHESS_CLOCK_LCD_D7_PIN};
	GPIO_Port_t ChessLCDDataPorts[] = {CHESS_CLOCK_LCD_D4_PORT,CHESS_CLOCK_LCD_D5_PORT,CHESS_CLOCK_LCD_D6_PORT,CHESS_CLOCK_LCD_D7_PORT};

	LCD_t	ChessLCD = {LCD_MODE_4_BIT,{4,20},{CHESS_CLOCK_LCD_RS_PIN,CHESS_CLOCK_LCD_RW_PIN,CHESS_CLOCK_LCD_E_PIN},
											{CHESS_CLOCK_LCD_RS_PORT,CHESS_CLOCK_LCD_RW_PORT,CHESS_CLOCK_LCD_E_PORT},
											ChessLCDDataPins,ChessLCDDataPorts};
	HLCD_voidInit(&ChessLCD);

	HENCODER_voidInit();

	HENCODER_voidSetChangeCallBack(ChessClock_voidEncoderMoved);
	HENCODER_voidEnableEncoder();
}

/*	Initializes NVIC, STK */
static void ChessClock_voidInitMCALModules(void){

	MNVIC_voidInit(NVIC_CONFIG_1_GROUP_16_SUB);

	MSTK_voidInit(STK_CLOCK_AHB,MRCC_u32GetBusClock(RCC_BUS_AHB));


}

/*	Enables All Chess Clock Interrupts	*/
static void ChessClock_voidEnableInterrupts(void){

	/*	External Interrupts Enable	*/
	MEXTI_voidEnableInterrupt(CHESS_CLOCK_PLAYER_1_SWITCH_PIN);
	MEXTI_voidEnableInterrupt(CHESS_CLOCK_PLAYER_2_SWITCH_PIN);

	/*	Encoder Interrupts Enable	*/
	HENCODER_voidEnableEncoder();

}

/*	Disables All Chess Clock Interrupts	*/
static void ChessClock_voidDisableInterrupts(void){

	/*	External Interrupts Enable	*/
	MEXTI_voidDisableInterrupt(CHESS_CLOCK_PLAYER_1_SWITCH_PIN);
	MEXTI_voidDisableInterrupt(CHESS_CLOCK_PLAYER_2_SWITCH_PIN);

	/*	Encoder Interrupts Enable	*/
	HENCODER_voidDisableEncoder();
}


static void ChessClock_voidPlayer1Pressed(void){

}

static void ChessClock_voidPlayer2Pressed(void){

}

/*	Called When Encoder Moves*/
static void ChessClock_voidEncoderMoved(EncoderChange_t Direction){


}
