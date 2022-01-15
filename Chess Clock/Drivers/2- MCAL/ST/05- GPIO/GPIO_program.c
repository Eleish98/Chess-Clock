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

#include "GPIO_interface.h"
#include "GPIO_private.h"


void MGPIO_voidSetPinDirection	(GPIO_Port_t Copy_Port, GPIO_Pin_t  Copy_Pin, GPIO_Direction_t Copy_Dir){
/*	Writes Selected Direction to pin Configuration	*/
	if (Copy_Port > GPIO_MAX_GPIO_ID)
		return;
	if(Copy_Pin < 8){
		GPIO_REG[Copy_Port]->CRL &= ~(0xF << (Copy_Pin*4));
		GPIO_REG[Copy_Port]->CRL |= Copy_Dir << (Copy_Pin*4);
	}
	else if (Copy_Pin < 16){
		Copy_Pin %= 8;
		GPIO_REG[Copy_Port]->CRH &= ~(0xF << (Copy_Pin*4));
		GPIO_REG[Copy_Port]->CRH |= Copy_Dir << (Copy_Pin*4);
	}
}

void MGPIO_voidSetPortDirection	(GPIO_Port_t Copy_Port, GPIO_Direction_t Copy_Dir){
/*	Writes Selected Direction to Port Configuration fields*/
	if (Copy_Port > GPIO_MAX_GPIO_ID)
			return;
	u32 Local_u32PortValue = 0;
	u8 Local_u8Direction = Copy_Dir;
	for(u8 i= 0; i < 8;i ++)
		Local_u32PortValue = Local_u32PortValue<<4 | Local_u8Direction;
	GPIO_REG[Copy_Port]->CRL = Local_u32PortValue;
	GPIO_REG[Copy_Port]->CRH = Local_u32PortValue;
}

void MGPIO_voidSetPinSpeed		(GPIO_Port_t Copy_Port, GPIO_Pin_t  Copy_Pin, GPIO_Speed_t Copy_Speed){
/*	Clears Speed field then writes new value	*/
	if (Copy_Port > GPIO_MAX_GPIO_ID)
		return;
	if(Copy_Pin < 8){
		GPIO_REG[Copy_Port]->CRL &= ~(0x3 << (Copy_Pin*4 ));
		GPIO_REG[Copy_Port]->CRL |= Copy_Speed << (Copy_Pin*4);
	}
	else if (Copy_Pin < 16){
		Copy_Pin %= 8;
		GPIO_REG[Copy_Port]->CRH &= ~(0x3 << (Copy_Pin*4));
		GPIO_REG[Copy_Port]->CRH |= Copy_Speed << (Copy_Pin*4);
	}
}

void MGPIO_voidSetPortSpeed		(GPIO_Port_t Copy_Port, GPIO_Speed_t Copy_Speed){
/*	Clears Speed field from all port then writes new value	*/
	if (Copy_Port > GPIO_MAX_GPIO_ID)
		return;
	u32 Local_u32PortValue = 0;
	for(u8 i= 0; i < 8;i ++)
		Local_u32PortValue = Local_u32PortValue<<4 | Copy_Speed;
	GPIO_REG[Copy_Port]->CRL &= ~(0x33333333);
	GPIO_REG[Copy_Port]->CRH &= ~(0x33333333);
	
	GPIO_REG[Copy_Port]->CRL |= Local_u32PortValue;
	GPIO_REG[Copy_Port]->CRH |= Local_u32PortValue;
}

/*	Sets Pull Up or Pull Down resistor for an input pin	*/
void MGPIO_voidSetPinPull(GPIO_Port_t Copy_Port, GPIO_Pin_t Copy_Pin, GPIO_Pull_t Copy_Pull){
	GPIO_REG[Copy_Port]->BSRR = (1<<(Copy_Pin+Copy_Pull));
}
/*	Sets Pull Up or Pull Down resistor for an input port	*/
void MGPIO_voidSetPortPull(GPIO_Port_t Copy_Port, GPIO_Pull_t Copy_Pull){
	GPIO_REG[Copy_Port]->BSRR = (0xFFFF<<Copy_Pull);
}


