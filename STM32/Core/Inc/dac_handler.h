#ifndef DAC_HANDLER_H
#define DAC_HANDLER_H

#include "main.h"
#include "stm32f1xx_hal.h"



// Prototipagem das funções
void DAC_Start_DMA(uint32_t channel, uint32_t *data, uint32_t length);
void DAC_Stop_DMA(uint32_t channel);
void DAC_Frequency_Control(uint32_t channel, float frequency, uint32_t SMP);
void DMA2_Channel3_IRQHandler(void);
uint32_t Get_Periods();
void Reset_Periods();
void HAL_DAC_ConvCpltCallbackCh1(DAC_HandleTypeDef* hdac);

#endif // DAC_HANDLER_H
