/************************************************/
/*	Author		:		Mohamed G. ELeish		*/
/*	Date		:		4 September 2021		*/
/*	Version		:		V01						*/
/************************************************/

/************************************************/
/************************************************/
/*****					LOG					*****/
/*	4/9/2021:	File Created					*/
/************************************************/
/************************************************/


#ifndef RCC_PRIVATE_H_INCLUDDED
#define RCC_PRIVATE_H_INCLUDDED

/*	Reset and Clock Control Unit Base Address	*/
#define RCC_BASE_ADDRESS		0x40021000

/*	Reset and Clock Control Unit Registers	*/
typedef struct{
	volatile u32 CR			;
	volatile u32 CFGR		;
	volatile u32 CIR		;
	volatile u32 APB2RSTR	;
	volatile u32 APB1RSTR	;
	volatile u32 AHBENR	 	;
	volatile u32 APB2ENR	;
	volatile u32 APB1ENR	;
	volatile u32 BDCR		;
	volatile u32 CSR		;
	
}REG_RCC_t;


#define RCC_REG			((volatile REG_RCC_t*)(RCC_BASE_ADDRESS))

/*	Options for System Clock Selection	*/
#define RCC_CLOCK_HSI				0
#define RCC_CLOCK_PLL				1
#define RCC_CLOCK_HSE				2

/*	Options for High Frequenct External Clock	*/
#define RCC_HSE_CRYSTAL				3
#define	RCC_HSE_EXTERNAL_SOURCE 	4

/*	Options for PLL Clock Input		*/
#define RCC_HSE						5
#define RCC_HSE_DIV_2				6
#define RCC_HSI_DIV_2				7

/*	Options for PLL Multiplier	*/
#define RCC_PLL_MULT_2				0
#define RCC_PLL_MULT_3				1
#define RCC_PLL_MULT_4				2
#define RCC_PLL_MULT_5				3
#define RCC_PLL_MULT_6				4
#define RCC_PLL_MULT_7				5
#define RCC_PLL_MULT_8				6
#define RCC_PLL_MULT_9				7
#define RCC_PLL_MULT_10				8
#define RCC_PLL_MULT_11				9
#define RCC_PLL_MULT_12				10
#define RCC_PLL_MULT_13				11
#define RCC_PLL_MULT_14				12
#define RCC_PLL_MULT_15				13
#define RCC_PLL_MULT_16				14


#define RCC_ENABLE					1
#define RCC_DISABLE					0

/*	Options for Low Frequency External Clock	*/
#define RCC_LSE_CRYSTAL				0
#define RCC_LSE_EXTERNAL_SOURCE		1

/*	Options for Real Time Clock Input	*/
#define RCC_HSE_DIV_128				3
#define RCC_LSE_32_768KHZ			1
#define RCC_LSI_40KHZ				2

/*	Options for USB Input Clock		*/
#define RCC_PLL_CLOCLK_DIV_1		1
#define RCC_PLL_CLOCLK_1_5			0

/*	Options for AHB Clock Input	*/
#define RCC_SYSTEM_CLCOCK_DIV_1		0
#define RCC_SYSTEM_CLCOCK_DIV_2		8
#define RCC_SYSTEM_CLCOCK_DIV_4		9
#define RCC_SYSTEM_CLCOCK_DIV_8		10
#define RCC_SYSTEM_CLCOCK_DIV_16	11
#define RCC_SYSTEM_CLCOCK_DIV_64	12
#define RCC_SYSTEM_CLCOCK_DIV_128	13
#define RCC_SYSTEM_CLCOCK_DIV_256	14
#define RCC_SYSTEM_CLCOCK_DIV_512	15

/*	Options for APB1 and APB2 Clock Input	*/
#define RCC_AHB_CLOCK_DIV_1			0
#define RCC_AHB_CLOCK_DIV_2			4
#define RCC_AHB_CLOCK_DIV_4			5
#define RCC_AHB_CLOCK_DIV_8			6
#define RCC_AHB_CLOCK_DIV_16		7

/*	Options for ADC Clock Input	*/
#define RCC_APB2_CLOCK_DIV_2		0
#define RCC_APB2_CLOCK_DIV_4		1
#define RCC_APB2_CLOCK_DIV_6		2
#define RCC_APB2_CLOCK_DIV_8		3

/*	CallBacks for RCC	*/
void (*PRCC_voidCallBacks[5])(void)={0,0,0,0,0};

/*	Prescalars for AHB, APB1 and APB2	*/
u16 PRCC_u16AHBPrescalars[9] = {1,2,4,8,16,64,128,256,512};
u16 PRCC_u16APBPescalars[4] = {2,4,8,16};

#endif

