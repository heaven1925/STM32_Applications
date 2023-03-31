/*
 * timers.h
 *
 *  Created on: 11 Kas 2014
 *      Author: Tanju Tascilar
 *  Copyright : tanju@elektronist.com
 *  License   : GPLv3
 */

#ifndef TIMERS_H_
#define TIMERS_H_

#include "chip.h"
#include "misc.h"
#include "stopwatch.h"

#define SYSTICK_DELAY		(SystemCoreClock/1000)		/* for 1 mSec */
#define US_TIME    			(SystemCoreClock/100000)   	/* 10 uS */

typedef struct TIMER_TIMER {
	uint32_t Value;										// Reload value
	uint32_t Base;										// Base counter to compare
} TIMER_TIMER;
extern volatile uint32_t mSec_Counter;

void Timers_Init(void);

void TIMER_Start(TIMER_TIMER *Timer, uint32_t Value);
uint8_t TIMER_Over(TIMER_TIMER *Timer);
void TIMER_Reset(TIMER_TIMER *Timer);
void SysTickOfFreeRTOS(void);

void delayMs(uint32_t delayInMs);


#endif /* TIMERS_H_ */
