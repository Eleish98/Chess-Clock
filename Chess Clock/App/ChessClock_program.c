/*
 * ChessClock_program.c
 *
 *  Created on: Jan 16, 2022
 *      Author: 20109
 */
//Library Files Includes
#include "1- LIB/STD_TYPES.h"
#include "1- LIB/BIT_MATH.h"
#include "1- LIB/Delay.h"
#include <stdio.h>


//Core Peripherals Includes
#include "2- MCAL/ARM _CORTEX_M3/01- NVIC/NVIC_interface.h"
#include "2- MCAL/ARM _CORTEX_M3/03- STK/STK_interface.h"
#include "2- MCAL/ARM _CORTEX_M3/02- SCB/SCB_interface.h"

//MCAL Peripherals includes
#include "2- MCAL/ST/04- RCC/RCC_interface.h"
#include "2- MCAL/ST/05- GPIO/GPIO_interface.h"
#include "2- MCAL/ST/06- AFIO/AFIO_interface.h"
#include "2- MCAL/ST/07- EXTI/EXTI_interface.h"
#include "2- MCAL/ST/10- TIM/TIM_interface.h"
//HAL Includes
#include "3- HAL/03- Char LCD/LCD_interface.h"
#include "3- HAL/04- Rotary Encoder/Encoder_interface.h"

//App Includes
#include "ChessClock_interface.h"
#include "ChessClock_HWConfig.h"
#include "ChessClock_private.h"





void ChessClock_voidInit(void){

	/*	Initialization Sequence	*/
	ChessClock_voidEnablePeripheralClock();

	ChessClock_voidSetPinsDirections();

	ChessClock_voidConfigureInterrupts();

	ChessClock_voidInitMCALModules();

	ChessClock_voidInitHALModules();


}

void ChessClock_voidRun(void){

	ChessClock_voidEnableInterrupts();

	ChessClock_voidStoppedOnEntry();

	while(1);
}


void SM_ChessClockMain(ChessClockSignal_t Signal){

	switch(PCHESS_CLOCK_STATE){

	case STATE_STOPPED:
	case STATE_IDLE:
		SM_StoppedState(Signal);
		break;
	case STATE_SAVED_MODE_SELECTED:
		SM_SavedModeSelectedState(Signal);
		break;
	case STATE_CONFIGURE_TIME_CONTROL:
		SM_ConfiguringTimeControlState(Signal);
		break;
	case STATE_STARTING:
		SM_StartingState(Signal);
		break;
	case STATE_PLAYING:
		SM_PlayingState(Signal);
		break;
	default:

		break;

	}

}


void SM_StoppedState(ChessClockSignal_t Signal){

	if(PCHESS_CLOCK_STATE != STATE_STOPPED){
		ChessClock_voidStoppedOnEntry();
	}
	switch(Signal){
		case STATE_MACHINE_SIGNAL_ENCODER_STEP_CLOCKWISE:
		case STATE_MACHINE_SIGNAL_ENCODER_STEP_COUNTERCLOCKWISE:
			if (PCHESS_MODEModeSelector == MODE_SAVED){
				HLCD_voidSetPosition((LCD_t*)&ChessLCD,3,3);
				PCHESS_MODEModeSelector = MODE_MANUAL;
			}
			else{
				HLCD_voidSetPosition((LCD_t*)&ChessLCD,4,2);
				PCHESS_MODEModeSelector = MODE_SAVED;
			}
			PCHESS_CLOCK_STATE = STATE_STOPPED;
			break;
		case STATE_MACHINE_SIGNAL_ENTER_LESS_THAN_3_SECONDS:
			if (PCHESS_MODEModeSelector == MODE_SAVED){
				//Saved Mode is selected
				//display list of saved modes
				ChessClock_voidSavedModeSelectedOnEntry();
				//next state is Saved Mode Selected
				PCHESS_CLOCK_STATE = STATE_SAVED_MODE_SELECTED;
			}
			else{
				//Manual Mode is selected
				ChessClock_voidConfigureTimeControlOnentry();
				//next state Configure Time Control
				PCHESS_CLOCK_STATE = STATE_CONFIGURE_TIME_CONTROL;
			}
			break;
		default:
			break;
	}
}

