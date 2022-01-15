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
#ifndef ADC_PRIVATE_H_INCLUDED
#define ADC_PRIVATE_H_INCLUDED

#define ADC1_BASE_ADDRESS				0x40012400
#define ADC2_BASE_ADDRESS				0x40012800



typedef struct{
	
	volatile u32 SR			;
	volatile u32 CR1		;
	volatile u32 CR2		;
	volatile u32 SMPR[2]	;
	volatile u32 JOFR[4]	;
	volatile u32 HTR		;
	volatile u32 LTR		;
	volatile u32 SQR[3]		;
	volatile u32 JSQR		;
	volatile u32 JDR[4]		;
	volatile u32 DR			;
	
}REG_ADC_t;

#define ADC1_REG				((volatile REG_ADC_t*)(ADC1_BASE_ADDRESS))
#define ADC2_REG				((volatile REG_ADC_t*)(ADC2_BASE_ADDRESS))


#define ADC_TEMP_SENSOR_V_SENSE			(1)
#define ADC_TEMP_SENSOR_AVG_SLOP		(4.3e-3)
#define ADC_TEMP_SENSOR_V_25			(1.377)



volatile REG_ADC_t  *ADCS[2] = {ADC1_REG,ADC2_REG};

void (*ADCSInterruptHandlers[2][3])(void);

#endif


