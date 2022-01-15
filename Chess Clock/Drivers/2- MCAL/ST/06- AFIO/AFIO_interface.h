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

#ifndef AFIO_INETRFACE_H_INCLUDED
#define AFIO_INETRFACE_H_INCLUDED

typedef enum{
	AFIO_EXTI_LINE0,
	AFIO_EXTI_LINE1,
	AFIO_EXTI_LINE2,
	AFIO_EXTI_LINE3,
	AFIO_EXTI_LINE4,
	AFIO_EXTI_LINE5,
	AFIO_EXTI_LINE6,
	AFIO_EXTI_LINE7,
	AFIO_EXTI_LINE8,
	AFIO_EXTI_LINE9,
	AFIO_EXTI_LINE10,
	AFIO_EXTI_LINE11,
	AFIO_EXTI_LINE12,
	AFIO_EXTI_LINE13,
	AFIO_EXTI_LINE14,
	AFIO_EXTI_LINE15
}AFIO_EXTIID_t;

typedef enum{
	AFIO_PORTA,
	AFIO_PORTB,
	AFIO_PORTC,
}AFIO_PORTID_t;

typedef enum{
	AFIO_JTAG_MODE_1,	//Full SWJ (JTAG-DP + SW-DP)
	AFIO_JTAG_MODE_2,	//Full SWJ (JTAG-DP + SW-DP) No NJTRST
	AFIO_JTAG_MODE_3,	//JTAG-DP Disabled, SW-DP Enabled
	AFIO_JTAG_MODE_4 = 4,	//JTAG-DP Disabled, SW-DP Disabled
}AFIO_JTAGMode_t;

typedef enum{
	AFIO_ADC_REGULAR_EXTI11,
	AFIO_ADC_REGULAR_TIM8_TRGO
}AFIO_ADCRegularTrigger_t;

typedef enum{
	AFIO_ADC_INJECTED_EXTI15,
	AFIO_ADC_INJECTED_TIM8_CH4
}AFIO_ADCInjectedTrigger_t;

typedef enum{
	AFIO_PD01_MODE_1,		//PD0 and PD1 Not Remapped
	AFIO_PD01_MODE_2		//PD0 and PD1 are Mapped to OSC_In and OSC_Out
}AFIO_PD01Mode_t;

typedef enum{
	AFIO_CAN_MODE_1,		//CAN_RX => PA11, 	CAN_TX => PA12
	AFIO_CAN_MODE_2 = 2,	//CAN_RX => PB8, 	CAN_TX => PB9
	AFIO_CAN_MODE_3			//CAN_RX => PD0, 	CAN_TX => PD1
}AFIO_CANMode_t;

typedef enum{
	AFIO_TIM4_MODE_1,		//TIM4_CH1 => PB6, 	TIM4_CH2 => PB7, 	TIM4_CH3 => PB8, 	TIM4_CH4 => PB9
	AFIO_TIM4_MODE_2		//TIM4_CH1 => PD12, TIM4_CH2 => PD13, 	TIM4_CH3 => PD14, 	TIM4_CH4 => PD15
}AFIO_TIM4Mode_t;

typedef enum{
	AFIO_TIM3_MODE_1,		//TIM3_CH1 => PA6, TIM3_CH2 => PA7, TIM3_CH3 => PB0, TIM3_CH4 => PB1
	AFIO_TIM3_MODE_2 = 2,	//TIM3_CH1 => PB4, TIM3_CH2 => PB5, TIM3_CH3 => PB0, TIM3_CH4 => PB1
	AFIO_TIM3_MODE_3		//TIM3_CH1 => PC6, TIM3_CH2 => PC7, TIM3_CH3 => PC8, TIM3_CH4 => PC9
}AFIO_TIM3Mode_t;

typedef enum{
	AFIO_TIM2_MODE_1,		//TIM2_CH1/ETR => PA0, 	TIM2_CH2 => PA1, TIM2_CH3 => PA2, 	TIM2_CH4 => PA3
	AFIO_TIM2_MODE_2,		//TIM2_CH1/ETR => PA15, TIM2_CH2 => PB2, TIM2_CH3 => PA2, 	TIM2_CH4 => PA3
	AFIO_TIM2_MODE_3,		//TIM2_CH1/ETR => PA0, 	TIM2_CH2 => PA1, TIM2_CH3 => PB10, 	TIM2_CH4 => PB11
	AFIO_TIM2_MODE_4		//TIM2_CH1/ETR => PA15, TIM2_CH2 => PB3, TIM2_CH3 => PB10, 	TIM2_CH4 => PB11
}AFIO_TIM2Mode_t;

typedef enum{
	AFIO_TIM1_MODE_1,		//ETR => PA12, CH1 => PA8, CH2 => PA9, CH3 => PA10,	CH4 => PA11, BKIN => PB12, CH1N => PB13, CH2N => PB14, CH3N => PB15
	AFIO_TIM1_MODE_2,		//ETR => PA12, CH1 => PA8, CH2 => PA9, CH3 => PA10,	CH4 => PA11, BKIN => PA6,  CH1N => PA7,  CH2N => PB0,  CH3N => PB1
	AFIO_TIM1_MODE_3 = 3,	//ETR => PE7,  CH1 => PE9, CH2 => PE11, CH3 => PE13, CH4 => PE14, BKIN => PE15, CH1N => PE8, CH2N => PE10, CH3N => PE12
	
}AFIO_TIM1Mode_t;

