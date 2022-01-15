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

#ifndef GPIO_INTERFACE_H_INCLUDED
#define GPIO_INTERFACE_H_INCLUDED

/* This enum is used with All Functions in this driver */
typedef enum{
	GPIO_PORTA,
	GPIO_PORTB,
	GPIO_PORTC
}GPIO_Port_t;

/* This enum is used with:
*
* 1- void	MGPIO_voidSetPinDirection
* 2- void	MGPIO_voidSetPinSpeed
* 3- void	MGPIO_voidSetPin
* 4- void	MGPIO_voidClearPin	
* 5- void	MGPIO_voidSetPinValue
* 6- u8		MGPIO_u8GetPinValue
* 7- void 	MGPIO_voidLockPin
*
*/
typedef enum{
	GPIO_PIN_0,
	GPIO_PIN_1,
	GPIO_PIN_2,
	GPIO_PIN_3,
	GPIO_PIN_4,
	GPIO_PIN_5,
	GPIO_PIN_6,
	GPIO_PIN_7,
	GPIO_PIN_8,
	GPIO_PIN_9,
	GPIO_PIN_10,
	GPIO_PIN_11,
	GPIO_PIN_12,
	GPIO_PIN_13,
	GPIO_PIN_14,
	GPIO_PIN_15,
}GPIO_Pin_t;


/* This enum is used with:
*
* 1- void 	MGPIO_voidSetPinSpeed	
* 2- void 	MGPIO_voidSetPortSpeed
*
*/
typedef enum{
	GPIO_SPEED_10_MHZ = 1,
	GPIO_SPEED_2_MHZ,
	GPIO_SPEED_50_MHZ
}GPIO_Speed_t;


typedef enum{
	GPIO_PULL_UP = 0,
	GPIO_PULL_DOWN = 16
}GPIO_Pull_t;

/* This enum is used with:
*
* 1- void	MGPIO_voidSetPinDirection
* 2- void 	MGPIO_voidSetPortDirection
*
*/

typedef enum{
	GPIO_DIR_OUTPUT_PUSH_PULL = 2,
	GPIO_DIR_OUTPUT_OPEN_DRAIN = 6,
	GPIO_DIR_ALTERNATE_FUNCTION_PUSH_PULL = 10,
	GPIO_DIR_ALTERNATE_FUNCTION_OPEN_DRAIN = 14,
	GPIO_DIR_INPUT_ANALOG = 0,
	GPIO_DIR_INPUT_FLOATING = 4,
	GPIO_DIR_INPUT_PULL_UP_DOWN = 8
}GPIO_Direction_t;



/*	Sets Pin to Selected Mode	*/
/*	when a pin is configured to be output, its speed defaults to 2 MHz	*/
/*	When Configured to input Pullup_down, Pull Down Resistor is the default	*/
void MGPIO_voidSetPinDirection	(GPIO_Port_t Copy_Port, GPIO_Pin_t  Copy_Pin, GPIO_Direction_t Copy_Dir);
/*	Sets Port to Selected Mode, when a pin is configured to be output, its speed defaults to 2 MHz	*/
void MGPIO_voidSetPortDirection	(GPIO_Port_t Copy_Port, GPIO_Direction_t Copy_Dir);
/*	Sets Pin to Selected Speed	*/
void MGPIO_voidSetPinSpeed		(GPIO_Port_t Copy_Port, GPIO_Pin_t  Copy_Pin, GPIO_Speed_t Copy_Speed);
/*	Sets Port to Selected Speed	*/
void MGPIO_voidSetPortSpeed		(GPIO_Port_t Copy_Port, GPIO_Speed_t Copy_Speed);
/*	Sets Pull Up or Pull Down resistor for an input pin	*/
void MGPIO_voidSetPinPull(GPIO_Port_t Copy_Port, GPIO_Pin_t Copy_Pin, GPIO_Pull_t Copy_Pull);
/*	Sets Pull Up or Pull Down resistor for an input port	*/
void MGPIO_voidSetPortPull(GPIO_Port_t Copy_Port, GPIO_Pull_t Copy_Pull);
/*	Sets pin to High	*/
void MGPIO_voidSetPin			(GPIO_Port_t Copy_Port, GPIO_Pin_t Copy_Pin);
/*	Sets Port to High	*/
void MGPIO_voidSetPort			(GPIO_Port_t Copy_Port);
/*	Sets Pin to Low		*/
void MGPIO_voidClearPin			(GPIO_Port_t Copy_Port, GPIO_Pin_t Copy_Pin);
/*	Sets Port to Low	*/
void MGPIO_voidClearPort		(GPIO_Port_t Copy_Port);
/*	Sets Pin to selected Value	*/
void MGPIO_voidSetPinValue		(GPIO_Port_t Copy_Port, GPIO_Pin_t Copy_Pin, u8 Copy_u8Value);
/*	Sets Port to selected Value	*/
void MGPIO_voidSetPortValue		(GPIO_Port_t Copy_Port, u16 Copy_u16Value);
/*	Returns Pin Value	*/
u8	 MGPIO_u8GetPinValue		(GPIO_Port_t Copy_Port, GPIO_Pin_t Copy_Pin);
/*	Returns Port Value	*/
u16  MGPIO_u16GetPortValue		(GPIO_Port_t Copy_Port);
/*	Locks Pin	*/
void MGPIO_voidLockPin			(GPIO_Port_t Copy_Port, GPIO_Pin_t Copy_Pin);
/*	Locks Port	*/
void MGPIO_voidLockPort			(GPIO_Port_t Copy_Port);

#endif