void SM_SavedModeSelectedState(ChessClockSignal_t Signal){
	u8 Local_u8CursorPos;
	if (PCHESS_CLOCK_STATE != STATE_SAVED_MODE_SELECTED){
		//On Entry
		ChessClock_voidSavedModeSelectedOnEntry();
	}

	switch(Signal){
		case STATE_MACHINE_SIGNAL_ENCODER_STEP_CLOCKWISE:
			//Increment Saved Mode Selector
			PCHESS_u8SavedModeSelector++;
			if (PCHESS_FLAGModeSelected == FLAG_CLEAR){
				Local_u8CursorPos = PCHESS_u8SavedModeSelector%12;
				ChessClock_UpdateSavedModesScreenCursor(Local_u8CursorPos);
			}
			else{
				Local_u8CursorPos = PCHESS_u8SavedModeSelector%2;
				ChessClock_UpdateSavedModeSelectedScreenCursor(Local_u8CursorPos);
			}

			PCHESS_CLOCK_STATE = STATE_SAVED_MODE_SELECTED;
			break;
		case STATE_MACHINE_SIGNAL_ENCODER_STEP_COUNTERCLOCKWISE:
			//decrement Saved Mode Selector
			PCHESS_u8SavedModeSelector--;
			if (PCHESS_FLAGModeSelected == FLAG_CLEAR){
				Local_u8CursorPos = PCHESS_u8SavedModeSelector%12;
				ChessClock_UpdateSavedModesScreenCursor(Local_u8CursorPos);
			}
			else{
				Local_u8CursorPos = PCHESS_u8SavedModeSelector%2;
				ChessClock_UpdateSavedModeSelectedScreenCursor(Local_u8CursorPos);
			}
			PCHESS_CLOCK_STATE = STATE_SAVED_MODE_SELECTED;
			break;
		case STATE_MACHINE_SIGNAL_ENTER_LESS_THAN_3_SECONDS:
			if(PCHESS_FLAGModeSelected == FLAG_CLEAR){
				PCHESS_FLAGModeSelected = FLAG_SET;
				ChessClock_voidDisplayScreen(&SavedModeSelectedScreen);
				HLCD_voidSetPosition((LCD_t*)(&ChessLCD),6,1);
			}
			else{
				Local_u8CursorPos = PCHESS_u8SavedModeEnsuring++%2;
				if (Local_u8CursorPos == 0){
					ChessClock_voidStartingOnEntry();
					PCHESS_CLOCK_STATE = STATE_STARTING;
				}
				else{
					PCHESS_FLAGModeSelected = FLAG_CLEAR;
					ChessClock_voidSavedModeSelectedOnEntry();
					PCHESS_CLOCK_STATE = STATE_SAVED_MODE_SELECTED;
				}
			}
			break;
		default:
			break;
	}

}

void SM_ConfiguringTimeControlState(ChessClockSignal_t Signal){
	if (PCHESS_CLOCK_STATE != STATE_CONFIGURE_TIME_CONTROL){
		//On Entry
		ChessClock_voidConfigureTimeControlOnentry();
	}
}

