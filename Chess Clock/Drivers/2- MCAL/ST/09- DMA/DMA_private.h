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
#ifndef DMA_PRIVATE_H_INCLUDED
#define DMA_PRIVATE_H_INCLUDED




#define DMA1_BASE_ADDRESS					0x40020000
#define DMA2_BASE_ADDRESS					0x40020400


typedef struct{
	volatile u32 CCR		;
	volatile u32 CNDTR		;
	volatile u32 CPAR		;
	volatile u32 CMAR		;
	volatile u32 RESERVED	;
	
}REG_DMA_CHANNEL_t;

typedef struct{
	volatile u32 ISR							;
	volatile u32 IFCR							;
	volatile REG_DMA_CHANNEL_t CHANNEL[7]		;
	
	
}REG_DMA_t;


#define DMA1_REG			((volatile REG_DMA_t *)(DMA1_BASE_ADDRESS))


typedef struct{
	void (*TransferComplete)(void);
	void (*HalfTransfer)(void);
	void (*TransferError)(void);
}DMA_InterruptCallBacks_t;


DMA_InterruptCallBacks_t PDMA_CallBacks[7];

#endif



