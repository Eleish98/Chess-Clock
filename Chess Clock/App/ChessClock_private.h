/*
 * ChessClock_private.h
 *
 *  Created on: Jan 16, 2022
 *      Author: 20109
 */

#ifndef CHESSCLOCK_PRIVATE_H_
#define CHESSCLOCK_PRIVATE_H_

#define CHESS_CLOCK_RTC_TRIGGER_PERIOD_MS		((u32)100)

typedef struct{
	u8 Rows[4][21];
}ChessClockScreen_t;

typedef enum{
	FLAG_SET,
	FLAG_CLEAR
}ChessClockFlagValue_t;

typedef enum{
	FIELD_UNIT,
	FIELD_TIME,
	FIELD_INCREMENT
}ChessClockField_t;

typedef enum{
	NOT_PLAYED,
	PLAYED,
}ChessClockMove_t;

typedef enum{
	MODE_SAVED,
	MODE_MANUAL
}ChessClockMode_t;


typedef enum {
	STATE_IDLE,
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
	u8 Minutes;
	s32 MilleSeconds;
}Time_t;

typedef struct {
	Time_t BaseTime;
	u8 Increment;
}ChessTime_t;

typedef struct {

	ChessPlayerTag_t Tag;
	ChessTime_t Time;
	ChessClockMove_t FirstMove;
}ChessPlayer_t;


/**************	Local Variables	******************************/

GPIO_Pin_t ChessLCDDataPins[] = {CHESS_CLOCK_LCD_D4_PIN,CHESS_CLOCK_LCD_D5_PIN,CHESS_CLOCK_LCD_D6_PIN,CHESS_CLOCK_LCD_D7_PIN};
GPIO_Port_t ChessLCDDataPorts[] = {CHESS_CLOCK_LCD_D4_PORT,CHESS_CLOCK_LCD_D5_PORT,CHESS_CLOCK_LCD_D6_PORT,CHESS_CLOCK_LCD_D7_PORT};


const LCD_t	ChessLCD = {LCD_MODE_4_BIT,{4,20},{CHESS_CLOCK_LCD_RS_PIN,CHESS_CLOCK_LCD_RW_PIN,CHESS_CLOCK_LCD_E_PIN},
										{CHESS_CLOCK_LCD_RS_PORT,CHESS_CLOCK_LCD_RW_PORT,CHESS_CLOCK_LCD_E_PORT},
										ChessLCDDataPins,ChessLCDDataPorts};

ChessPlayer_t ChessPlayer1 = {CHESS_PLAYER_1, {{0,0}}, NOT_PLAYED}, ChessPlayer2 = {CHESS_PLAYER_2,{{0,0}}, NOT_PLAYED};

const ChessTime_t PCHESS_arrSavedTimeModes[] = {{{1,0},0},{{3,0},5},{{5,0},0},{{5,0},5},{{10,0},0},{{10,0},5},{{30,0},0},{{15,0},10},{{20,0},0},{{30,0},0},{{60,0},0}};

//const ChessTime_t PCHESS_arrSavedTimeModes[] = {{{1,0}},{{3,5}},{{5,0}},{{5,5}},{{10,0}},{{10,5}},{{30,0}},{{15,10}},{{20,0}},{{30,0}},{{60,0}}};

const ChessClockScreen_t StoppedStateScreen = {{	"    CHESS CLOCK     ",
													"    Choose Mode:    ",
													"    *Saved Modes    ",
													"   *Enter Manually  "
											  }};

const ChessClockScreen_t SavedModesScreen = {{		"A 1+0 E 10+0 I 15+10",
													"B 3+5 F 10+5 J 20+00",
													"C 5+0 G 15+0 K 30+00",
													"D 5+5 F 30+0 L 60+00"
											  }};

const ChessClockScreen_t SavedModeSelectedScreen =
											  {{	"                    ",
													"       Start        ",
													"     Re-Select      ",
													"                    "
											  }};


const ChessClockScreen_t ConfigureTimeControlScreen1 =
											  {{	"  Set Time Control  ",
													"     unit: Min      ",
													"   Minutes: 0 Min   ",
													"  Increment: 0 Sec  "
											  }};

const ChessClockScreen_t ConfigureTimeControlScreen2 =
											  {{	"                    ",
													" Start  Config Time ",
													"                    ",
													"                    "
											  }};

const ChessClockScreen_t StartingScreen = 	  {{	"                    ",
													"  Player1  Player2  ",
													"   0:30     0:30    ",
													"                    "
											  }};

const ChessClockScreen_t PlayingScreen = 	  {{	"                    ",
													"  Player1  Player2  ",
													"                    ",
													"                    "
											  }};
ChessClockScreen_t LostOnFirstMoveScreen = 	  {{	"                    ",
													"     Player         ",
													" Lost On First Move ",
													"                    "
											  }};

ChessClockScreen_t LostOnTimeScreen = 	  {{	"                    ",
													"     Player         ",
													"    Lost On Time    ",
													"                    "
											  }};