void SM_StartingState(ChessClockSignal_t Signal){
	if (PCHESS_CLOCK_STATE != STATE_STARTING){
		//On Entry
		ChessClock_voidStartingOnEntry();
	}

	switch(Signal){

		case STATE_MACHINE_SIGNAL_RTC_TRIGGER:
			if ( CurrentTurn == TURN_PLAYER_1 ){
				ChessClock_voidUpdatePlayerTime(&ChessPlayer1, (s32)(-1 * (CHESS_CLOCK_RTC_TRIGGER_PERIOD_MS)));
				ChessClock_voidUpdatePlayerTimeOnScreen(&ChessPlayer1);
				if (ChessPlayer1.Time.BaseTime.Minutes == 0 && ChessPlayer1.Time.BaseTime.MilleSeconds == 0){
					//Player 1 Lost on first move
					ChessClock_voidDisplayPlayerLostOnTimeScreen(&LostOnFirstMoveScreen,1);
					LDelay_voidSetBusyWait(3000);
					//Go to Stopped state
					ChessClock_voidStoppedOnEntry();
					PCHESS_CLOCK_STATE = STATE_STOPPED;
				}
			}
			else {
				ChessClock_voidUpdatePlayerTime(&ChessPlayer2, (s32)(-1 * (CHESS_CLOCK_RTC_TRIGGER_PERIOD_MS)));
				ChessClock_voidUpdatePlayerTimeOnScreen(&ChessPlayer2);
				if (ChessPlayer2.Time.BaseTime.Minutes == 0 && ChessPlayer2.Time.BaseTime.MilleSeconds == 0){
					//Player 2 Lost on first move
					ChessClock_voidDisplayPlayerLostOnTimeScreen(&LostOnFirstMoveScreen,2);
					LDelay_voidSetBusyWait(3000);
					//Go to Stopped state
					ChessClock_voidStoppedOnEntry();
					PCHESS_CLOCK_STATE = STATE_STOPPED;
				}
			}
			break;
		case STATE_MACHINE_SIGNAL_PLAYER_1_BUTTON:
			if (CurrentTurn == TURN_PLAYER_1){
				ChessPlayer1.FirstMove = PLAYED;
				CurrentTurn = TURN_PLAYER_2;
				if (ChessClock_GetFirstMoveStatus(&ChessPlayer1, &ChessPlayer2) == PLAYED){
					//Go to playing State
					ChessClock_voidPlayingOnEntry();
					PCHESS_CLOCK_STATE = STATE_PLAYING;
				}
				else{
					PCHESS_CLOCK_STATE = STATE_STARTING;
				}
			}
			break;
		case STATE_MACHINE_SIGNAL_PLAYER_2_BUTTON:
			if(CurrentTurn == TURN_PLAYER_2){
				ChessPlayer2.FirstMove = PLAYED;
				CurrentTurn = TURN_PLAYER_2;
				if (ChessClock_GetFirstMoveStatus(&ChessPlayer1, &ChessPlayer2) == PLAYED){
					//Go to playing State
					ChessClock_voidPlayingOnEntry();
					PCHESS_CLOCK_STATE = STATE_PLAYING;
				}
				else{
					PCHESS_CLOCK_STATE = STATE_STARTING;
				}
			}
			break;
		default:
			break;
	}
}

