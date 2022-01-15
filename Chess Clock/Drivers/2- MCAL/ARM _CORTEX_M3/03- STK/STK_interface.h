/************************************************/
/*	Author		:		Mohamed G. ELeish		*/
/*	Date		:		8 September 2021		*/
/*	Version		:		V01						*/
/************************************************/

/************************************************/
/************************************************/
/*****					LOG					*****/
/*	8/9/2021:	File Created					*/
/************************************************/
/************************************************/

#ifndef STK_INTERFACE_H_INCLUDED
#define STK_INTERFACE_H_INCLUDED

typedef enum{
	STK_CLOCK_AHB_DIV_8,
	STK_CLOCK_AHB
}STK_ClockSource_t;

typedef struct{
	STK_ClockSource_t ClockSource;
	u32 AHBClockFrequency;
}STK_Config_t;

void MSTK_voidInit(STK_ClockSource_t Copy_ClockSource, u32 Copy_u32AHBClockFrequency);

void MSTK_voidStop(void);

void MSTK_voidSetBusyWaitUS(u32 Copy_u32MicroSec);

void MSTK_voidSetPeriodicInterval(u32 Copy_u32MicroSec, void(*CallBack)(void));

void MSTK_voidSetSingleInterval(u32 Copy_u32MicroSec, void(*CallBack)(void));

u32 MSTK_u32GetElapsedTime(void);

u32 MSTK_u32GetRemainingTime(void);

void MSTK_voidClibrate(void);

#endif

