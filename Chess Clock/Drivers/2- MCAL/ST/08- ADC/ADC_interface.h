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

#ifndef ADC_INTERFACE_H_INCLUDED
#define ADC_INTERFACE_H_INCLUDED

typedef enum {
	ADC1,
	ADC2
}ADC_ID_t;


typedef enum{
	
	ADC_MODE_SINGLE_CHANNEL,
	ADC_MODE_SCAN_CHANNELS
	
}ADC_Mode_t;

typedef enum{
	ADC_CONV_SINGLE,
	ADC_CONV_CONTINIOUS
}ADC_Conversion_t;

typedef enum{
	ADC_CHANNEL_0,
	ADC_CHANNEL_1,
	ADC_CHANNEL_2,
	ADC_CHANNEL_3,
	ADC_CHANNEL_4,
	ADC_CHANNEL_5,
	ADC_CHANNEL_6,
	ADC_CHANNEL_7,
	ADC_CHANNEL_8,
	ADC_CHANNEL_9,
	ADC_CHANNEL_10,
	ADC_CHANNEL_11,
	ADC_CHANNEL_12,
	ADC_CHANNEL_13,
	ADC_CHANNEL_14,
	ADC_CHANNEL_15,
	ADC_CHANNEL_TEMP_SENSOR,
	ADC_CHANNEL_INT_REF
}ADC_ChannelID_t;

typedef enum{
	ADC_REG_TRIG_TIM1_CC1,
	ADC_REG_TRIG_TIM1_CC2,
	ADC_REG_TRIG_TIM1_CC3,
	ADC_REG_TRIG_TIM2_CC2,
	ADC_REG_TRIG_TIM2_TRGO,
	ADC_REG_TRIG_TIM4_CC4,
	ADC_REG_TRIG_EXTI_LINE11,
	ADC_REG_TRIG_SOFTWARE
	
}ADC_RegularTrigger_t;

typedef enum{
	ADC_INJ_TRIG_TIM1_TRGO,
	ADC_INJ_TRIG_TIM1_CC4,
	ADC_INJ_TRIG_TIM2_TRGO,
	ADC_INJ_TRIG_TIM2_CC1,
	ADC_INJ_TRIG_TIM3_CC4,
	ADC_INJ_TRIG_TIM4_TRGO,
	ADC_INJ_TRIG_EXTI_LINE15,
	ADC_INJ_TRIG_SOFTWARE

}ADC_InjectedTrigger_t;

typedef enum{

	ADC_SAMPLE_1_5_CYCLES,
	ADC_SAMPLE_7_5_CYCLES,
	ADC_SAMPLE_13_5_CYCLES,
	ADC_SAMPLE_28_5_CYCLES,
	ADC_SAMPLE_41_5_CYCLES,
	ADC_SAMPLE_55_5_CYCLES,
	ADC_SAMPLE_71_5_CYCLES,
	ADC_SAMPLE_239_5_CYCLES
	
}ADC_Sample_t;

typedef enum{

	ADC_ANALOG_WATCHDOG_ALL_CHANNELS,
	ADC_ANALOG_WATCHDOG_SINGLE_CHANNEL

}ADC_AnalogWatchDogMode_t;

typedef enum{

	ADC_INJ_CHANNEL_0,
	ADC_INJ_CHANNEL_1,
	ADC_INJ_CHANNEL_2,
	ADC_INJ_CHANNEL_3
}ADC_InjectedChannelID_t;

typedef enum{
	ADC_INTERRUPT_END_REGULAR = 5,
	ADC_INTERRUPT_ANALOG_WATCHDOG,
	ADC_INTERRUPT_END_INJECTED
}ADC_Interrupt_t;

/*	Must Be Called at first and sets the mode for the ADC	*/
void MADC_voidInit(ADC_ID_t ADC, ADC_Mode_t Mode, ADC_Conversion_t ConversionType);

/*	Sets Scan Mode with an array of channels	*/
void MADC_voidConfigureRegularChannels(ADC_ID_t ADC, ADC_ChannelID_t Channels[], u8 NumberOfChannels);

/*	Starts ADC when configured in Continuous and Discontinuous using software*/
void MADC_voidStartRegularConversions(ADC_ID_t ADC);

/*	Stops ADC when configured in Continuous and Discontinuous using software*/
void MADC_voidStopRegularConversions(ADC_ID_t ADC);

/*	Configure Discontinuous Mode	*/
/*	The ADC Must be configured in continuous at first and scan mode must be configured beforehand	*/
void MADC_voidConfigureDiscontinuous(ADC_ID_t ADC, u8 NumberOfChannels);

/*	Enables Discontinuous Mode For Regular Group	*/
void MADC_voidEnableRegularDiscontinuous(ADC_ID_t ADC);

/*	Disables Discontinuous Mode For Regular Group	*/
void MADC_voidDisableRegularDiscontinuous(ADC_ID_t ADC);

/*	Sets Sampling Time for a channel	*/
void MADC_voidSetChannelSampleTime(ADC_ID_t ADC, ADC_ChannelID_t Channel, ADC_Sample_t Sample);

/*	Sets the trigger Source for ADC Regular Conversion	*/
void MADC_voidConfigureRegularTrigger(ADC_ID_t ADC, ADC_RegularTrigger_t Trigger);

/*	Reads Channel Then Returns the Result	*/
u16 MADC_u16ReadChannel(ADC_ID_t ADC, ADC_ChannelID_t Channel);

