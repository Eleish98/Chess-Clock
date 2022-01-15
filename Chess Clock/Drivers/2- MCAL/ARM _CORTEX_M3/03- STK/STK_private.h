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

#ifndef STK_PRIVATE_H_INCLUDED
#define STK_PRIVATE_H_INCLUDED

#define SYSTICK_BASE_ADDRESS					0xE000E010

typedef struct{
	volatile u32 CTRL		;
	volatile u32 LOAD		;
	volatile u32 VAL		;
	volatile u32 CALIB		;
}REG_SYSTICK_t;


#define STK_REG				((volatile REG_SYSTICK_t*)(SYSTICK_BASE_ADDRESS))

u32 PSTK_u32TicksPerMicroSeconds = 1;

u8 PSTK_u8SingleInterruptFlag = 0;

void (*PSTK_voidUnderFlowCallBack)(void) = 0;

#endif

