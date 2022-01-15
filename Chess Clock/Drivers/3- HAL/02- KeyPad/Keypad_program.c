#include "1- LIB/STD_TYPES.h"
#include "1- LIB/BIT_MATH.h"

#include "2- MCAL/ST/05- GPIO/GPIO_interface.h"

#include "Keypad_interface.h"
#include "Keypad_private.h"



void HKeypad_voidInit(Keypad_t* K){
	
	//Make all Row pins as input with pullup
	for(u8 i = 0; i < K->Rows; i++){
		MGPIO_voidSetPinDirection(K->RowPorts[i],K->RowPins[i],GPIO_DIR_INPUT_PULL_UP_DOWN);
		MGPIO_voidSetPinPull(K->RowPorts[i],K->RowPins[i],GPIO_PULL_UP);
	}
	
	//Make all Colomn Pins as Output and set to HIGH to disable them;
	for(u8 i = 0; i < K->Columns; i++){
		MGPIO_voidSetPinDirection(K->ColumnPorts[i],K->ColumnPins[i],GPIO_DIR_OUTPUT_PUSH_PULL);
		MGPIO_voidSetPinSpeed(K->RowPorts[i],K->RowPins[i],GPIO_SPEED_50_MHZ);
	}
	//Disable All Columns (AKA set all columns to high)
	PKeypad_voidDisableColumns(K);
	
}

u8 HKeypad_u8GetKey(Keypad_t* K){
	//Variable to hold the pressed key value
	u8 Local_u8PressedKey = 0;
	//variables to hold timeout, or 1 in case of blocking == 0
	u32 Local_u32Timeout = K->Blocking == 0?	1:K->Blocking;
	
	while(Local_u32Timeout){
		for(u8 i = 0; i < K->Columns; i++){
			//loop on all columns, enable just one column
			PKeypad_voidEnableColumn(K,i);
			//read all the rows (here, the keypad can only handle 8 rows as we use an u8 variable to hold the value)
			u8 RowsValue = PKeypad_u8ReadRows(K);
			//find the first instance of the 0 bit
			u8 ZeroIndex = PKeypad_u8GetZeroIndex(RowsValue,K->Rows);
			if(ZeroIndex != 255){
				//ZeroIndex == 255 means that no key is pressed, so if ZeroIndex != 255 that means a key has been pressed
				//Read the Pressed key
				Local_u8PressedKey = *((K->Map)+ZeroIndex*(K->Columns)+i);	
				break;
			}
		}
		//After looping on all columns, if the pressed key variable holds a key, break from the outer loop
		if (Local_u8PressedKey != 0)
			break;
		//if Blocking == 0 that means that the function is blocking, if not it is not blocking which
		//means we decrement the Timeout variable
		if(K->Blocking != 0)
			Local_u32Timeout--;
		
	}
	
	
	return Local_u8PressedKey;
}

u8 PKeypad_u8GetZeroIndex(u8 Value, u8 Max){
	//This Function finds the index of the 0 bit index in an 8-bit number starting from Least Significant Bit (LSB)
	//if no zero is found, it returns 255
	u8 Local_u8Index = 255;
	for(u8 i = 0; i < Max ; i++)
		Local_u8Index = GET_BIT(Value,i) == 0? i:Local_u8Index;
	return Local_u8Index;
}


u8 PKeypad_u8ReadRows(Keypad_t* K){
	
	//This function reads the Rows values and codes the values into one 8-bit number
	//meaning that it returns a number like 
	/********************************************************************************************************/
	/*		bit7	|	bit6	 |	 bit5	 |	bit4	 |	 bit3	 |	bit2	 |	 bit1	 |	 bit0	 |	*/
	/*	  R7value   |  R6value   |  R5value  |  R4value  |  R3value  |  R2value  |  R1value  |  R0value  |	*/
	/*																										*/
	/********************************************************************************************************/
	
	volatile u8 Local_u8Value = 0;
	
	for(u8 i = 0; i < K->Rows; i++){
		u8 RowValue = (MGPIO_u8GetPinValue(K->RowPorts[i],K->RowPins[i]) << i);
		Local_u8Value = Local_u8Value | RowValue;
	}
	return Local_u8Value;
}


void PKeypad_voidEnableColumn(Keypad_t* K, u8 Colomn){
	//This function enables just one column (Sets it to low)
	PKeypad_voidDisableColumns(K);
	MGPIO_voidClearPin(K->RowPorts[Colomn],K->RowPins[Colomn]);
	//MGPIO_voidSetPinValue(K->ColumnPorts[Colomn],K->ColumnPins[Colomn],GPIO_LOW);
	
}

void PKeypad_voidDisableColumns(Keypad_t* K){
	//This function disables all columns (Sets them to high)
	for(u8 i = 0;i < K->Columns; i++)
		MGPIO_voidSetPin(K->RowPorts[i],K->RowPins[i]);
		//MGPIO_voidSetPinValue(K->ColumnPorts[i],K->ColumnPins[i],GPIO_HIGH);

}


