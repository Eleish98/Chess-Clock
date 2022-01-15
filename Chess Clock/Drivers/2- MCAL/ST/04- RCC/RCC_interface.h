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


#ifndef RCC_INTERFACE_H_INCLUDDED
#define RCC_INTERFACE_H_INCLUDDED
/*This enum is used with:
*
* 1- void MRCC_voidEnablePeripheral
* 2- void MRCC_voidDisablePeripheral
* 3- void MRCC_voidResetPeripheral
*
*/
typedef enum
{
	RCC_PER_TIM2,
	RCC_PER_TIM3,
	RCC_PER_TIM4,
	RCC_PER_TIM5,
	RCC_PER_TIM6,
	RCC_PER_TIM7,
	RCC_PER_TIM12,
	RCC_PER_TIM13,
	RCC_PER_TIM14,
	RCC_PER_WWDG=11,
	RCC_PER_SPI2=14,
	RCC_PER_SPI3,
	RCC_PER_USART2=17,
	RCC_PER_USART3,
	RCC_PER_USART4,
	RCC_PER_USART_5,
	RCC_PER_I2C1,
	RCC_PER_I2C2,
	RCC_PER_USB,
	RCC_PER_CAN=25,
	RCC_PER_BKP=27,
	RCC_PER_PWR,
	RCC_PER_DAC,
	RCC_PER_AFIO,
	RCC_PER_GPIOA=32,
	RCC_PER_GPIOB,
	RCC_PER_GPIOC,
	RCC_PER_GPIOD,
	RCC_PER_GPIOE,
	RCC_PER_GPIOF,
	RCC_PER_GPIOG,
	RCC_PER_ADC1,
	RCC_PER_ADC2,
	RCC_PER_TIM1,
	RCC_PER_SPI1,
	RCC_PER_TIM8,
	RCC_PER_USART1,
	RCC_PER_ADC3,
	RCC_PER_TIM9=50,
	RCC_PER_TIM10,
	RCC_PER_TIM11,
	RCC_PER_DMA1=53,
	RCC_PER_DMA2,
	RCC_PER_SRAM,
	RCC_PER_FLITF=57,
	RCC_PER_CRC=59,
	RCC_PER_FSMC=61,
	RCC_PER_SDIO=63
}RCC_PeripheralID_t;

/* This enum is used with:
*
* 1- void MRCC_voidEnableMCO
*
*/
typedef enum
{
	RCC_MCO_SYSTEM_CLOCK = 1,
	RCC_MCO_HSI_CLOCK,
	RCC_MCO_HSE_CLOCK,
	RCC_MCO_PLL_CLOCK_DIV_2
}RCC_MCO_Source_t;

/* This enum is used with:
*
* 1- void MRCC_voidSetCallBack
* 2- void MRCC_voidEnableInterrupt
* 3- void MRCC_voidDisableInterrupt
* 4- u8 MRCC_u8GetIneterruptStatus
* 5- void MRCC_voidClearInterrupt
*
*/
typedef enum{
	RCC_INTERRUPT_LSI_READY,
	RCC_INTERRUPT_LSE_READY,
	RCC_INTERRUPT_HSI_READY,
	RCC_INTERRUPT_HSE_READY,
	RCC_INTERRUPT_PLL_READY,

}RCC_Interrupt_t;

/*This enum is used with:
*
* 1- u32 MRCC_u32GetBusClock
*
*/
typedef enum{
	RCC_BUS_AHB,
	RCC_BUS_APB1,
	RCC_BUS_APB2
}RCC_BUS_t;


/*	Initializes the Clock Sources configured in configuration file*/
void MRCC_voidInitClock(void);
/*	Enables Selected Peripheral	*/
void MRCC_voidEnablePeripheral(RCC_PeripheralID_t Copy_Peripheral);
/*	Disables Selected Peripheral	*/
void MRCC_voidDisablePeripheral(RCC_PeripheralID_t Copy_Peripheral);
/*	Resets Selected Peripheral	*/
void MRCC_voidResetPeripheral(RCC_PeripheralID_t Copy_Peripheral);
/*	Enables MCO pin outputing the Selected Clock Source	*/
void MRCC_voidEnableMCO(RCC_MCO_Source_t Copy_Source);
/*	Disables MCO pin	*/
void MRCC_voidDisableMCO(void);
/*	Sets Callback function to selected interrupt source	*/
void MRCC_voidSetCallBack(RCC_Interrupt_t Interrupt, void(*Callback)(void));
/*	Enables Selected Interrupt	*/
void MRCC_voidEnableInterrupt(RCC_Interrupt_t Interrupt);
/*	Disables Selected Interrupt	*/
void MRCC_voidDisableInterrupt(RCC_Interrupt_t Interrupt);
/*	Returns Selected Interrupt Flag	*/
u8 MRCC_u8GetIneterruptStatus(RCC_Interrupt_t Interrupt);
/*	Clears Selected Interrupt Flag	*/
void MRCC_voidClearInterrupt(RCC_Interrupt_t Interrupt);
/*	Returns System Clock in Hz	*/
u32 MRCC_u32GetSystemClock(void);
/*	Returns Selected Bus Clock in Hz	*/
u32 MRCC_u32GetBusClock(RCC_BUS_t Copy_Bus);

#endif

