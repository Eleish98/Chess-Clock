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
#ifndef SCB_INTERFACE_H_INCLUEDED
#define SCB_INTERFACE_H_INCLUEDED

/* This enum is used with:
*	
* 1- void MSCB_voidSetInterruptGroups 
* 
*/
typedef enum{
	/*16 Groups, 1 Interrupt per group*/
	SCB_INTERRUPT_16_GROUP_1_SUB = 3,
	/*8 Groups, 2 Interrupts per group*/
	SCB_INTERRUPT_8_GROUP_2_SUB,
	/*4 Groups, 4 Interrupts per group*/
	SCB_INTERRUPT_4_GROUP_4_SUB,
	/*2 Groups, 8 Interrupts per group*/
	SCB_INTERRUPT_2_GROUP_8_SUB,
	/*1 Group, 16 Interrupts per group*/
	SCB_INTERRUPT_1_GROUP_16_SUB
}SCB_Interrupt_Group_t;

/*This enum is used with:
*
* 1- void MSCB_voidSetExceptionPriority
* 2- void MSCB_voidEnableException 
* 3- void MSCB_voidDisableException
* 4- void MSCB_voidSetExceptionPending
* 5- void MSCB_voidClearExceptionPending
* 6- u8 MSCB_u8GetExceptionStatus
*
*/
typedef enum{
	/*Memory Managment Fault Exception ID*/
	SCB_EXCEPTION_MEMORY_MANAGE_FAULT,
	/*Bus Fault Exception ID*/
	SCB_EXCEPTION_BUS_FAULT,
	/*Usage Fault Exception ID*/
	SCB_EXCEPTION_USAGE_FAULT,
	/*SV Call Exception ID*/
	SCB_EXCEPTION_SV_CALL,
	/*Pending SV Exception ID*/
	SCB_EXCEPTION_PEND_SV,
	/*Systick Exception ID*/
	SCB_EXCEPTION_SYSTICK
}SCB_Exception_t;

/*This enum is used with:
*
* 1- void MSCB_voidSetEventOnPendingInterrupt
*
*/
typedef enum{
	/*Interrupts Enabled and Acknowledged By NVIC*/
	SCB_EVENT_ENABLED_INTERRUPTS,
	/*Interrupts Enabled only by thier Peripherals*/
	SCB_EVENT_DISABLED_INTERRUPTS
}SCB_Event_Mode_t;

/*  Sets The Interrupt Priority Configuration 	*/
void MSCB_voidSetInterruptGroups(SCB_Interrupt_Group_t GroupConfig);

/*	Set Priority for Priority-Settable Exceptions	*/
void MSCB_voidSetExceptionPriority(SCB_Exception_t Exception, u8 Priority);
/*	Enables Exception Handler	*/
void MSCB_voidEnableException(SCB_Exception_t Exception);
/*	Disables Exception Handler	*/
void MSCB_voidDisableException(SCB_Exception_t Exception);
/*	Sets The Pending Bit for Exception Allowing for SW trigger for the Exception	*/
void MSCB_voidSetExceptionPending(SCB_Exception_t Exception);
/*	Clears Pending Bit for Exception	*/
void MSCB_voidClearExceptionPending(SCB_Exception_t Exception);
/*	Returns Exception Pending Bit Status	*/
u8 MSCB_u8GetExceptionStatus(SCB_Exception_t Exception);
/*	Perform A system Reset	*/
void MSCB_voidRequestSystemReset(void);
/*	Enables Immediate Sleep when using Any Sleep Mode	*/
void MSCB_voidEnableSleepNow(void);
/*	Disables Immediate Sleep when using Any Sleep Mode	*/
/*	
*	The Selected Sleep Mode is Enterred after
*	returning from The Lowest Priority ISR
*/
void MSCB_voidDisableSleepNow(void);
/*	Disables Deep Sleep Mode	*/
void MSCB_voidDisableDeepSleep(void);
/*	Enables Deep Sleep Mode (Allowing StandBy and Stop Modes)	*/
void MSCB_voidEnableDeepSleep(void);
/*	Sets Mode for WakeUp Event	*/
void MSCB_voidSetEventOnPendingInterrupt(SCB_Event_Mode_t Copy_EventMode);

#endif

