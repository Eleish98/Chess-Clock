/*
 * ADVANCED_TIMERS_private.h
 *
 *  Created on: Oct 14, 2021
 *      Author: MohammedGamalEleish
 */

#ifndef TIM_PRIVATE_H_
#define TIM_PRIVATE_H_

#define GNRL_TIM_MAX_COUNT				4
#define ADV_TIM_MAX_COUNT				1

#define TIM_MAX_COUNT					GNRL_TIM_MAX_COUNT+ADV_TIM_MAX_COUNT

#define GNRL_TIM2_BASE_ADDRESS			0x40000000
#define GNRL_TIM3_BASE_ADDRESS			0x40000400
#define GNRL_TIM4_BASE_ADDRESS			0x40000800
#define GNRL_TIM5_BASE_ADDRESS			0x40000C00

#define ADV_TIM1_BASE_ADDRESS			0x40012C00
#define ADV_TIM8_BASE_ADDRESS			0x40013400


typedef struct{

	volatile u32 CR[2];
	volatile u32 SMCR;
	volatile u32 DIER;
	volatile u32 SR;
	volatile u32 EGR;
	volatile u32 CCMR[2];
	volatile u32 CCER;
	volatile u32 CNT;
	volatile u32 PSC;
	volatile u32 ARR;
	volatile u32 CCR[4];
	volatile u32 DCR;
	volatile u32 DMAR;

}REG_GNRL_TIM_t;


typedef struct{
	volatile u32 CR[2];
	volatile u32 SMCR;
	volatile u32 DIER;
	volatile u32 SR;
	volatile u32 EGR;
	volatile u32 CCMR[2];
	volatile u32 CCER;
	volatile u32 CNT;
	volatile u32 PSC;
	volatile u32 ARR;
	volatile u32 RCR;
	volatile u32 CCR[4];
	volatile u32 BDTR;
	volatile u32 DCR;
	volatile u32 DMAR;

}REG_ADV_TIM_t;


#define TIM1_REG				((volatile REG_ADV_TIM_t *)(ADV_TIM1_BASE_ADDRESS))
#define TIM8_REG				((volatile REG_ADV_TIM_t *)(ADV_TIM8_BASE_ADDRESS))

#define TIM2_REG				((volatile REG_GNRL_TIM_t *)(GNRL_TIM2_BASE_ADDRESS))
#define TIM3_REG				((volatile REG_GNRL_TIM_t *)(GNRL_TIM3_BASE_ADDRESS))
#define TIM4_REG				((volatile REG_GNRL_TIM_t *)(GNRL_TIM4_BASE_ADDRESS))
#define TIM5_REG				((volatile REG_GNRL_TIM_t *)(GNRL_TIM5_BASE_ADDRESS))

volatile REG_GNRL_TIM_t *GNR_TIM_REGs[GNRL_TIM_MAX_COUNT] = {TIM2_REG, TIM3_REG, TIM4_REG, TIM5_REG};
volatile REG_ADV_TIM_t *ADV_TIM_REGs[ADV_TIM_MAX_COUNT] = {TIM1_REG};



/*		General Purpose Timer Function Declarations		*/
static void GNRL_TIM_voidInit(TIM_ID_t TIM, TIM_Direction_t Direction, TIM_ClockMode_t ClockMode, u16 Prescalar, u16 AutoReloadValue, TIM_AutoReloadUpdate_t AutoReloadMode);

static void GNRL_TIM_voidConfigureExternalMode1(TIM_ID_t Tim, TIM_ExternalMode1_t ExternalMode1);

static void GNRL_TIM_voidStartTimer(TIM_ID_t Tim);

static void GNRL_TIM_voidStopTimer(TIM_ID_t Tim);

static void GNRL_TIM_voidStartTimeMeasure(TIM_ID_t Tim);

static u16 GNRL_TIM_u16GetElapsedTicks(TIM_ID_t Tim);

static void GNRL_TIM_voidSetBysyWait(TIM_ID_t TIM, u32 Ticks);

//=========================================================================================================================================================

/*		Advanced Control Timer Function Declarations		*/
static void ADV_TIM_voidInit(TIM_ID_t TIM, TIM_Direction_t Direction, TIM_ClockMode_t ClockMode, u16 Prescalar, u16 AutoReloadValue, u16 RepetitionCounter, TIM_AutoReloadUpdate_t AutoReloadMode);

static void ADV_TIM_voidConfigureExternalMode1(TIM_ID_t Tim, TIM_ExternalMode1_t ExternalMode1);

static void ADV_TIM_voidStartTimer(TIM_ID_t Tim);

static void ADV_TIM_voidStopTimer(TIM_ID_t Tim);

static void ADV_TIM_voidStartTimeMeasure(TIM_ID_t Tim);

static u16 ADV_TIM_u16GetElapsedTicks(TIM_ID_t Tim);

static void ADV_TIM_voidSetBysyWait(TIM_ID_t TIM, u32 Ticks);

#endif