void SM_PlayingState(ChessClockSignal_t Signal){
	if (PCHESS_CLOCK_STATE != STATE_PLAYING){
		//On Entry
		ChessClock_voidPlayingOnEntry();
	}

	switch(Signal){

		case STATE_MACHINE_SIGNAL_RTC_TRIGGER:
			if ( CurrentTurn == TURN_PLAYER_1 ){
				ChessClock_voidUpdatePlayerTime(&ChessPlayer1, (s32)(-1 * (CHESS_CLOCK_RTC_TRIGGER_PERIOD_MS)));
				ChessClock_voidUpdatePlayerTimeOnScreen(&ChessPlayer1);
				if (ChessPlayer1.Time.BaseTime.Minutes == 0 && ChessPlayer1.Time.BaseTime.MilleSeconds == 0){
					//Player 1 Lost Time
					ChessClock_voidDisplayPlayerLostOnTimeScreen(&LostOnTimeScreen,1);
					LDelay_voidSetBusyWait(3000);
					//Go to Stopped state
					ChessClock_voidStoppedOnEntry();
					PCHESS_CLOCK_STATE = STATE_STOPPED;
				}
			}
			else {
				ChessClock_voidUpdatePlayerTime(&ChessPlayer2, (s32)(-1 * (CHESS_CLOCK_RTC_TRIGGER_PERIOD_MS)));
				ChessClock_voidUpdatePlayerTimeOnScreen(&ChessPlayer2);
				if (ChessPlayer2.Time.BaseTime.Minutes == 0 && ChessPlayer2.Time.BaseTime.MilleSeconds == 0){
					//Player 2 Lost on first move
					ChessClock_voidDisplayPlayerLostOnTimeScreen(&LostOnTimeScreen,2);
					LDelay_voidSetBusyWait(3000);
					//Go to Stopped state
					ChessClock_voidStoppedOnEntry();
					PCHESS_CLOCK_STATE = STATE_STOPPED;
				}
			}
			break;
		case STATE_MACHINE_SIGNAL_PLAYER_1_BUTTON:
			if (CurrentTurn == TURN_PLAYER_1){
				CurrentTurn = TURN_PLAYER_2;

				ChessClock_voidUpdatePlayerTime(&ChessPlayer1, ChessPlayer1.Time.Increment*1000);
				ChessClock_voidUpdatePlayerTimeOnScreen(&ChessPlayer1);
				PCHESS_CLOCK_STATE = STATE_PLAYING;
			}
			break;

		case STATE_MACHINE_SIGNAL_PLAYER_2_BUTTON:
			if (CurrentTurn == TURN_PLAYER_2){
				CurrentTurn = TURN_PLAYER_1;
				ChessClock_voidUpdatePlayerTime(&ChessPlayer2, ChessPlayer2.Time.Increment*1000);
				ChessClock_voidUpdatePlayerTimeOnScreen(&ChessPlayer2);
				PCHESS_CLOCK_STATE = STATE_PLAYING;
			}
			break;
		case STATE_MACHINE_SIGNAL_PLAYER_1_RESIGN:
			ChessClock_voidDisplayPlayerLostOnTimeScreen(&LostOnResign,1);
			LDelay_voidSetBusyWait(3000);
			//Go to Stopped
			ChessClock_voidStoppedOnEntry();
			PCHESS_CLOCK_STATE = STATE_STOPPED;
			break;
		case STATE_MACHINE_SIGNAL_PLAYER_2_RESIGN:
			ChessClock_voidDisplayPlayerLostOnTimeScreen(&LostOnResign,2);
			LDelay_voidSetBusyWait(3000);
			//Go to Stopped
			ChessClock_voidStoppedOnEntry();
			PCHESS_CLOCK_STATE = STATE_STOPPED;
			break;

		default:
			break;
	}
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

	/*	Enable Timer 1 Clock	*/
	MRCC_voidEnablePeripheral(RCC_PER_TIM1);
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

	HLCD_voidInit((LCD_t*)&ChessLCD);
	HLCD_voidSetCursorMode((LCD_t*)&ChessLCD,LCD_CURSOR_ON_BLINK_ON);

	HENCODER_voidSetChangeCallBack(ChessClock_voidEncoderMoved);
	HENCODER_voidSetSwitchCallBack(ChessClock_voidEncoderSwitchPressed);
	HENCODER_voidInit();
	HENCODER_voidEnableEncoder();
}

/*	Initializes NVIC, STK */
static void ChessClock_voidInitMCALModules(void){

	MNVIC_voidInit(NVIC_CONFIG_1_GROUP_16_SUB);

	MSTK_voidInit(STK_CLOCK_AHB,MRCC_u32GetBusClock(RCC_BUS_AHB));
	MSTK_voidSetPeriodicInterval(CHESS_CLOCK_RTC_TRIGGER_PERIOD_MS * 1000,ChessClock_RTCCallBack);
	MSTK_voidStop();

	MTIM_voidInit(TIM1,TIM_DIRECTION_COUNT_UP,TIM_CLOCK_MODE_INTERNAL_CLK,MRCC_u32GetTimerFrequency(RCC_TIMER_1)/1000 -1,0xFFFF,0,TIM_AUTORELOAD_UPDATE_IMMEDIATE);

	LDelay_voidInit(MRCC_u32GetBusClock(RCC_BUS_AHB));
}

