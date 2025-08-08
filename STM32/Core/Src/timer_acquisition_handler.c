#include "timer_acquisition_handler.h"
#include "string.h"
#include <stdio.h>
#include "adc_handler.h"
#include "acquisition_handler.h"
uint32_t stopwatch_ms;
#define DEVICE_ADDRESS 0x42

void Stopwatch_Init(void){
	 HAL_TIM_Base_Start_IT(&htim2);
}

void TIM2_Callback() {
	stopwatch_ms++;
}

uint32_t Get_Current_Time(void) {
	uint32_t current_time = stopwatch_ms;
	return current_time;// Retorna o valor atual do cronômetro em milissegundos
}
void Stopwatch_Reset(void){
	stopwatch_ms = 0;
}

uint32_t Measure_Duration(uint32_t start_time) {
    uint32_t duration = Get_Current_Time() - start_time;
    return duration;
}

