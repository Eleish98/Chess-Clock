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

#ifndef NVIC_PRIVATE_H_INCLUDED
#define NVIC_PRIVATE_H_INCLUDED

/*	NVIC Base Address	*/
#define NVIC_BASE_ADDRESS				0xE000E100

/*	NVIC Registers	*/
typedef struct{
	volatile u32 ISER[3];
	volatile u32 RESERVED1[29];
	volatile u32 ICER[3];
	volatile u32 RESERVED2[29];
	volatile u32 ISPR[3];
	volatile u32 RESERVED3[29];
	volatile u32 ICPR[3];
	volatile u32 RESERVED4[29];
	volatile u32 IABR[4];
	volatile u32 RESERVED5[60];
	volatile u32 IPR[20];
}REG_NVIC_t;

#define NVIC_REG			((volatile REG_NVIC_t*)(NVIC_BASE_ADDRESS))

NVIC_Config_t PNVIC_GroupingConfig = 0;

#endif
