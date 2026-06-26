// adc_handler.c
#include "adc_handler.h"
#include "acquisition_handler.h"
#include "timer_acquisition_handler.h"
#include "string.h"
#include "stdio.h"

// Definições atualizadas conforme datasheet
#define WRITE_REG_CMD(addr) (0xD8 | (((addr) >> 8) & 0x03))  // Comando WRITE (11010_00)
#define REG_INPUT_RANGE     0x14  // Endereço do RANGE_SEL_REG
#define RANGE_0_5V12        0x0B  // 1011b para faixa 0-5.12V (conforme tabela 7-16)
#define INTREF_ENABLED      0x00  // Bit 6 = 0 para referência interna habilitada

// Estrutura para o comando de escrita de registro
typedef struct {
    uint8_t cmd;        // Byte de comando (WRITE_REG_CMD)
    uint8_t addr_high;  // Parte alta do endereço (0x00 para nossos registros)
    uint8_t addr_low;   // Parte baixa do endereço
    uint8_t data_high;  // Dado alto (nesse caso, contém INTREF_DIS)
    uint8_t data_low;   // Dado baixo (contém RANGE_SEL[3:0])
} ADS8661_WriteCmd;

uint16_t adcBuffer[ADC_BUFFER_SIZE];
float voltage;
float current;
uint8_t time;

float getVoltage(){
    return voltage;
}

float getCurrent(){
    return current;
}

void ADS8661_WriteRegister(uint8_t reg, uint16_t value) {
    // Monta o comando de escrita conforme o datasheet (Tabela 7-5)
    //uint8_t tx[4] = {
    //    WRITE_REG_CMD(reg),  // Byte de comando
    //    0x00,                // Parte alta do endereço (sempre 0 para nossos registros)
    //    reg,                 // Parte baixa do endereço
    //    (value >> 8) & 0xFF, // Dado alto
    //    value & 0xFF         // Dado baixo
    //};
	uint8_t tx[4] = {
			0xD8,
			0x14,
			0x00,
			0x0B
	};

    HAL_SPI_Transmit(&hspi3, tx, 4, HAL_MAX_DELAY);
}

void ADC_Start(void) {
    ADS8661_Deselect(1);
    ADS8661_Deselect(2);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);

    // Configura ADC 1 para faixa 0-5.12V
    ADS8661_Select(1);
    ADS8661_WriteRegister(REG_INPUT_RANGE, (INTREF_ENABLED << 6) | RANGE_0_5V12);
    ADS8661_Deselect(1);

    // Configura ADC 2 para faixa 0-5.12V
    ADS8661_Select(2);
    ADS8661_WriteRegister(REG_INPUT_RANGE, (INTREF_ENABLED << 6) | RANGE_0_5V12);
    ADS8661_Deselect(2);

    HAL_Delay(20); // Tempo para estabilização

    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adcBuffer, ADC_BUFFER_SIZE);

    //HAL_TIM_Base_Start_IT(&htim7);
    HAL_TIM_Base_Start_IT(&htim3);
    Stopwatch_Init();
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
	if (hadc->Instance == ADC1) {  // Verifica se é o ADC esperado
			voltage = ConvertOutputVoltage(adcBuffer[1]);
			current = ConvertOutputCurrent(adcBuffer[0]);
	}
}


void TIM3_Callback() {
	ADS8661_Select(1);
	//ADS8661_WriteRegister(REG_INPUT_RANGE, (INTREF_ENABLED << 6) | RANGE_0_5V12);
	ADS8661_Deselect(1);
    // Leitura do ADC 1 (tensão)
    ADS8661_Select(1);
    //voltage = ADS8661_Read(); // Conversão para tensão (0-5.12V)
    ADS8661_Deselect(1);

    ADS8661_Select(2);
	//ADS8661_WriteRegister(REG_INPUT_RANGE, (INTREF_ENABLED << 6) | RANGE_0_5V12);
	ADS8661_Deselect(2);

    // Leitura do ADC 2 (corrente)
    ADS8661_Select(2);
    //current = ADS8661_Read(); // Conversão para tensão (0-5.12V)
    ADS8661_Deselect(2);
}

void Control_AcquisitionRate(float freq){
    uint32_t ARR = (uint32_t)(72000000/(720 * freq))-1;
    //__HAL_TIM_SET_AUTORELOAD(&htim7, ARR);
    __HAL_TIM_SET_AUTORELOAD(&htim3, ARR);
}
