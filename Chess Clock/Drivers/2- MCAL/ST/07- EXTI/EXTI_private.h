/************************************************/
/*	Author		:		Mohamed G. ELeish		*/
/*	Date		:		5 September 2021		*/
/*	Version		:		V01						*/
/************************************************/

/************************************************/
/************************************************/
/*****					LOG					*****/
/*	5/9/2021:	File Created					*/
/************************************************/
/************************************************/

#ifndef EXTI_PRIVATE_H_INCLUDED
#define EXTI_PRIVATE_H_INCLUDED

#define EXTI_BASE_ADDRESS					0x40010400

typedef struct{
	volatile u32 IMR	;
	volatile u32 EMR	;
	volatile u32 RTSR	;
	volatile u32 FTSR	;
	volatile u32 SWIER	;
	volatile u32 PR		;
}REG_EXTI_t;


#define EXTI_REG			((volatile REG_EXTI_t*)(EXTI_BASE_ADDRESS))

void (*PEXTI_CallBacks[19])(void);

#endif