/*	Enables All Chess Clock Interrupts	*/
static void ChessClock_voidEnableInterrupts(void){

	/*	External Interrupts Enable	*/
	MEXTI_voidEnableInterrupt(CHESS_CLOCK_PLAYER_1_SWITCH_PIN);
	MEXTI_voidEnableInterrupt(CHESS_CLOCK_PLAYER_2_SWITCH_PIN);

	/*	Encoder Interrupts Enable	*/
	HENCODER_voidEnableEncoder();

	MNVIC_voidEnableInterrupt(NVIC_INTERRUPT_EXTI10_15);
}

/*	Disables All Chess Clock Interrupts	*/
static void ChessClock_voidDisableInterrupts(void){

	/*	External Interrupts Enable	*/
	MEXTI_voidDisableInterrupt(CHESS_CLOCK_PLAYER_1_SWITCH_PIN);
	MEXTI_voidDisableInterrupt(CHESS_CLOCK_PLAYER_2_SWITCH_PIN);

	/*	Encoder Interrupts Enable	*/
	HENCODER_voidDisableEncoder();
	MNVIC_voidDisableInterrupt(NVIC_INTERRUPT_EXTI10_15);
}


static void ChessClock_voidPlayer1Pressed(void){
	u32 PressedPeriod = 0;

	MTIM_voidStartTimeMeasure(TIM1);

	while(MGPIO_u8GetPinValue(CHESS_CLOCK_PLAYER_1_SWITCH_PORT,CHESS_CLOCK_PLAYER_1_SWITCH_PIN) == 1);

	PressedPeriod = MTIM_u16GetElapsedTicks(TIM1);

	if(PressedPeriod >= 3000)
		SM_ChessClockMain(STATE_MACHINE_SIGNAL_PLAYER_1_RESIGN);
	else
		SM_ChessClockMain(STATE_MACHINE_SIGNAL_PLAYER_1_BUTTON);

}

static void ChessClock_voidPlayer2Pressed(void){
	u32 PressedPeriod = 0;

		MTIM_voidStartTimeMeasure(TIM1);

		while(MGPIO_u8GetPinValue(CHESS_CLOCK_PLAYER_2_SWITCH_PORT,CHESS_CLOCK_PLAYER_2_SWITCH_PIN) == 1);

		PressedPeriod = MTIM_u16GetElapsedTicks(TIM1);

		if(PressedPeriod >= 3000)
			SM_ChessClockMain(STATE_MACHINE_SIGNAL_PLAYER_2_RESIGN);
		else
			SM_ChessClockMain(STATE_MACHINE_SIGNAL_PLAYER_2_BUTTON);
}

/*	Called When Encoder Moves*/
static void ChessClock_voidEncoderMoved(EncoderChange_t Direction){

	if(Direction == ENCODER_CHANGE_CLOCKWISE)
		SM_ChessClockMain(STATE_MACHINE_SIGNAL_ENCODER_STEP_CLOCKWISE);
	else if (Direction == ENCODER_CHANGE_COUNTER_CLOCKWISE)
		SM_ChessClockMain(STATE_MACHINE_SIGNAL_ENCODER_STEP_COUNTERCLOCKWISE);
}

/*	Called When Encoder Switch is Pressed	*/
static void ChessClock_voidEncoderSwitchPressed(void){

	u32 PressedPeriod = 0;

	MTIM_voidStartTimeMeasure(TIM1);

	while(HENCODER_enuGetSwitchState() == ENCODER_SWITCH_PRESSED);

	PressedPeriod = MTIM_u16GetElapsedTicks(TIM1);

	if(PressedPeriod >= 3000)
		SM_ChessClockMain(STATE_MACHINE_SIGNAL_ENTER_MORE_THAN_3_SECONDS);
	else
		SM_ChessClockMain(STATE_MACHINE_SIGNAL_ENTER_LESS_THAN_3_SECONDS);
}

