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
#include "1- LIB/STD_TYPES.h"
#include "1- LIB/BIT_MATH.h"

#include "ADC_interface.h"
#include "ADC_private.h"



/*	Must Be Called at first and sets the mode for the ADC	*/
void MADC_voidInit(ADC_ID_t ADC, ADC_Mode_t Mode, ADC_Conversion_t ConversionType){
	if(ADC > ADC2)
		return;
	//Set Mode
	CLR_BIT(ADCS[ADC]->CR1,8);
	ADCS[ADC]->CR1 |= (Mode << 8);
	
	//Enable ADC
	SET_BIT(ADCS[ADC]->CR2,0);
}

/*	Sets Scan Mode with an array of channels	*/
void MADC_voidConfigureRegularChannels(ADC_ID_t ADC, ADC_ChannelID_t Channels[], u8 NumberOfChannels){
	if(ADC > ADC2 || NumberOfChannels > 16)
		return;
	ADCS[ADC]->SQR[0] &= ~(0xF << 20);
	ADCS[ADC]->SQR[0] |= ((NumberOfChannels -1 ) << 20);
	for(u8 i = 0; i < NumberOfChannels; i++){
		ADCS[ADC]->SQR[2-i/6] &= ~(0x1F << ((i%6) * 5));
		ADCS[ADC]->SQR[2-i/6] |= (Channels[i] << ((i%6)*5));
	}
	//Enable Continuous mode
	SET_BIT(ADCS[ADC]->CR2,1);
}

/*	Starts ADC when configured in Continuous, Scan and Discontinuous using software*/
void MADC_voidStartRegularConversions(ADC_ID_t ADC){
	if(ADC > ADC2)
		return;
	SET_BIT(ADCS[ADC]->CR2,1);
	SET_BIT(ADCS[ADC]->CR2,22);
	while(CHK_BIT(ADCS[ADC]->CR2,22));
}

/*	Stops ADC when configured in Continuous and Discontinuous using software*/
void MADC_voidStopRegularConversions(ADC_ID_t ADC){
	if(ADC > ADC2)
		return;
	CLR_BIT(ADCS[ADC]->CR2,1);
	CLR_BIT(ADCS[ADC]->CR2,22);
}

/*	Configure Discontinuous Mode for Regular Group	*/
/*	The ADC Must be configured in continuous at first and scan mode must be configured beforehand	*/
void MADC_voidConfigureDiscontinuous(ADC_ID_t ADC, u8 NumberOfChannels){
	if(ADC > ADC2)
		return;
	
	ADCS[ADC]->CR1 &= ~(0x7 << 13);
	ADCS[ADC]->CR1 |= ((NumberOfChannels & 7) << 13);
}

void MADC_voidEnableRegularDiscontinuous(ADC_ID_t ADC){
	if(ADC > ADC2)
			return;
	SET_BIT(ADCS[ADC]->CR1,11);
}

void MADC_voidDisableRegularDiscontinuous(ADC_ID_t ADC){
	if(ADC > ADC2)
		return;
	CLR_BIT(ADCS[ADC]->CR1,11);
}

/*	Sets Sampling Time for a channel	*/
void MADC_voidSetChannelSampleTime(ADC_ID_t ADC, ADC_ChannelID_t Channel, ADC_Sample_t Sample){
	if(ADC > ADC2 || Channel > ADC_CHANNEL_INT_REF)
		return;
	ADCS[ADC]->SMPR[1-Channel/10] &= ~(0x7 << ((Channel%10) * 3));
	ADCS[ADC]->SMPR[1-Channel/10] |= ((Sample & 0x7) << ((Channel%10) * 3));
}

/*	Sets the trigger Source for ADC Regular Conversion	*/
void MADC_voidConfigureRegularTrigger(ADC_ID_t ADC, ADC_RegularTrigger_t Trigger){
	if(ADC > ADC2 || Trigger > ADC_REG_TRIG_SOFTWARE)
		return;
	ADCS[ADC]->CR2 &= ~(0x7 << 17);
	ADCS[ADC]->CR2 |= (Trigger << 17);

}

