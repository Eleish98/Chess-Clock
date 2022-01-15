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

#ifndef CRC_INTERFACE_H_INCLUDED
#define CRC_INTERFACE_H_INCLUDED

/*	Initializes the CRC Unit	*/
void MCRC_voidInit(void);

/*	Calculates 32-Bit CRC Code on One 32-bit Word*/
u32 MCRC_u32CalculateOnWord(u32 Copy_u32Word);

/*	Calculates 32-Bit CRC Code on Multiple 32-Bit Words*/
u32 MCRC_u32CalculateOnWordArray(u32 *Copy_u32Ptr, u32 Len);




#endif