void MGPIO_voidSetPin			(GPIO_Port_t Copy_Port, GPIO_Pin_t Copy_Pin){
/*	Writes 1 to first half of BSRR register setting pin high	*/
	if (Copy_Port > GPIO_MAX_GPIO_ID)
		return;
	GPIO_REG[Copy_Port]->BSRR = (1<<Copy_Pin);
}

void MGPIO_voidSetPort			(GPIO_Port_t Copy_Port){
/*	Writes 0xFFFF to first half BSRR register setting port high	*/
	if (Copy_Port > GPIO_MAX_GPIO_ID)
		return;
	GPIO_REG[Copy_Port]->BSRR = 0xFFFF;
}

void MGPIO_voidClearPin			(GPIO_Port_t Copy_Port, GPIO_Pin_t Copy_Pin){
/*	Writes 1 to in second half of BSRR register setting pin low	*/
	if (Copy_Port > GPIO_MAX_GPIO_ID)
		return;
	GPIO_REG[Copy_Port]->BSRR = (1<<(Copy_Pin+16));
}

void MGPIO_voidClearPort		(GPIO_Port_t Copy_Port){
/*	Writes 0xFFFF to second half of BSRR register setting port low	*/	
	if (Copy_Port > GPIO_MAX_GPIO_ID)
		return;
	GPIO_REG[Copy_Port]->BSRR = 0xFFFF0000;
}

void MGPIO_voidSetPinValue		(GPIO_Port_t Copy_Port, GPIO_Pin_t Copy_Pin, u8 Copy_u8Value){
/*	Writes to first or second half of BSRR according to value	*/
	if (Copy_Port > GPIO_MAX_GPIO_ID)
		return;
	if(Copy_u8Value == 0)
		GPIO_REG[Copy_Port]->BSRR = (1<<(Copy_Pin+16));
	else if(Copy_u8Value == 1)
		GPIO_REG[Copy_Port]->BSRR = (1<<Copy_Pin);
}

void MGPIO_voidSetPortValue		(GPIO_Port_t Copy_Port, u16 Copy_u16Value){
/*	Writes Value to ODR	*/
	if (Copy_Port > GPIO_MAX_GPIO_ID)
		return;
	GPIO_REG[Copy_Port]->ODR = Copy_u16Value;

}

u8 	MGPIO_u8GetPinValue			(GPIO_Port_t Copy_Port, GPIO_Pin_t Copy_Pin){
	if (Copy_Port > GPIO_MAX_GPIO_ID)
		return 0;
	return GET_BIT(GPIO_REG[Copy_Port]->IDR,Copy_Pin);
}

u16 MGPIO_u16GetPortValue		(GPIO_Port_t Copy_Port){
	if (Copy_Port > GPIO_MAX_GPIO_ID)
		return 0;
	return GPIO_REG[Copy_Port]->IDR;
}

void MGPIO_voidLockPin			(GPIO_Port_t Copy_Port, GPIO_Pin_t Copy_Pin){
	if (Copy_Port > GPIO_MAX_GPIO_ID)
		return;
	GPIO_REG[Copy_Port]->LCKR |= (1<<Copy_Pin);
	SET_BIT(GPIO_REG[Copy_Port]->LCKR,16);
	CLR_BIT(GPIO_REG[Copy_Port]->LCKR,16);
	SET_BIT(GPIO_REG[Copy_Port]->LCKR,16);
	GPIO_REG[Copy_Port]->LCKR;
	GPIO_REG[Copy_Port]->LCKR;


}

void MGPIO_voidLockPort			(GPIO_Port_t Copy_Port){
	if (Copy_Port > GPIO_MAX_GPIO_ID)
		return;
	GPIO_REG[Copy_Port]->LCKR |= 0xFFFF;
	SET_BIT(GPIO_REG[Copy_Port]->LCKR,16);
	CLR_BIT(GPIO_REG[Copy_Port]->LCKR,16);
	SET_BIT(GPIO_REG[Copy_Port]->LCKR,16);
	GPIO_REG[Copy_Port]->LCKR;
	GPIO_REG[Copy_Port]->LCKR;
}

