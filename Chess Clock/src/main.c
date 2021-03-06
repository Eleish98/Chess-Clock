#include "1- LIB/STD_TYPES.h"
#include "1- LIB/BIT_MATH.h"


#include "2- MCAL/ARM _CORTEX_M3/03- STK/STK_interface.h"
#include "2- MCAL/ARM _CORTEX_M3/01- NVIC/NVIC_interface.h"

#include "2- MCAL/ST/04- RCC/RCC_interface.h"
#include "2- MCAL/ST/05- GPIO/GPIO_interface.h"
#include "2- MCAL/ST/06- AFIO/AFIO_interface.h"
#include "2- MCAL/ST/07- EXTI/EXTI_interface.h"


#include "3- HAL/03- Char LCD/LCD_interface.h"
#include "3- HAL/04- Rotary Encoder/Encoder_interface.h"

#include "ChessClock_interface.h"

#include "ChessClock_HWConfig.h"

#include "2- MCAL/ST/10- TIM/TIM_interface.h"

#include "1- LIB/Delay.h"

void EncoderMoved(EncoderChange_t Move){
	if(Move == ENCODER_CHANGE_CLOCKWISE)
		asm("NOP");
	else if (Move == ENCODER_CHANGE_COUNTER_CLOCKWISE)
		asm("NOP");
}

volatile u32 test = 0;

void Delay(u32 A){
	while(A--){
		asm("NOP");
	}
}

int main(void){


	MRCC_voidInitClock();

	ChessClock_voidInit();

	ChessClock_voidRun();

	while(1){
		asm("NOP");
	}
	return 0;
}
