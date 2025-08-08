#include "dac_handler.h"

volatile uint32_t periods = 0;

// Inicia o DAC com DMA
void DAC_Start_DMA(uint32_t channel, uint32_t *data, uint32_t length) {
    if (HAL_DAC_Start_DMA(&hdac, channel, data, length, DAC_ALIGN_12B_R) != HAL_OK) {
        Error_Handler();
    }
    if (HAL_TIM_Base_Start(&htim6) != HAL_OK) {
               Error_Handler();
    }
}

// Para o DAC com DMA
void DAC_Stop_DMA(uint32_t channel) {
    if (HAL_DAC_Stop_DMA(&hdac, channel) != HAL_OK) {
        Error_Handler();
    }
}

void DAC_Frequency_Control(uint32_t channel, float frequency, uint32_t SMP){
	uint32_t psc;
	if (frequency<0.1){
		psc = 7199;
	}else if(frequency>1000){
		psc = 0;
	}else{
		psc = 71;
	}
	uint32_t ARR = (uint32_t)(72000000/((psc+1) * SMP * frequency))-1;

	if (channel == DAC_CHANNEL_1){
		HAL_TIM_Base_Stop_IT(&htim6);
		__HAL_TIM_SET_PRESCALER(&htim6, psc);
		__HAL_TIM_SET_AUTORELOAD(&htim6, ARR);
		HAL_TIM_Base_Start_IT(&htim6);
	}
}

void HAL_DAC_ConvCpltCallbackCh1(DAC_HandleTypeDef* hdac)
{
	if (hdac->Instance == DAC1) {
	        periods++;
	    }
}

uint32_t Get_Periods(){
	return periods;
}
void Reset_Periods(){
	periods = 0;
}
