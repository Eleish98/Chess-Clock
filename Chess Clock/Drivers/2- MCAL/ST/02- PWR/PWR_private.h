/************************************************/
/*	Author		:		Mohamed G. ELeish		*/
/*	Date		:		6 September 2021		*/
/*	Version		:		V01						*/
/************************************************/

/************************************************/
/************************************************/
/*****					LOG					*****/
/*	6/9/2021:	File Created					*/
/************************************************/
/************************************************/

#ifndef PWR_PRIVATE_H_INCLUDED
#define PWR_PRIVATE_H_INCLUDED

/*	Power Unit Base Address	*/
#define PWR_BASE_ADDRESS		0x40007000

/*	Power Unit Registers	*/
typedef struct{
	volatile u32 CR;
	volatile u32 CSR;
	
}REG_PWR_t;


#define PWR_REG		((volatile REG_PWR_t*)(PWR_BASE_ADDRESS))


#endif