typedef enum{
	AFIO_USART3_MODE_1,		//TX => PB10, RX => PB11, CK => PB12,  CTS => PB13,	RTS => PB14, 
	AFIO_USART3_MODE_2,		//TX => PC10, RX => PC11, CK => PC12,  CTS => PB13,	RTS => PB14, 
	AFIO_USART3_MODE_3 = 3,	//TX => PD8,  RX => PD9,  CK => PD10,  CTS => PD11,	RTS => PD12, 
	
}AFIO_USART3Mode_t;


typedef enum{
	AFIO_USART2_MODE_1,		//TX => PA2, RX => PA3, CK => PA4,  CTS => PA0,	RTS => PA1 
	AFIO_USART2_MODE_2		//TX => PD5, RX => PD6, CK => PD7,  CTS => PD3,	RTS => PD4, 
	
}AFIO_USART2Mode_t;


typedef enum{
	AFIO_USART1_MODE_1,		//TX => PA9, RX => PA10
	AFIO_USART1_MODE_2		//TX => PB6, RX => PB7
	
}AFIO_USART1Mode_t;


typedef enum{
	AFIO_I2C1_MODE_1,		//SCL => PB6, SDA => PB7
	AFIO_I2C1_MODE_2		//SCL => PB8, SDA => PB9
	
}AFIO_I2C1Mode_t;

typedef enum{
	AFIO_SPI1_MODE_1,		//NSS => PA4, 	SCK => PA5, MISO => PA6,  MOSI => PA7
	AFIO_SPI1_MODE_2		//NSS => PA15, 	SCK => PB3, MISO => PB4,  MOSI => PB5 
	
}AFIO_SPI1Mode_t;

typedef enum{
	AFIO_FSMC_NADV_MODE_1,		//NADV signal is connected to output
	AFIO_FSMC_NADV_MODE_2		//Output Pin can be used by other i/o peripheral
	
}AFIO_FSMCMode_t;

typedef enum{
	AFIO_TIM14_MODE_1,		//CH1 => PA7
	AFIO_TIM14_MODE_2		//CH1 => PF9
	
}AFIO_TIM14Mode_t;


typedef enum{
	AFIO_TIM13_MODE_1,		//CH1 => PA6
	AFIO_TIM13_MODE_2		//CH1 => PF8
	
}AFIO_TIM13Mode_t;

typedef enum{
	AFIO_TIM11_MODE_1,		//CH1 => PB9
	AFIO_TIM11_MODE_2		//CH1 => PF7
	
}AFIO_TIM11Mode_t;

typedef enum{
	AFIO_TIM10_MODE_1,		//CH1 => PB8
	AFIO_TIM10_MODE_2		//CH1 => PF6
	
}AFIO_TIM10Mode_t;

typedef enum{
	AFIO_TIM9_MODE_1,		//CH1 => PA2,	CH2 => PA3
	AFIO_TIM9_MODE_2		//CH1 => PE5,	CH2 => PE6
	
}AFIO_TIM9Mode_t;



void MAFIO_voidSetEXTIConfiguration(AFIO_EXTIID_t EXTILine, AFIO_PORTID_t PortMap);

void MAFIO_voidEnableEventOutput(AFIO_PORTID_t Port, u8 Pin);

void MAFIO_voidDisableEventOutput(void);

void MAFIO_voidSetJTAGConfiguration(AFIO_JTAGMode_t Mode);

void MAFIO_voidRemapADC2RegularTrigger(AFIO_ADCRegularTrigger_t TriggerSource);

void MAFIO_voidRemapADC2InjectedTrigger(AFIO_ADCInjectedTrigger_t TriggerSource);

void MAFIO_voidRemapADC1RegularTrigger(AFIO_ADCRegularTrigger_t TriggerSource);

void MAFIO_voidRemapADC1InjectedTrigger(AFIO_ADCInjectedTrigger_t TriggerSource);

void MAFIO_RemapPD01(AFIO_PD01Mode_t Mode);

void MAFIO_voidRemapCAN(AFIO_CANMode_t Mode);

void MAFIO_voidRemapTIM4(AFIO_TIM4Mode_t Mode);

void MAFIO_voidRemapTIM3(AFIO_TIM3Mode_t Mode);

void MAFIO_voidRemapTIM2(AFIO_TIM2Mode_t Mode);

void MAFIO_voidRemapTIM1(AFIO_TIM1Mode_t Mode);

void MAFIO_voidRemapUSART3(AFIO_USART3Mode_t Mode);

void MAFIO_voidRemapUSART2(AFIO_USART2Mode_t Mode);

void MAFIO_voidRemapUSART1(AFIO_USART1Mode_t Mode);

void MAFIO_voidRemapI2C1(AFIO_I2C1Mode_t Mode);

void MAFIO_voidRemapSPI1(AFIO_SPI1Mode_t Mode);

void MAFIO_voidRemapFSMC(AFIO_FSMCMode_t Mode);

void MAFIO_voidRemapTIM14(AFIO_TIM14Mode_t Mode);

void MAFIO_voidRemapTIM13(AFIO_TIM13Mode_t Mode);

void MAFIO_voidRemapTIM11(AFIO_TIM11Mode_t Mode);

void MAFIO_voidRemapTIM10(AFIO_TIM10Mode_t Mode);

void MAFIO_voidRemapTIM9(AFIO_TIM9Mode_t Mode);


#endif

