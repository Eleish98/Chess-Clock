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

#ifndef CRC_PRIVATE_H_INCLUDED
#define CRC_PRIVATE_H_INCLUDED

/*	Cyclic Redunduncy Check Unit Base Address	*/
#define CRC_BASE_ADDRESS		0x40023000

/*	Cyclic Redunduncy Check Unit Registers	*/
typedef struct{
	volatile u32 DR;
	volatile u32 IDR;
	volatile u32 CR;
}REG_CRC_t;


#define CRC_REG		((volatile REG_CRC_t*)(CRC_BASE_ADDRESS))




#endif