/*	Reads Channel Then Returns the Result	*/
u16 MADC_u16ReadChannel(ADC_ID_t ADC, ADC_ChannelID_t Channel){
	if(ADC > ADC2 || Channel > ADC_CHANNEL_INT_REF)
		return 0xFFFF;
	ADCS[ADC]->SQR[0] &= ~(0xF << 20);
	ADCS[ADC]->SQR[2] &= ~(0x1F);

	ADCS[ADC]->SQR[2] |= Channel;

	SET_BIT(ADCS[ADC]->CR2,0);

	while(!CHK_BIT(ADCS[ADC]->SR,1));

	ADCS[ADC]->SR = (1<<2);

	return ADCS[ADC]->DR & 0xFFF;
}

u16 MADC_u16GetRegularData(ADC_ID_t ADC){
	if(ADC > ADC2)
		return 0xFFFF;
	return ADCS[ADC]->DR;
}

/*	Enables Trigger for Regular GROUP */
void MADC_voidEnableRegularTrigger(ADC_ID_t ADC){
	if(ADC > ADC2)
		return;
	SET_BIT(ADCS[ADC]->CR2,20);
}

/*	Disables Trigger for Regular GROUP */
void MADC_voidDisableRegularTrigger(ADC_ID_t ADC){
	if(ADC > ADC2)
		return;
	CLR_BIT(ADCS[ADC]->CR2,20);
}

/*	Sets Mode for Analog WatchDog	*/
void MADC_voidConfigureAnalogWatchDog(ADC_ID_t ADC, ADC_AnalogWatchDogMode_t Mode){
	if (ADC > ADC2)
		return;
	CLR_BIT(ADCS[ADC]->CR1,9);
	ADCS[ADC]->CR1 |= (Mode & 1) << 9;
}

/*	Sets Analog WatchDog channel if Single Channel Mode was Chosen	*/
void MADC_voidSetAnalogWatchDogSingleChannel(ADC_ID_t ADC, ADC_ChannelID_t Channel){
	if (ADC > ADC2)
		return;
	ADCS[ADC]->CR1 &= (~0x1F);
	ADCS[ADC]->CR1 |= Channel & 0x1F;
}

/*	Sets Analog WatchDog Limits	*/
void MADC_voidSetAnalogWatchDogLimits(ADC_ID_t ADC, u16 UpperLimit, u16 LowerLimit){
	if(ADC > ADC2)
		return;
	ADCS[ADC]->LTR = LowerLimit;
	ADCS[ADC]->HTR = UpperLimit;
}

/*	Enables Analog WatchDog	*/
void MADC_voidEnableAnalogWatchDogOnRegular(ADC_ID_t ADC){
	if (ADC > ADC2)
		return;
	SET_BIT(ADCS[ADC]->CR1,23);

}

/*	Disables Analog WatchDog	*/
void MADC_voidDisableAnalogWatchDogOnRegular(ADC_ID_t ADC){
	if (ADC > ADC2)
		return;
	CLR_BIT(ADCS[ADC]->CR1,23);
}


/*	Configures Injected Channels */
/*	Number of channels must not exceed 4	*/
void MADC_voidConfigureInjectedChannels(ADC_ID_t ADC, ADC_ChannelID_t Channels[], u8 NumberOfChannels){

	if(ADC > ADC2 || NumberOfChannels > 4 || NumberOfChannels == 0)
		return;
	ADCS[ADC]->JSQR = (NumberOfChannels - 1)<<20;
	switch(NumberOfChannels){
		case 1:
			ADCS[ADC]->JSQR |= Channels[0]<<15;
			break;
		case 2:
			ADCS[ADC]->JSQR |= Channels[0]<<10 | Channels[1]<<15;
			break;
		case 3:
			ADCS[ADC]->JSQR |= Channels[0]<<5 | Channels[1]<<10 | Channels[2] << 15;
			break;
		case 4:
			ADCS[ADC]->JSQR |= Channels[0] | Channels[1]<<5 | Channels[2] << 10 | Channels[3] << 15;
			break;
	}

}

/*	Start ADC when configured in Continuous and Discontinuous using software	*/
void MADC_voidStartInjectedConversions(ADC_ID_t ADC){
	if(ADC > ADC2)
		return;
	SET_BIT(ADCS[ADC]->CR2,1);
	SET_BIT(ADCS[ADC]->CR2,21);
	while(CHK_BIT(ADCS[ADC]->CR2,21));
}

/*	Stops Injected Conversions for Continuous and Discontinuous Modes	*/
void MADC_voidStopInjectedConversions(ADC_ID_t ADC){
	if(ADC > ADC2)
		return;
	CLR_BIT(ADCS[ADC]->CR2,1);
	CLR_BIT(ADCS[ADC]->CR2,21);
}