void ChessClock_RTCCallBack(void)
{
	SM_ChessClockMain(STATE_MACHINE_SIGNAL_RTC_TRIGGER);
}


/*	Displays Screen_t on LCD	*/
static void ChessClock_voidDisplayScreen(ChessClockScreen_t const* screen){

	HLCD_voidClearScreen((LCD_t*)&ChessLCD);
	//HLCD_voidWriteString(&ChessLCD, " Hello ");
	for(u8 i = 0; i < 4; i++){
		HLCD_voidSetPosition((LCD_t*)&ChessLCD,0,i);
		HLCD_voidWriteString((LCD_t*)&ChessLCD,(char*)screen->Rows[i]);

	}
}


static void ChessClock_UpdateSavedModesScreenCursor(u8 Copy_u8CursorPos){
	u8 Local_u8xposition = (Copy_u8CursorPos <=3)? 0: ((Copy_u8CursorPos <= 7)? 6:13);
	u8 Local_u8yposition = (Copy_u8CursorPos) % 4;
	HLCD_voidSetPosition((LCD_t*)(&ChessLCD),Local_u8xposition, Local_u8yposition);

}

static void ChessClock_UpdateSavedModeSelectedScreenCursor(u8 Copy_u8CursorPos){
	u8 Local_u8xposition = (Copy_u8CursorPos == 0)?  6:4;
	u8 Local_u8yposition = (Copy_u8CursorPos == 0)?  1:2;;
	HLCD_voidSetPosition((LCD_t*)(&ChessLCD), Local_u8xposition, Local_u8yposition);
}



static void ChessClock_voidUpdatePlayerTime(ChessPlayer_t* Player, s16 Copy_s16MilleSeconds){

	Player->Time.BaseTime.MilleSeconds += Copy_s16MilleSeconds;
	if (Player->Time.BaseTime.MilleSeconds < 0){
		Player->Time.BaseTime.Minutes--;
		Player->Time.BaseTime.MilleSeconds += 60000;
	}
	else if(Player->Time.BaseTime.MilleSeconds > 60000){
		Player->Time.BaseTime.Minutes++;
		Player->Time.BaseTime.MilleSeconds -= 60000;
	}
}


static void ChessClock_voidUpdatePlayerTimeOnScreen(ChessPlayer_t* Player){

	s8 Local_s8arrTime[10];
	//Don't display ms if Time is more than 10 seconds
	if (Player->Time.BaseTime.Minutes > 0 || Player->Time.BaseTime.MilleSeconds > 10000){
		//Time is more than 10 seconds
		if (Player->Tag == CHESS_PLAYER_1){
			//player 1
			HLCD_voidSetPosition((LCD_t*)(&ChessLCD),3,2);
		}
		else{
			//player 2
			HLCD_voidSetPosition((LCD_t*)(&ChessLCD),12,2);
		}
		sprintf(Local_s8arrTime,"%d:%d  ",Player->Time.BaseTime.Minutes,(s16)(Player->Time.BaseTime.MilleSeconds/1000));
		HLCD_voidWriteString((LCD_t*)(&ChessLCD),Local_s8arrTime);
	}
	else{
		//Time is less than 10 seconds
		if (Player->Tag == CHESS_PLAYER_1){
			//player 1
			HLCD_voidSetPosition((LCD_t*)(&ChessLCD),3,2);
		}
		else{
			//player 2
			HLCD_voidSetPosition((LCD_t*)(&ChessLCD),12,2);
		}
		u16 MilleSeconds = Player->Time.BaseTime.MilleSeconds;
		sprintf(Local_s8arrTime,"0%d.%d  ",MilleSeconds/1000, (MilleSeconds - ((MilleSeconds/1000) * 1000))/100);
		HLCD_voidWriteString((LCD_t*)(&ChessLCD),Local_s8arrTime);
	}

}