ChessClockScreen_t LostOnResign = 	  {{	"                    ",
											"     Player         ",
											"      Resigned      ",
											"                    "
									  }};

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

/*	Displays Screen_t on LCD	*/
static void ChessClock_voidDisplayScreen(ChessClockScreen_t const *screen);

/*	Updates the Cursor position in SavedModeSelected State	*/
static void ChessClock_UpdateSavedModesScreenCursor(u8 Copy_u8CursorPos);

/*	Updates the Cursor position in SavedModeSelectedState	*/
static void ChessClock_UpdateSavedModeSelectedScreenCursor(u8 Copy_u8CursorPos);

/*	Updates the Player Time with MilleSeconds value	*/
static void ChessClock_voidUpdatePlayerTime(ChessPlayer_t* Player, s16 Copy_s16MilleSeconds);

/*	Updates the Displayed Player Time	*/
static void ChessClock_voidUpdatePlayerTimeOnScreen(ChessPlayer_t* Player);

/*	Returns the state of the first move if played or not	*/
static ChessClockMove_t ChessClock_GetFirstMoveStatus(ChessPlayer_t* Player1, ChessPlayer_t* Player2);

/*	Displays the Lost on First Move Screen with the player Number	*/
static void ChessClock_voidDisplayPlayerLostOnTimeScreen(ChessClockScreen_t* Screen, u8 PlayerID);


static void ChessClock_voidDisplayResignedPlayer(ChessClockScreen_t* Screen, u8 PlayerID);



/* States On-Entry Functions	*/
//Stopped
static void ChessClock_voidStoppedOnEntry(void);
//Saved Mode Selected
static void ChessClock_voidSavedModeSelectedOnEntry(void);
//Configure Time Control
static void ChessClock_voidConfigureTimeControlOnentry(void);
//Starting
static void ChessClock_voidStartingOnEntry(void);
//Playing
static void ChessClock_voidPlayingOnEntry(void);

/**************	CallBack Functions	***************************/

/*	Called When Player 1 Switch is pressed	*/
static void ChessClock_voidPlayer1Pressed(void);

/*	Called When Player 2 Switch is pressed	*/
static void ChessClock_voidPlayer2Pressed(void);

/*	Called When Encoder Moves*/
static void ChessClock_voidEncoderMoved(EncoderChange_t Direction);

/*	Called When Encoder Switch is Pressed	*/
static void ChessClock_voidEncoderSwitchPressed(void);

/*	Called When RTC Trigger every 10 msec	*/
static void ChessClock_RTCCallBack(void);

/*************************************************************/
/*********************State Machine***************************/
/*************************************************************/

/**************** State Machine Signals ************************/
typedef enum{
	STATE_MACHINE_SIGNAL_INITIAL,
	STATE_MACHINE_SIGNAL_ENTER_LESS_THAN_3_SECONDS,
	STATE_MACHINE_SIGNAL_ENTER_MORE_THAN_3_SECONDS,
	STATE_MACHINE_SIGNAL_ENCODER_STEP_CLOCKWISE,
	STATE_MACHINE_SIGNAL_ENCODER_STEP_COUNTERCLOCKWISE,
	STATE_MACHINE_SIGNAL_RTC_TRIGGER,
	STATE_MACHINE_SIGNAL_PLAYER_1_BUTTON,
	STATE_MACHINE_SIGNAL_PLAYER_1_RESIGN,
	STATE_MACHINE_SIGNAL_PLAYER_2_BUTTON,
	STATE_MACHINE_SIGNAL_PLAYER_2_RESIGN
}ChessClockSignal_t;



/*************** State Machine Functions**********************/

void SM_StoppedState(ChessClockSignal_t Signal);

void SM_SavedModeSelectedState(ChessClockSignal_t Signal);

void SM_ConfiguringTimeControlState(ChessClockSignal_t Signal);

void SM_StartingState(ChessClockSignal_t Signal);

void SM_PlayingState(ChessClockSignal_t Signal);

void SM_ChessClockMain(ChessClockSignal_t Signal);



/*************** State Machine Variables **********************/

ChessClockState_t PCHESS_CLOCK_STATE = STATE_IDLE;

ChessClockMode_t PCHESS_MODEModeSelector = MODE_SAVED;

u8 PCHESS_u8SavedModeSelector = 0;

u8 PCHESS_u8SavedModeEnsuring = 0;

ChessClockField_t PCHESS_CLOCKCurrentField = FIELD_UNIT;

ChessTurn_t CurrentTurn = TURN_PLAYER_1;

/************** State Machine Flags ***************************/
ChessClockFlagValue_t PCHESS_FLAGModeSelected = FLAG_CLEAR;

//ChessClockMove_t PCHESS_CLOCKFirstMoveFlag = NOT_PLAYED;

#endif /* CHESSCLOCK_PRIVATE_H_ */
