#ifndef ADC_HANDLER_H
#define ADC_HANDLER_H

#include "main.h"

// Tamanho do buffer do ADC (ajustar conforme o número de canais e requisitos)
#define ADC_BUFFER_SIZE 3

// Declaração do buffer global para armazenar as leituras do ADC
extern uint16_t adcBuffer[ADC_BUFFER_SIZE];
extern float voltage, current;
/**
 * @brief Inicialização do ADC e suas dependências (DMA e Timer).
 *
 * Deve ser chamado após a inicialização do hardware pelos arquivos MX_*.
 */

/**
 * @brief Inicia a conversão do ADC utilizando DMA e Timer.
 *
 * Esta função é usada para começar o processo de leitura do ADC
 * de forma contínua em modo circular.
 */
void ADS8661_Select(int adc);
void ADS8661_Deselect(int adc);
void ADS8661_WriteRegister(uint8_t reg, uint16_t value);
uint16_t ADS8661_Read(void);
float getVoltage();
float getCurrent();
void ADC_Start(void);
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc);
void TIM3_Callback();
void Control_AcquisitionRate(float freq);
#endif /* ADC_HANDLER_H */
