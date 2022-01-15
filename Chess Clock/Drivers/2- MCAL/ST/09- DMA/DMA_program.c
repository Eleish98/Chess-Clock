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

#include "DMA_interface.h"
#include "DMA_private.h"


void MDMA_voidConfigureChannel(DMA_ChannelID_t Channel, DMA_Direction_t ChannelDir, DMA_ChannelPriority_t Priority, u16 Copy_u16BlockLength, DMA_Circular_t CircMode){
	
	u8 Local_u8MemToMem = 0;
	if(Channel > DMA_CHANNEL_7)
		return;
	
	DMA1_REG->CHANNEL[Channel].CCR &= ~((1<<14) | (3 << 12) | (1<<5) | (1 << 4));
	if(ChannelDir == DMA_DIR_MEM_TO_MEM)
		Local_u8MemToMem = 1;

	DMA1_REG->CHANNEL[Channel].CCR |= ((Local_u8MemToMem << 14) | (Priority << 12) | (CircMode << 5) | ((ChannelDir & 1) << 4));
	DMA1_REG->CHANNEL[Channel].CNDTR = Copy_u16BlockLength;
}

void MDMA_voidConfigureMem(DMA_ChannelID_t Channel, DMA_TransferSize_t MemSize, DMA_INC_t MemInc, u32* MemAddress){
	if(Channel > DMA_CHANNEL_7)
		return;
	DMA1_REG->CHANNEL[Channel].CCR &= ~((3 << 10) | (1 << 7));
	DMA1_REG->CHANNEL[Channel].CCR |= (MemSize << 10) | (MemInc << 7 );
	DMA1_REG->CHANNEL[Channel].CMAR = (u32)MemAddress;
}

void MDMA_voidConfigurePer(DMA_ChannelID_t Channel, DMA_TransferSize_t PerSize, DMA_INC_t PerInc, volatile u32* PerAddress){
	if(Channel > DMA_CHANNEL_7)
		return;
	DMA1_REG->CHANNEL[Channel].CCR &= ~((3 << 8) | (1 << 6));
	DMA1_REG->CHANNEL[Channel].CCR |= (PerSize << 8) | (PerInc << 6 );
	DMA1_REG->CHANNEL[Channel].CPAR = (u32)PerAddress;
	
}


void MDMA_voidEnableChannel(DMA_ChannelID_t Channel){
	if(Channel > DMA_CHANNEL_7)
		return;
	SET_BIT(DMA1_REG->CHANNEL[Channel].CCR,0);
}

void MDMA_voidDisableChannel(DMA_ChannelID_t Channel){
	if(Channel > DMA_CHANNEL_7)
		return;
	CLR_BIT(DMA1_REG->CHANNEL[Channel].CCR,0);
}




void MDMA_voidSetCallBack(DMA_ChannelID_t Channel, DMA_Interrupt_t Interrupt, void(*CallBack)(void)){
	if(Channel > DMA_CHANNEL_7)
		return;
	switch(Interrupt){
			case DMA_INTERRUPT_TRANSFER_COMPLETE:
				PDMA_CallBacks[Channel].TransferComplete = CallBack;
				break;
			case DMA_INTERRUPT_HALF_TRANSFER:
				PDMA_CallBacks[Channel].HalfTransfer = CallBack;
				break;
			case DMA_INTERRUPT_TRANSFER_ERROR:
				PDMA_CallBacks[Channel].TransferError = CallBack;
				break;
			default:
				return;
	}
}


void MDMA_voidEnableInterrupt(DMA_ChannelID_t Channel, DMA_Interrupt_t Interrupt){
	if(Channel > DMA_CHANNEL_7)
		return;
	SET_BIT(DMA1_REG->CHANNEL[Channel].CCR,(1+Interrupt));
}
void MDMA_voidDisableInterrupt(DMA_ChannelID_t Channel, DMA_Interrupt_t Interrupt){
	if(Channel > DMA_CHANNEL_7)
		return;
	CLR_BIT(DMA1_REG->CHANNEL[Channel].CCR,(1+Interrupt));
}


