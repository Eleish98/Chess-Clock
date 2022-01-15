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

#include "SCB_interface.h"
#include "SCB_private.h"

void MSCB_voidSetInterruptGroups(SCB_Interrupt_Group_t GroupConfig){
	/*	Read Least 3 bits of AIRCR Register	*/
	u32 Local_u32RegValue = (SCB_REG->AIRCR) & 7;
	/*	Add Write Key and Priority Cofiguration */
	Local_u32RegValue |= SCB_AIRCR_WRITE_KEY | (GroupConfig<<8);
	/*	Write New Value to AIRCR Register*/
	SCB_REG->AIRCR = Local_u32RegValue;
}

void MSCB_voidRequestSystemReset(void){
	/*	Read Least Half Word of AIRCR Register	*/
	u32 Local_u32RegValue = (SCB_REG->AIRCR) & 0xFFFF;
	/*	Add Write Key and Set SYSRESETREQ Bit	*/
	Local_u32RegValue |= SCB_AIRCR_WRITE_KEY | (1<<2);
	/*	Write New Value to AIRCR Register	*/
	SCB_REG->AIRCR = Local_u32RegValue;
}

void MSCB_voidSetExceptionPriority(SCB_Exception_t Exception, u8 Priority){
	if(Exception < SCB_EXCEPTION_SV_CALL){
		/*	Clear Priority Field according to Exception value and Set it the new Value	*/
		SCB_REG->SHPR1 &= ~(0xf << (Exception*8 + 4));
		SCB_REG->SHPR1 |= ((Priority & 0xf) << (Exception*8 + 4));
	}	
	else if(Exception < SCB_EXCEPTION_PEND_SV){
		/*	Clear Priority Field and Set it the new Value	*/
		SCB_REG->SHPR2 &= ~(0xf << 28);
		SCB_REG->SHPR2 |= ((Priority & 0xf) << 28);
	}
	else if(Exception <= SCB_EXCEPTION_SYSTICK){
		/*	Clear Priority Field according to Exception value and Set it the new Value	*/
		SCB_REG->SHPR2 &= ~(0xf << (Exception*8 - 12));
		SCB_REG->SHPR2 |= ((Priority & 0xf) << (Exception*8 - 12));
	}
}




void MSCB_voidEnableException(SCB_Exception_t Exception){
	/*	Sets Exception Enable Bit According to Exception Value	*/
	switch(Exception){
		case SCB_EXCEPTION_USAGE_FAULT:
			SET_BIT(SCB_REG->SHCSR,18);
			break;
		case SCB_EXCEPTION_MEMORY_MANAGE_FAULT:
			SET_BIT(SCB_REG->SHCSR,16);
			break;
		case SCB_EXCEPTION_BUS_FAULT:
			SET_BIT(SCB_REG->SHCSR,17);
			break;
		default:
			break;
	}
}

void MSCB_voidDisableException(SCB_Exception_t Exception){
	/*	Clears Exception Enable Bit According to Exception Value	*/
	switch(Exception){
		case SCB_EXCEPTION_USAGE_FAULT:
			CLR_BIT(SCB_REG->SHCSR,18);
			break;
		case SCB_EXCEPTION_MEMORY_MANAGE_FAULT:
			CLR_BIT(SCB_REG->SHCSR,16);
			break;
		case SCB_EXCEPTION_BUS_FAULT:
			CLR_BIT(SCB_REG->SHCSR,17);
			break;
		default:
			break;
	}	
}

void MSCB_voidSetExceptionPending(SCB_Exception_t Exception){
	/*	Sets Exception Pending Bit According to Exception Value	*/
	switch(Exception){
		case SCB_EXCEPTION_USAGE_FAULT:
			SET_BIT(SCB_REG->SHCSR,12);
			break;
		case SCB_EXCEPTION_MEMORY_MANAGE_FAULT:
			SET_BIT(SCB_REG->SHCSR,13);
			break;
		case SCB_EXCEPTION_BUS_FAULT:
			SET_BIT(SCB_REG->SHCSR,14);
			break;
		case SCB_EXCEPTION_SV_CALL:
			SET_BIT(SCB_REG->SHCSR,15);
			break;
		case SCB_EXCEPTION_PEND_SV:
			SCB_REG->ICSR = (1<<28);
			break;
		case SCB_EXCEPTION_SYSTICK:
			SCB_REG->ICSR = (1<<26);
		default:
			break;
	}
}

void MSCB_voidClearExceptionPending(SCB_Exception_t Exception){
	/*	Clears Exception Pending Bit According to Exception Value	*/
	switch(Exception){
		case SCB_EXCEPTION_USAGE_FAULT:
			CLR_BIT(SCB_REG->SHCSR,12);
			break;
		case SCB_EXCEPTION_MEMORY_MANAGE_FAULT:
			CLR_BIT(SCB_REG->SHCSR,13);
			break;
		case SCB_EXCEPTION_BUS_FAULT:
			CLR_BIT(SCB_REG->SHCSR,14);
			break;
		case SCB_EXCEPTION_SV_CALL:
			CLR_BIT(SCB_REG->SHCSR,15);
			break;
		case SCB_EXCEPTION_PEND_SV:
			SCB_REG->ICSR = (1<<27);
			break;
		case SCB_EXCEPTION_SYSTICK:
			SCB_REG->ICSR = (1<<25);
		default:
			break;
	}
}

u8 MSCB_u8GetExceptionStatus(SCB_Exception_t Exception){
/*	
*	Returns the Status of The Exception
*	0			:	Exception not Active
*	otherwise	:	Exception Active
*
*/
	u8 Local_u8State = 0;
	if (Exception < SCB_EXCEPTION_USAGE_FAULT)
		Local_u8State = GET_BIT(SCB_REG->SHCSR,Exception);
	else if(Exception == SCB_EXCEPTION_USAGE_FAULT)
		Local_u8State = GET_BIT(SCB_REG->SHCSR,3);
	else if(Exception == SCB_EXCEPTION_SV_CALL)
		Local_u8State = GET_BIT(SCB_REG->SHCSR,7);
	else if(Exception <= SCB_EXCEPTION_SYSTICK)
		Local_u8State = GET_BIT(SCB_REG->SHCSR,(Exception+6));
	return Local_u8State;
}


void MSCB_voidEnableSleepNow(void){
	/*	Clears SLEEPONEXIT Bit	*/
	CLR_BIT(SCB_REG->SCR,1);
}


void MSCB_voidDisableSleepNow(void){
	/*	Sets SLEEPONEXIT Bit	*/
	SET_BIT(SCB_REG->SCR,1);
}


void MSCB_voidEnableDeepSleep(void){
	/*	Sets DEEPSLEEP Bit	*/
	SET_BIT(SCB_REG->SCR,2);
}

void MSCB_voidDisableDeepSleep(void){
	/*	Clears DEEPSLEEP Bit	*/
	CLR_BIT(SCB_REG->SCR,2);
}

void MSCB_voidSetEventOnPendingInterrupt(SCB_Event_Mode_t Copy_EventMode){
	/*	Clears SEVONPEND Bit	*/
	CLR_BIT(SCB_REG->SCR,4);
	/*	Writes SEVONPEND with new value	*/
	SCB_REG->SCR |= ((Copy_EventMode&1) << 4);
}
