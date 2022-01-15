/*
 * ADVANCED_TIMERS_private.h
 *
 *  Created on: Oct 14, 2021
 *      Author: MohammedGamalEleish
 */

#ifndef ADVANCED_TIMERS_PRIVATE_H_
#define ADVANCED_TIMERS_PRIVATE_H_

#define ADV_TIM1_BASE_ADDRESS		0x40012C00
#define ADV_TIM8_BASE_ADDRESS		0x40013400


typedef struct{
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 SMCR;
	volatile u32 DIER;
	volatile u32 SR;
	volatile u32 EGR;
	volatile u32 CCMR1;
	volatile u32 CCMR2;
	volatile u32 CCER;
	volatile u32 CNT;
	volatile u32 PSC;
	volatile u32 ARR;
	volatile u32 RCR;
	volatile u32 CCR[4];
	volatile u32 BDTR;
	volatile u32 DCR;
	volatile u32 DMAR;

}REG_ADV_TIMER_t;


#endif
