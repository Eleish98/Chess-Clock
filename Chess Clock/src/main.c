#include "1- LIB/STD_TYPES.h"
#include "1- LIB/BIT_MATH.h"


#include "2- MCAL/ARM _CORTEX_M3/03- STK/STK_interface.h"
#include "2- MCAL/ARM _CORTEX_M3/01- NVIC/NVIC_interface.h"

#include "2- MCAL/ST/04- RCC/RCC_interface.h"
#include "2- MCAL/ST/05- GPIO/GPIO_interface.h"



#include "3- HAL/03- Char LCD/LCD_interface.h"
#include "3- HAL/04- Rotary Encoder/Encoder_interface.h"


void EncoderMoved(EncoderChange_t Move){
	if(Move == ENCODER_CHANGE_CLOCKWISE)
		asm("NOP");
	else if (Move == ENCODER_CHANGE_COUNTER_CLOCKWISE)
		asm("NOP");
}

int main(void){

	MRCC_voidInitClock();
	MRCC_voidEnablePeripheral(RCC_PER_GPIOA);
	MRCC_voidEnablePeripheral(RCC_PER_GPIOB);
	MRCC_voidEnablePeripheral(RCC_PER_AFIO);

	MNVIC_voidInit(NVIC_CONFIG_1_GROUP_16_SUB);

	MSTK_voidInit(STK_CLOCK_AHB,MRCC_u32GetBusClock(RCC_BUS_AHB));

	GPIO_Port_t LCD_DataPorts[4] = {GPIO_PORTA,GPIO_PORTA,GPIO_PORTA,GPIO_PORTA};
	GPIO_Pin_t LCD_DataPins[4] = {GPIO_PIN_3, GPIO_PIN_4,GPIO_PIN_5,GPIO_PIN_6};


	LCD_t LCD = {LCD_MODE_4_BIT,{4,20},{GPIO_PIN_0, GPIO_PIN_1,GPIO_PIN_2},{GPIO_PORTA,GPIO_PORTA,GPIO_PORTA},LCD_DataPins,LCD_DataPorts};

	HLCD_voidInit(&LCD);

	HLCD_voidWriteString(&LCD, "Hello From STM32!");

	HENCODER_voidInit();
	HENCODER_voidSetChangeCallBack(EncoderMoved);
	HENCODER_voidEnableEncoder();
	while(1){



	}
	return 0;
}
