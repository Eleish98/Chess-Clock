/************************************************/
/*	Author		:		Mohamed G. ELeish		*/
/*	Date		:		6 September 2021		*/
/*	Version		:		V01						*/
/************************************************/

/************************************************/
/************************************************/
/*****					LOG					*****/
/*	6/9/2021:	File Created					*/
/************************************************/
/************************************************/

#ifndef BKP_PRIVATE_H_INCLUDED
#define BKP_PRIVATE_H_INCLUDED

/*	Backup Unit Base Address	*/
#define BKP_BASE_ADDRESS		0x40006C00

/*	Backup Unit Registers	*/
typedef struct{
	volatile u32 DR[10]		;
	volatile u32 RTCCR		;
	volatile u32 CR			;
	volatile u32 CSR		;
}REG_BKP_t;


#define BKP_REG			((volatile REG_BKP_t*)(BKP_BASE_ADDRESS))

/*	Backup Unit CallBack Function	*/
void (*PBKP_voidCallBack)(void) = 0;

#endif

