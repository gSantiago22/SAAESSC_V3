#ifndef TIMER_ACQUISITION_HANDLER_H
#define TIMER_ACQUISITION_HANDLER_H

#include "main.h"
#include "stm32f1xx_hal.h"

extern uint32_t stopwatch_ms;

void Stopwatch_Init(void);
uint32_t Get_Current_Time(void);
uint32_t Measure_Duration(uint32_t start_time);
void Stopwatch_Reset(void);
void TIM2_Callback();

#endif
