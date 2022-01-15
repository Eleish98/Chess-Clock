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

#include "CRC_interface.h"
#include "CRC_private.h"

void MCRC_voidInit(void){
	/*	Resets CRC Unit	*/
	SET_BIT(CRC_REG->CR,0);
}

u32 MCRC_u32CalculateOnWord(u32 Copy_u32Word){
	/*	Reset CRC Unit */
	SET_BIT(CRC_REG->CR,0);
	/*	Compute CRC Code	*/
	CRC_REG->DR = Copy_u32Word;
	return CRC_REG->DR;
}

u32 MCRC_u32CalculateOnWordArray(u32 *Copy_u32Ptr, u32 Len){
	/*	Reset CRC Unit */
	SET_BIT(CRC_REG->CR,0);
	/*	Compute CRC Code	*/
	for(u32 i = 0; i < Len; i++)
		CRC_REG->DR = Copy_u32Ptr[i];
	return CRC_REG->DR;
}