void DMA1_Channel1_IRQHandler (void){
	if(DMA1_REG->ISR & (1<<3)){
		if (PDMA_CallBacks[0].TransferError != 0)
			PDMA_CallBacks[0].TransferError();
		DMA1_REG->IFCR = 1<<3;
	}
	if(DMA1_REG->ISR & (1<<2)){
		if (PDMA_CallBacks[0].HalfTransfer != 0)
			PDMA_CallBacks[0].HalfTransfer();
		DMA1_REG->IFCR = 1<<2;
	}
	if(DMA1_REG->ISR & (1<<1)){
		if (PDMA_CallBacks[0].TransferComplete != 0)
			PDMA_CallBacks[0].TransferComplete();
		DMA1_REG->IFCR = 1<<1;
	}
	
}
void DMA1_Channel2_IRQHandler (void){
	if(DMA1_REG->ISR & (1<<7)){
		if (PDMA_CallBacks[1].TransferError != 0)
			PDMA_CallBacks[1].TransferError();
		DMA1_REG->IFCR = 1<<7;
	}
	if(DMA1_REG->ISR & (1<<6)){
		if (PDMA_CallBacks[1].HalfTransfer != 0)
			PDMA_CallBacks[1].HalfTransfer();
		DMA1_REG->IFCR = 1<<6;
	}
	if(DMA1_REG->ISR & (1<<5)){
		if (PDMA_CallBacks[1].TransferComplete != 0)
			PDMA_CallBacks[1].TransferComplete();
		DMA1_REG->IFCR = 1<<5;
	}
}
void DMA1_Channel3_IRQHandler (void){
	if(DMA1_REG->ISR & (1<<11)){
		if (PDMA_CallBacks[2].TransferError != 0)
			PDMA_CallBacks[2].TransferError();
		DMA1_REG->IFCR = 1<<11;
	}
	if(DMA1_REG->ISR & (1<<10)){
		if (PDMA_CallBacks[2].HalfTransfer != 0)
			PDMA_CallBacks[2].HalfTransfer();
		DMA1_REG->IFCR = 1<<10;
	}
	if(DMA1_REG->ISR & (1<<9)){
		if (PDMA_CallBacks[2].TransferComplete != 0)
			PDMA_CallBacks[2].TransferComplete();
		DMA1_REG->IFCR = 1<<9;
	}
}
void DMA1_Channel4_IRQHandler (void){
	if(DMA1_REG->ISR & (1<<15)){
		if (PDMA_CallBacks[3].TransferError != 0)
			PDMA_CallBacks[3].TransferError();
		DMA1_REG->IFCR = 1<<15;
	}
	if(DMA1_REG->ISR & (1<<14)){
		if (PDMA_CallBacks[3].HalfTransfer != 0)
			PDMA_CallBacks[3].HalfTransfer();
		DMA1_REG->IFCR = 1<<14;
	}
	if(DMA1_REG->ISR & (1<<13)){
		if (PDMA_CallBacks[3].TransferComplete != 0)
			PDMA_CallBacks[3].TransferComplete();
		DMA1_REG->IFCR = 1<<13;
	}
}
void DMA1_Channel5_IRQHandler (void){
	if(DMA1_REG->ISR & (1<<19)){
		if (PDMA_CallBacks[4].TransferError != 0)
			PDMA_CallBacks[4].TransferError();
		DMA1_REG->IFCR = 1<<19;
	}
	if(DMA1_REG->ISR & (1<<18)){
		if (PDMA_CallBacks[4].HalfTransfer != 0)
			PDMA_CallBacks[4].HalfTransfer();
		DMA1_REG->IFCR = 1<<18;
	}
	if(DMA1_REG->ISR & (1<<17)){
		if (PDMA_CallBacks[4].TransferComplete != 0)
			PDMA_CallBacks[4].TransferComplete();
		DMA1_REG->IFCR = 1<<17;
	}
}

void DMA1_Channel6_IRQHandler (void){
	if(DMA1_REG->ISR & (1<<23)){
		if (PDMA_CallBacks[5].TransferError != 0)
			PDMA_CallBacks[5].TransferError();
		DMA1_REG->IFCR = 1<<23;
	}
	if(DMA1_REG->ISR & (1<<22)){
		if (PDMA_CallBacks[5].HalfTransfer != 0)
			PDMA_CallBacks[5].HalfTransfer();
		DMA1_REG->IFCR = 1<<22;
	}
	if(DMA1_REG->ISR & (1<<21)){
		if (PDMA_CallBacks[5].TransferComplete != 0)
			PDMA_CallBacks[5].TransferComplete();
		DMA1_REG->IFCR = 1<<21;
	}
}
void DMA1_Channel7_IRQHandler (void){
	if(DMA1_REG->ISR & (1<<27)){
		if (PDMA_CallBacks[6].TransferError != 0)
			PDMA_CallBacks[6].TransferError();
		DMA1_REG->IFCR = 1<<27;
	}
	if(DMA1_REG->ISR & (1<<26)){
		if (PDMA_CallBacks[6].HalfTransfer != 0)
			PDMA_CallBacks[6].HalfTransfer();
		DMA1_REG->IFCR = 1<<26;
	}
	if(DMA1_REG->ISR & (1<<25)){
		if (PDMA_CallBacks[6].TransferComplete != 0)
			PDMA_CallBacks[6].TransferComplete();
		DMA1_REG->IFCR = 1<<25;
	}
}






