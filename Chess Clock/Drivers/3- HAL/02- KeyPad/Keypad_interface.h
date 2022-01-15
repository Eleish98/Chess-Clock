#ifndef KEYPAD_INTERFACE_H
#define KEYPAD_INTERFACE_H


typedef struct{
	u8 Rows;
	u8 Columns;
	GPIO_Pin_t* RowPins;
	GPIO_Port_t * RowPorts;
	GPIO_Pin_t* ColumnPins;
	GPIO_Port_t * ColumnPorts;
	u8* Map;
	u32 Blocking;
}Keypad_t;


void HKeypad_voidInit(Keypad_t* K);

u8 HKeypad_u8GetKey(Keypad_t* K);


#endif