/*	Sets Trigger Source for Injected Conversions	*/
void MADC_voidConfigureInjectedTrigger(ADC_ID_t ADC, ADC_InjectedTrigger_t Trigger){
	if(ADC > ADC2)
		return;
	ADCS[ADC]->CR2 &= ~(0x7 << 12);
	ADCS[ADC]->CR2 |= (Trigger & 0x7)<<12;
}

/*	Enables Trigger for Injected Group	*/
void MADC_voidEnableInjectedTrigger(ADC_ID_t ADC){
	if(ADC > ADC2)
		return;
	SET_BIT(ADCS[ADC]->CR2,15);
}

/*	Disables Trigger for Injected Group	*/
void MADC_voidDisableInjectedTrigger(ADC_ID_t ADC){
	if(ADC > ADC2)
		return;
	CLR_BIT(ADCS[ADC]->CR2,15);
}

/*	Enables Analog WatchDog on Injected Group Channels	*/
void MADC_voidEnableAnalogWatchDogOnInjected(ADC_ID_t ADC){
	if(ADC > ADC2)
			return;
	SET_BIT(ADCS[ADC]->CR1,22);
}

/*	Disables Analog WatchDog on Injected Group Channels	*/
void MADC_voidDisableAnalogWatchDogOnInjected(ADC_ID_t ADC){
	if(ADC > ADC2)
			return;
	CLR_BIT(ADCS[ADC]->CR1,22);
}

/*	Enables Analog WatchDog on Injected Group	*/
void MADC_voidEnableInjectedDiscontinuous(ADC_ID_t ADC){
	if(ADC > ADC2)
		return;
	SET_BIT(ADCS[ADC]->CR1,12);
}

/*	Disables Analog WatchDog on Injected Group	*/
void MADC_voidDisableInjectedDiscontinuous(ADC_ID_t ADC){
	if(ADC > ADC2)
		return;
	CLR_BIT(ADCS[ADC]->CR1,12);
}


/*	Sets the Offset that would be subtracted from the Injected Group Reading	*/
void MADC_voidSetInjectedOffset(ADC_ID_t ADC, ADC_InjectedChannelID_t Channel, u16 Offset){
	if(ADC > ADC2 || Channel > ADC_INJ_CHANNEL_3)
		return;
	ADCS[ADC]->JOFR[Channel] = Offset;
}

/*	Returns the Result of the Injected Channels	*/
s16 MADC_s16GetInjectedData(ADC_ID_t ADC, ADC_InjectedChannelID_t Channel){
	if(ADC > ADC2 ||  Channel > ADC_INJ_CHANNEL_3)
		return 0xFFFF;
	return ADCS[ADC]->JDR[Channel];
}

/*	Enables the Conversion of Injected Group after the Conversion of Regular Group	*/
void MADC_voidEnableAutoInjected(ADC_ID_t ADC){
	if(ADC > ADC2)
		return;
	SET_BIT(ADCS[ADC]->CR1,10);
}

/*	Disables the Conversion of Injected Group after the Conversion of Regular Group	*/
void MADC_voidDisableAutoInjected(ADC_ID_t ADC){
	if(ADC > ADC2)
		return;
	CLR_BIT(ADCS[ADC]->CR1,10);
}

/*	Returns the Address for the Regular Data Register to be used with DMA */
volatile u32* MADC_u32PtrGetRegularDataAddress(ADC_ID_t ADC){
	if(ADC > ADC2)
		return 0;
	return &(ADCS[ADC]->DR);
}

/*	Returns the Address for the Injected Data Register to be used with DMA */
volatile u32* MADC_u32PtrGetInjectedDataAddress(ADC_ID_t ADC, ADC_InjectedChannelID_t Channel){
	if(ADC > ADC2 || Channel > ADC_INJ_CHANNEL_3)
		return 0;
	return &(ADCS[ADC]->JDR[Channel]);
}

/*	Enables DMA Request for End of Conversion	*/
void MADC_voidEnableDMARequest(ADC_ID_t ADC){
	if(ADC > ADC2)
		return;
	SET_BIT(ADCS[ADC]->CR2,8);
}

/*	Disables DMA Request for End of Conversion	*/
void MADC_voidDisableDMARequest(ADC_ID_t ADC){
	if(ADC > ADC2)
		return;
	CLR_BIT(ADCS[ADC]->CR2,8);
}

