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

#ifndef DMA_INTERFACE_H_INCLUDED
#define DMA_INTERFACE_H_INCLUDED


typedef enum{
	DMA_CHANNEL_1,
	DMA_CHANNEL_2,
	DMA_CHANNEL_3,
	DMA_CHANNEL_4,
	DMA_CHANNEL_5,
	DMA_CHANNEL_6,
	DMA_CHANNEL_7,
	
}DMA_ChannelID_t;

typedef enum{
	DMA_TRANSFER_BYTE,
	DMA_TRANSFER_HALF_WORD,
	DMA_TRANSFER_WORD
}DMA_TransferSize_t;

typedef enum{
	DMA_DIR_PER_TO_MEM,
	DMA_DIR_MEM_TO_PER,
	DMA_DIR_MEM_TO_MEM		//When Chosen, Data source is set by PER, Destination is set by MEM
}DMA_Direction_t;

typedef enum{
	DMA_INC_DISABLED,
	DMA_INC_ENABLED
}DMA_INC_t;

typedef enum{
	DMA_PRIORITY_LOW,
	DMA_PRIORITY_MEDIUM,
	DMA_PRIORITY_HIGH,
	DMA_PRIORITY_VERY_HIGH
}DMA_ChannelPriority_t;

typedef enum{
	DMA_CIRCULAR_DISABLED,
	DMA_CIRCULAR_ENABLED
}DMA_Circular_t;


typedef enum{
	DMA_INTERRUPT_TRANSFER_COMPLETE,
	DMA_INTERRUPT_HALF_TRANSFER,
	DMA_INTERRUPT_TRANSFER_ERROR
}DMA_Interrupt_t;



typedef enum{
	DMA_CHANNEL1_ADC1,
	DMA_CHANNEL1_TIM3_CH3,
	DMA_CHANNEL1_TIM4_CH1
}DMA_Channel1Peripherals;


typedef enum{
	DMA_CHANNEL2_SPI1_RX,
	DMA_CHANNEL2_USART3_TX,
	DMA_CHANNEL2_TIM1_CH1,
	DMA_CHANNEL2_TIM2_UP,
	DMA_CHANNEL2_TIM3_CH3
}DMA_Channel2Peripherals;

typedef enum{
	DMA_CHANNEL3_SPI1_TX,
	DMA_CHANNEL3_USART3_RX,
	DMA_CHANNEL3_TIM3_CH4,
	DMA_CHANNEL3_TIM3_UP
}DMA_Channel3Peripherals;

typedef enum{
	DMA_CHANNEL4_SPI2_I2S2_RX,
	DMA_CHANNEL4_USART1_TX,
	DMA_CHANNEL4_I2C2_TX,
	DMA_CHANNEL4_TIM1_CH4,
	DMA_CHANNEL4_TIM1_TRIG,
	DMA_CHANNEL4_TIM1_COM,
	DMA_CHANNEL4_TIM4_CH2
}DMA_Channel4Peripherals;

typedef enum{
	DMA_CHANNEL5_SPI2_I2S2_TX,
	DMA_CHANNEL5_USART1_RX,
	DMA_CHANNEL5_I2C2_RX,
	DMA_CHANNEL5_TIM2_CH1,
	DMA_CHANNEL5_TIM4_CH3
}DMA_Channel5Peripherals;

typedef enum{
	DMA_CHANNEL6_USART2_RX,
	DMA_CHANNEL6_I2C1_TX,
	DMA_CHANNEL6_TIM1_CH3,
	DMA_CHANNEL6_TIM3_CH1,
	DMA_CHANNEL6_TIM3_TRIG,
}DMA_Channel6Peripherals;

typedef enum{
	DMA_CHANNEL7_USART2_TX,
	DMA_CHANNEL7_I2C1_RX,
	DMA_CHANNEL7_TIM2_CH2,
	DMA_CHANNEL7_TIM2_CH4,
	DMA_CHANNEL7_TIM4_UP
}DMA_Channel7Peripherals;




void MDMA_voidConfigureChannel(DMA_ChannelID_t Channel, DMA_Direction_t ChannelDir, DMA_ChannelPriority_t Priority, u16 Copy_u16BlockLength,DMA_Circular_t CircMode);

void MDMA_voidConfigureMem(DMA_ChannelID_t Channel, DMA_TransferSize_t MemSize, DMA_INC_t MemInc, u32* MemAddress);
void MDMA_voidConfigurePer(DMA_ChannelID_t Channel, DMA_TransferSize_t PerSize, DMA_INC_t PerInc,volatile  u32* PerAddress);


void MDMA_voidEnableChannel(DMA_ChannelID_t Channel);
void MDMA_voidDisableChannel(DMA_ChannelID_t Channel);

void MDMA_voidSetCallBack(DMA_ChannelID_t Channel, DMA_Interrupt_t Interrupt, void(*CallBack)(void));
void MDMA_voidEnableInterrupt(DMA_ChannelID_t Channel, DMA_Interrupt_t Interrupt);
void MDMA_voidDisableInterrupt(DMA_ChannelID_t Channel, DMA_Interrupt_t Interrupt);

#endif

