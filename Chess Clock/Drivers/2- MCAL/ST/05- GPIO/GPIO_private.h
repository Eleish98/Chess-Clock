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

#ifndef GPIO_PRIVATE_H_INCLUDED
#define GPIO_PRIVATE_H_INCLUDED

/*	Numper of GPIO Ports in STM32F103C8T6	*/
#define GPIO_NUMBER_OF_PORTS			3

/*	GPIO Units Base Addresses	*/
#define GPIO_PORTA_BASE_ADDRESS			0x40010800
#define GPIO_PORTB_BASE_ADDRESS			0x40010C00
#define GPIO_PORTC_BASE_ADDRESS			0x40011000

/*	GPIO Unit Registers		*/
typedef struct{
	
	volatile u32 CRL		;
	volatile u32 CRH		;
	volatile u32 IDR		;
	volatile u32 ODR		;
	volatile u32 BSRR		;
	volatile u32 BRR		;
	volatile u32 LCKR		;
}REG_GPIO_t;


#define GPIO_PORTA_REG				((volatile REG_GPIO_t*)(GPIO_PORTA_BASE_ADDRESS))
#define GPIO_PORTB_REG				((volatile REG_GPIO_t*)(GPIO_PORTB_BASE_ADDRESS))
#define GPIO_PORTC_REG				((volatile REG_GPIO_t*)(GPIO_PORTC_BASE_ADDRESS))

volatile REG_GPIO_t* GPIO_REG[GPIO_NUMBER_OF_PORTS] = {GPIO_PORTA_REG,GPIO_PORTB_REG,GPIO_PORTC_REG};

/*	Max GPIO ID */
#define GPIO_MAX_GPIO_ID			GPIO_PORTC

#endif

