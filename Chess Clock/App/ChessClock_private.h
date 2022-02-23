/*
 * ChessClock_private.h
 *
 *  Created on: Jan 16, 2022
 *      Author: 20109
 */

#ifndef CHESSCLOCK_PRIVATE_H_
#define CHESSCLOCK_PRIVATE_H_

typedef enum{
	FLAG_SET,
	FLAG_CLEAR
}ChessClockFlagValue_t;



typedef enum{
	MODE_SAVED,
	MODE_MANUAL
}ChessClockMode_t;




typedef enum {

	STATE_STOPPED,
	STATE_SAVED_MODE_SELECTED,
	STATE_CONFIGURE_TIME_CONTROL,
	STATE_STARTING, STATE_PLAYING
}ChessClockState_t;

typedef enum {

	CHESS_PLAYER_1,
	CHESS_PLAYER_2
}ChessPlayerTag_t;

typedef enum {

	TURN_PLAYER_1,
	TURN_PLAYER_2
}ChessTurn_t;

typedef struct {

	ChessPlayerTag_t Tag;
	u16 Time;
}ChessPlayer_t;



ChessPlayer_t ChessPlayer1, ChessPlayer2;

/***************** Local Functions ***************************/
/*	Enables RCC Clock for All Used Peripherals	*/
static void ChessClock_voidEnablePeripheralClock(void);

/*	Configures Switches Used Pins	*/
static void ChessClock_voidSetPinsDirections(void);

/*	Configures All Used Interrupts	*/
static void ChessClock_voidConfigureInterrupts(void);

/*	Initializes LCD, Encoder	*/
static void ChessClock_voidInitHALModules(void);

/*	Initializes NVIC, STK, SCB */
static void ChessClock_voidInitMCALModules(void);

/*	Enables All Chess Clock Interrupts	*/
static void ChessClock_voidEnableInterrupts(void);

/*	Disables All Chess Clock Interrupts	*/
static void ChessClock_voidDisableInterrupts(void);


/**************	CallBack Functions	***************************/

/*	Called When Player 1 Switch is pressed	*/
static void ChessClock_voidPlayer1Pressed(void);

/*	Called When Player 2 Switch is pressed	*/
static void ChessClock_voidPlayer2Pressed(void);

/*	Called When Encoder Moves*/
static void ChessClock_voidEncoderMoved(EncoderChange_t Direction);


/*************************************************************/
/*********************State Machine***************************/
/*************************************************************/

/*************** State Machine Functions**********************/

void SM_StoppedState(void);

void SM_SavedModeSelectedState(void);

void SM_ConfiguringTimeControlState(void);

void SM_StartingState(void);

void SM_PlayingState(void);

void SM_ChessClockMain(void);

/**************** State Machine Signals ************************/
typedef enum{
	STATE_MACHINE_SIGNAL_ENTER_LESS_THAN_3_SECONDS,
	STATE_MACHINE_SIGNAL_ENTER_MORE_THAN_3_SECONDS,
	STATE_MACHINE_SIGNAL_ENCODER_STEP_CLOCKWISE,
	STATE_MACHINE_SIGNAL_ENCODER_STEP_COUNTERCLOCKWISE,
	STATE_MACHINE_SIGNAL_RTC_TRIGGER,
	STATE_MACHINE_SIGNAL_PLAYER_1_BUTTON,
	STATE_MACHINE_SIGNAL_PLAYER_2_BUTTON
}ChessClockSignal_t;


/*************** State Machine Variables **********************/

ChessClockState_t PCHESS_CLOCK_STATE = STATE_STOPPED;

ChessClockMode_t PCHESS_MODEModeSelector = MODE_SAVED;

u8 PCHESS_u8SavedModeSelector = 0;


/************** State Machine Flags ***************************/
ChessClockFlagValue_t PCHESS_FLAGModeSelected = FLAG_CLEAR;


#endif /* CHESSCLOCK_PRIVATE_H_ */
