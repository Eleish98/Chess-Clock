#include "STD_TYPES.h"
#include "Delay.h"

u32 DELAY_PER_MILLESECOND;

u32 Val = 10000;

void LDelay_voidInit(u32 AHBClock){
	DELAY_PER_MILLESECOND = AHBClock / 10000;
}

void LDelay_voidSetBusyWait(u32 MilleSeconds){
	u32 DelayCycles = MilleSeconds* DELAY_PER_MILLESECOND;
	while(DelayCycles--){
		asm("NOP");
	}
}