/*	Returns the Last Result of Regular Channel Conversion	*/
u16 MADC_u16GetRegularData(ADC_ID_t ADC);

/*	Enables Trigger for Regular GROUP */
void MADC_voidEnableRegularTrigger(ADC_ID_t ADC);

/*	Disables Trigger for Regular GROUP */
void MADC_voidDisableRegularTrigger(ADC_ID_t ADC);

/*	Sets Mode for Analog WatchDog	*/
void MADC_voidConfigureAnalogWatchDog(ADC_ID_t ADC, ADC_AnalogWatchDogMode_t Mode);

/*	Sets Analog WatchDog channel if Single Channel Mode was Chosen	*/
void MADC_voidSetAnalogWatchDogSingleChannel(ADC_ID_t ADC, ADC_ChannelID_t Channel);

/*	Sets Analog WatchDog Limits	*/
void MADC_voidSetAnalogWatchDogLimits(ADC_ID_t ADC, u16 UpperLimit, u16 LowerLimit);

/*	Enables Analog WatchDog	*/
void MADC_voidEnableAnalogWatchDogOnRegular(ADC_ID_t ADC);

/*	Disables Analog WatchDog	*/
void MADC_voidDisableAnalogWatchDogOnRegular(ADC_ID_t ADC);

/*	Configures Injected Channels */
/*	Number of channels must not exceed 4	*/
void MADC_voidConfigureInjectedChannels(ADC_ID_t ADC, ADC_ChannelID_t Channels[], u8 NumberOfChannels);

/*	Start ADC when configured in Continuous and Discontinuous using software	*/
void MADC_voidStartInjectedConversions(ADC_ID_t ADC);

/*	Stops Injected Conversions for Continuous and Discontinuous Modes	*/
void MADC_voidStopInjectedConversions(ADC_ID_t ADC);

/*	Sets Trigger Source for Injected Conversions	*/
void MADC_voidConfigureInjectedTrigger(ADC_ID_t ADC, ADC_InjectedTrigger_t Trigger);

/*	Enables Trigger fir Injected Group	*/
void MADC_voidEnableInjectedTrigger(ADC_ID_t ADC);

/*	Disables Trigger for Injected Group	*/
void MADC_voidDisableInjectedTrigger(ADC_ID_t ADC);

/*	Enables Analog WatchDog on Injected Group Channels	*/
void MADC_voidEnableAnalogWatchDogOnInjected(ADC_ID_t ADC);

/*	Disables Analog WatchDog on Injected Group Channels	*/
void MADC_voidDisableAnalogWatchDogOnInjected(ADC_ID_t ADC);

/*	Enables Analog WatchDog on Injected Group	*/
void MADC_voidEnableInjectedDiscontinuous(ADC_ID_t ADC);

/*	Disables Analog WatchDog on Injected Group	*/
void MADC_voidDisableInjectedDiscontinuous(ADC_ID_t ADC);

/*	Sets the Offset that would be subtracted from the Injected Group Reading	*/
void MADC_voidSetInjectedOffset(ADC_ID_t ADC, ADC_InjectedChannelID_t Channel, u16 Offset);

/*	Returns the Result of the Injected Channels	*/
s16 MADC_s16GetInjectedData(ADC_ID_t ADC, ADC_InjectedChannelID_t Channel);

/*	Enables the Conversion of Injected Group after the Conversion of Regular Group	*/
void MADC_voidEnableAutoInjected(ADC_ID_t ADC);

/*	Disables the Conversion of Injected Group after the Conversion of Regular Group	*/
void MADC_voidDisableAutoInjected(ADC_ID_t ADC);

/*	Returns the Address for the Regular Data Register to be used with DMA */
volatile u32* MADC_u32PtrGetRegularDataAddress(ADC_ID_t ADC);

/*	Returns the Address for the Injected Data Register to be used with DMA */
volatile u32* MADC_u32PtrGetInjectedDataAddress(ADC_ID_t ADC, ADC_InjectedChannelID_t Channel);

/*	Enables DMA Request for End of Conversion	*/
void MADC_voidEnableDMARequest(ADC_ID_t ADC);

/*	Disables DMA Request for End of Conversion	*/
void MADC_voidDisableDMARequest(ADC_ID_t ADC);

/*	Enables the ability to read the temperature sensor and Internal reference voltage	*/
void MADC_voidEnableTemperatureRefInt(ADC_ID_t ADC);

/*	Disables the ability to read the temperature sensor and Internal reference voltage	*/
void MADC_voidDisableTemperatureRefInt(ADC_ID_t ADC);

/*	Returns the Temperature using the temperature Sensor	*/
f32 MADC_f32GetTemperatureFromReading(ADC_ID_t ADC, u16 SensorReading);

/*	Returns the Internal voltage reference	*/
f32 MADC_f32GetInternalVoltage(ADC_ID_t ADC);

/*	Calibrates ADC and returns the Calibration value	*/
u16 MADC_u16Calibrate(ADC_ID_t ADC);

/*	Enables Interrupt for ADC	*/
void MADC_voidEnableInterrupt(ADC_ID_t ADC, ADC_Interrupt_t Interrupt);

/*	Disables Interrupt for ADC	*/
void MADC_voidDisableInterrupt(ADC_ID_t ADC, ADC_Interrupt_t Interrupt);

/*	Sets Interrupt Callback for ADC	*/
void MADC_voidSetCallBack(ADC_ID_t ADC, ADC_Interrupt_t Interrupt, void(*CallBack)(void));




#endif

