/*
 * ChessClock_private.h
 *
 *  Created on: Jan 16, 2022
 *      Author: 20109
 */

#ifndef CHESSCLOCK_PRIVATE_H_
#define CHESSCLOCK_PRIVATE_H_

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



ChessClockState_t PCHESS_CLOCK_STATE;

ChessPlayer_t ChessPlayer1, ChessPlayer2;




#endif /* CHESSCLOCK_PRIVATE_H_ */
