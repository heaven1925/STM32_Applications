/*
 * timers.c
 *
 *  Created on: 11 Kas 2014
 *      Author: Tanju Tascilar
 *  Copyright : tanju@elektronist.com
 *  License   : GPLv3
 */

#include "timers.h"

#define WEAK __attribute__ ((weak))

WEAK void TIMERS_Task(void);
WEAK void TIMERS_Task_1(void);
WEAK void TIMERS_Task_2(void);
WEAK void TIMERS_Task_4(void);
WEAK void TIMERS_Task_5(void);
WEAK void TIMERS_Task_6(void);
WEAK void TIMERS_Task_7(void);


/* Proto function must be overridden */
void TIMERS_Task(void)
{
	return;
}

void TIMERS_Task_1(void)
{
	return;
}

void TIMERS_Task_2(void)
{
	return;
}

void TIMERS_Task_4(void)
{
	return;
}

void TIMERS_Task_5(void)
{
	return;
}

void TIMERS_Task_6(void)
{
	return;
}

void TIMERS_Task_7(void)
{
	return;
}

volatile uint32_t mSec_Counter = 0;
TIMER_TIMER TIMER_Timer;

/* SysTick Interrupt Handler
 * SysTick interrupt happens on every 1 ms
 */
void SysTick_Handler(void)
{
	mSec_Counter++;
	TIMERS_Task();										// DMD
	TIMERS_Task_1();									// WI
	TIMERS_Task_2();									// GPS
	TIMERS_Task_4();									// SDCard
	TIMERS_Task_5();									// ETH
	TIMERS_Task_6();									// Petit MODBUS
	TIMERS_Task_7();									// MODBUS with Master
}

/* SysTick Timer Initializer
 * SYSTICK_DELAY defined in timers.h to interrupt on every 1 ms
 */
void Timers_Init(void){
	SystemCoreClockUpdate();
	SysTick_Config( SYSTICK_DELAY );
}

void TIMER_Start(TIMER_TIMER *Timer, uint32_t Value)
{
	Timer->Value = Value;
	Timer->Base = mSec_Counter;
}

void TIMER_Reset(TIMER_TIMER *Timer)
{
	Timer->Value = 0;
	Timer->Base = 0;
}

uint8_t TIMER_Over(TIMER_TIMER *Timer)
{
	if (Timer->Value > 0){
		while (Timer->Base != mSec_Counter){
			Timer->Value--;
			if (Timer->Value == 0) return TRUE;
			Timer->Base++;
		}
		return FALSE;
	} else{
		return TRUE;
	}
}

/*	delayMs */
void delayMs(uint32_t delayInMs)
{
	TIMER_Reset(&TIMER_Timer);
	TIMER_Start(&TIMER_Timer, delayInMs);
	while (!TIMER_Over(&TIMER_Timer));

	return;
}

/* End of File */
