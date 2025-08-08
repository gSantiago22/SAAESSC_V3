#include "comunication_handler.h"
#define DEVICE_ADDRESS 0x42

void TIM1_Callback() {

	// Iniciar envio por I2C com DMA
	//HAL_I2C_Master_Transmit_DMA(&hi2c1, DEVICE_ADDRESS << 1, (uint8_t*)tx_buffer, strlen(tx_buffer));
	//if (HAL_I2C_Master_Transmit(&hi2c1, DEVICE_ADDRESS << 1, (uint8_t *)tx_buffer, strlen(tx_buffer), HAL_MAX_DELAY) != HAL_OK) {
	//			Error_Handler();  // Trate erros na transmissão I2C
	//}
}