/*	Enables the ability to read the temperature sensor and Internal reference voltage	*/
void MADC_voidEnableTemperatureRefInt(ADC_ID_t ADC){
	if(ADC > ADC2)
		return;
	SET_BIT(ADCS[ADC]->CR2,23);
}

/*	Disables the ability to read the temperature sensor and Internal reference voltage	*/
void MADC_voidDisableTemperatureRefInt(ADC_ID_t ADC){
	if(ADC > ADC2)
		return;
	CLR_BIT(ADCS[ADC]->CR2,23);
}

/*	Returns the Temperature using the temperature Sensor	*/
f32 MADC_f32GetTemperatureFromReading(ADC_ID_t ADC, u16 SensorReading){
	if(ADC > ADC2)
		return 0;
	f32 Temperature = ((ADC_TEMP_SENSOR_V_25 - (SensorReading*3.3/4096.0))/ADC_TEMP_SENSOR_AVG_SLOP) + 25;
	return Temperature;
}

/*	Returns the Internal voltage reference	*/
f32 MADC_f32GetInternalVoltage(ADC_ID_t ADC){
	if(ADC > ADC2)
		return 0;
	return MADC_u16ReadChannel(ADC,ADC_CHANNEL_INT_REF)*3.3/4096;
}

/*	Calibrates ADC and returns the Calibration value	*/
u16 MADC_u16Calibrate(ADC_ID_t ADC){
	if(ADC > ADC2)
		return 0xFFFF;
	SET_BIT(ADCS[ADC]->CR2,2);
	while(CHK_BIT(ADCS[ADC]->CR2,2));
	return ADCS[ADC]->DR & 0xFFFF;
}


/*	Enables Interrupt for ADC	*/
void MADC_voidEnableInterrupt(ADC_ID_t ADC, ADC_Interrupt_t Interrupt){
	if(ADC > ADC2)
		return;
	SET_BIT(ADCS[ADC]->CR1,Interrupt);
}

/*	Disables Interrupt for ADC	*/
void MADC_voidDisableInterrupt(ADC_ID_t ADC, ADC_Interrupt_t Interrupt){
	if(ADC > ADC2)
		return;
	CLR_BIT(ADCS[ADC]->CR1,Interrupt);
}

/*	Sets Interrupt Callback for ADC	*/
void MADC_voidSetCallBack(ADC_ID_t ADC, ADC_Interrupt_t Interrupt, void(*CallBack)(void)){
	if(ADC > ADC2 || Interrupt > ADC_INTERRUPT_END_INJECTED || Interrupt < ADC_INTERRUPT_END_REGULAR)
		return;
	ADCSInterruptHandlers[ADC][Interrupt] = CallBack;
}

void ADC1_2_IRQHandler(void){
	if(CHK_BIT(ADCS[ADC1]->SR,0) && ADCSInterruptHandlers[0][1] != 0){	//Analog WatchDog, ADC1
		ADCSInterruptHandlers[0][1]();
		ADCS[ADC1]->SR &= ~1;
	}

	if(CHK_BIT(ADCS[ADC1]->SR,1) && ADCSInterruptHandlers[0][0] != 0){	//End of Regular Conversion, ADC1
		ADCSInterruptHandlers[0][0]();
		ADCS[ADC1]->SR &= ~2;
	}

	if(CHK_BIT(ADCS[ADC1]->SR,2) && ADCSInterruptHandlers[0][2] != 0){	//End of Injected Conversion, ADC1
		ADCSInterruptHandlers[0][2]();
		ADCS[ADC1]->SR &= ~4;
	}

	if(CHK_BIT(ADCS[ADC2]->SR,0) && ADCSInterruptHandlers[1][1] != 0){	//Analog WatchDog, ADC2
		ADCSInterruptHandlers[1][1]();
		ADCS[ADC2]->SR &= ~1;
	}

	if(CHK_BIT(ADCS[ADC2]->SR,1) && ADCSInterruptHandlers[1][0] != 0){	//End of Regular Conversion, ADC2
		ADCSInterruptHandlers[1][0]();
		ADCS[ADC2]->SR &= ~2;
	}

	if(CHK_BIT(ADCS[ADC2]->SR,2) && ADCSInterruptHandlers[1][2] != 0){	//End of Injected Conversion, ADC2
		ADCSInterruptHandlers[1][2]();
		ADCS[ADC2]->SR &= ~4;
	}
}
