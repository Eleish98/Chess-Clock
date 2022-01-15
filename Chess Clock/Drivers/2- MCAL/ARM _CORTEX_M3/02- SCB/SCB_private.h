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

#ifndef SCB_PRIVATE_H_INCLUEDED
#define SCB_PRIVATE_H_INCLUEDED

/*	System Control Block Base Memeory Address*/
#define SCB_BASE_ADDRESS		0xE000ED00

/*	System Control Bock Registers*/
typedef struct{
	volatile u32 CPUID		;
	volatile u32 ICSR		;
	volatile u32 VTOR		;
	volatile u32 AIRCR		;
	volatile u32 SCR		;
	volatile u32 CCR		;
	volatile u32 SHPR1		;
	volatile u32 SHPR2		;
	volatile u32 SHPR3		;
	volatile u32 SHCSR		;
	volatile u32 CFSR		;
	volatile u32 RESERVED	;
	volatile u32 HFSR		;
	volatile u32 MMFAR		;
	volatile u32 BFAR		;
}REG_SCB_t;


#define SCB_REG		((volatile REG_SCB_t*)(SCB_BASE_ADDRESS))

/*	Write Key for AIRCR Registers	*/
#define SCB_AIRCR_WRITE_KEY			0x05FA0000

#endif