static ChessClockMove_t ChessClock_GetFirstMoveStatus(ChessPlayer_t* Player1, ChessPlayer_t* Player2){
	return (((Player1->FirstMove == PLAYED) && (Player2->FirstMove == PLAYED))?	PLAYED:NOT_PLAYED);
}


static void ChessClock_voidDisplayPlayerLostOnTimeScreen(ChessClockScreen_t* Screen, u8 PlayerID){
	Screen->Rows[1][13] = PlayerID +'0';
	ChessClock_voidDisplayScreen(Screen);
}









//Stopped
static void ChessClock_voidStoppedOnEntry(void){
	//On Entry
	//Stop RTC
	MSTK_voidStop();
	ChessClock_voidDisplayScreen(&StoppedStateScreen);
	PCHESS_MODEModeSelector = MODE_SAVED;
	HLCD_voidSetPosition((LCD_t*)(&ChessLCD),4,2);
	HLCD_voidSetCursorMode((LCD_t*)(&ChessLCD),LCD_CURSOR_ON_BLINK_ON);
	PCHESS_CLOCK_STATE = STATE_STOPPED;
}
//Saved Mode Selected
static void ChessClock_voidSavedModeSelectedOnEntry(void){
	ChessClock_voidDisplayScreen(&SavedModesScreen);
	HLCD_voidSetPosition((LCD_t*)&ChessLCD,0,0);
	PCHESS_u8SavedModeSelector = 0;
}
//Configure Time Control
static void ChessClock_voidConfigureTimeControlOnentry(void){
	ChessClock_voidDisplayScreen(&ConfigureTimeControlScreen1);
	HLCD_voidSetPosition((LCD_t*)&ChessLCD,11,1);
	PCHESS_CLOCKCurrentField = FIELD_UNIT;
}
//Starting
static void ChessClock_voidStartingOnEntry(void){

	//Disable Cursor Flickering
	HLCD_voidSetCursorMode((LCD_t*)(&ChessLCD),LCD_CURSOR_OFF_BLINK_OFF);

	//Reset RTC
	MSTK_voidStop();

	//Display S4.1
	ChessClock_voidDisplayScreen(&StartingScreen);

	//Set First Move Flag to NOT_PLAYED
	//PCHESS_CLOCKFirstMoveFlag = NOT_PLAYED;

	//Set Player 1 Time to 30 Sec
	ChessPlayer1.Time.BaseTime.Minutes = 0;
	ChessPlayer1.Time.BaseTime.MilleSeconds = 30000;
	ChessPlayer1.FirstMove = NOT_PLAYED;

	//Set Player 2 Time to 30 Sec
	ChessPlayer2.Time.BaseTime.Minutes = 0;
	ChessPlayer2.Time.BaseTime.MilleSeconds = 30000;
	ChessPlayer2.FirstMove = NOT_PLAYED;


	//Set Turn to player1
	CurrentTurn = TURN_PLAYER_1;

	//StartRTC
	MSTK_voidSetPeriodicInterval(CHESS_CLOCK_RTC_TRIGGER_PERIOD_MS * 1000,ChessClock_RTCCallBack);

}
//Playing
static void ChessClock_voidPlayingOnEntry(void){

	//Set Turn to player1
	CurrentTurn = TURN_PLAYER_1;

	//Display screen 5.1
	ChessClock_voidDisplayScreen(&PlayingScreen);

	//Set Players Time
	ChessPlayer1.Time.BaseTime.MilleSeconds = 0;
	ChessPlayer2.Time.BaseTime.MilleSeconds = 0;

	ChessPlayer1.Time = PCHESS_arrSavedTimeModes[PCHESS_u8SavedModeSelector%12];
	ChessPlayer2.Time = PCHESS_arrSavedTimeModes[PCHESS_u8SavedModeSelector%12];

	ChessClock_voidUpdatePlayerTimeOnScreen(&ChessPlayer1);
	ChessClock_voidUpdatePlayerTimeOnScreen(&ChessPlayer2);

}

