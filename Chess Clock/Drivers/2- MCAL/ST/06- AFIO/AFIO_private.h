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

#ifndef AFIO_PRIVATE_H_INCLUDED
#define AFIO_PRIVATE_H_INCLUDED

#define AFIO_BASE_ADDRESS					0x40010000

typedef struct{
	volatile u32 EVCR		;
	volatile u32 MAPR		;
	volatile u32 EXTICR[4]	;
	volatile u32 MAPR2		;
}REG_AFIO_t;


#define AFIO_REG				((volatile REG_AFIO_t*)(AFIO_BASE_ADDRESS))


#endif

