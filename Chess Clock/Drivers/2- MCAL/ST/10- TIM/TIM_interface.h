/*
 * ADVANCED_TIMERS_inerface.h
 *
 *  Created on: Oct 14, 2021
 *      Author: MohammedGamalEleish
 */

#ifndef TIM_INTERFACE_H_
#define TIM_INTERFACE_H_

typedef enum{
	TIM1,
	TIM2,
	TIM3,
	TIM4,
	TIM5
}TIM_ID_t;

typedef enum{

	TIM_CLOCK_MODE_INTERNAL_CLK,
	TIM_CLOCK_MODE_EXTERNAL_MODE1,
	TIM_CLOCK_MODE_EXTERNAL_MODE2,
	TIM_CLOCK_MODE_ENCODER

}TIM_ClockMode_t;

typedef enum{
	TIM_DIRECTION_COUNT_UP,
	TIM_DIRECTION_COUNT_DOWN,
	TIM_DIRECTION_COUNT_UP_DOWN
}TIM_Direction_t;

typedef enum{

	TIM_AUTORELOAD_UPDATE_IMMEDIATE,
	TIM_AUTORELOAD_UPDATE_ON_NEXT_CYCLE
}TIM_AutoReloadUpdate_t;

typedef enum{

	TIM_EXTERNAL_MODE1_INTERNAL_TRIGGER0,
	TIM_EXTERNAL_MODE1_INTERNAL_TRIGGER1,
	TIM_EXTERNAL_MODE1_INTERNAL_TRIGGER2,
	TIM_EXTERNAL_MODE1_INTERNAL_TRIGGER3,
	TIM_EXTERNAL_MODE1_T1_EDGE_DETECTOR,
	TIM_EXTERNAL_MODE1_T1_FILTERED_INPUT,
	TIM_EXTERNAL_MODE1_T2_FILTERED_INPUT,
	TIM_EXTERNAL_MODE1_EXTERNAL_TRIGGER
}TIM_ExternalMode1_t;

typedef enum{

	TIM_EDGE_POLARITY_RISING,
	TIM_EDGE_POLARITY_FALLING
}TIM_EdgePolarity_t;

void MTIM_voidInit(TIM_ID_t Tim, TIM_Direction_t Direction, TIM_ClockMode_t ClockMode, u16 Prescalar, u16 AutoReloadValue, u16 RepetitionCounter, TIM_AutoReloadUpdate_t AutoReloadMode);

void MTIM_voidConfigureExternalMode1(TIM_ID_t Tim, TIM_ExternalMode1_t ExternalMode1);

void MTIM_voidStartTimer(TIM_ID_t Tim);

void MTIM_voidStopTimer(TIM_ID_t Tim);

void MTIM_voidStartTimeMeasure(TIM_ID_t Tim);

u16 MTIM_u16GetElapsedTicks(TIM_ID_t Tim);

void MTIM_voidSetBysyWait(TIM_ID_t Tim, u32 Ticks);


//void MTIM_voidConfigureEncoderMode(TIM_ID_t Tim);


#endif

