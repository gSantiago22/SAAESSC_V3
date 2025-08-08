#include "test_routines_handler.h"
#include "gpio_handler.h"
#include "acquisition_handler.h"
#include "string.h"
#include "timer_acquisition_handler.h"
#include "stdio.h"
#include "math.h"
#define DAC_MAX_VALUE 4095
#define DEVICE_ADDRESS 0x42

void ImpedanceSpectroscopy(float min_frequency, float max_frequency, int num_frequencies) {
    uint32_t time;
    uint32_t SMP;
    float Vsc, Csc;

    float frequencies[num_frequencies];
    float log_step = (max_frequency - min_frequency)/num_frequencies;

    // Gera as frequências log-espaçadas
    frequencies[0] = min_frequency;
    for (int i = 1; i < num_frequencies; i++) {
        frequencies[i] = frequencies[i - 1] + log_step;
    }


    SourceOperation(VOLTAGE);
    uint16_t wave[8];
            uint16_t off[8];
    GenerateWaveform(SINE_WAVE, 0.1, 0, min_frequency, 8, wave, off); // 10 mVpp, offset 0

    for (int i = 0; i < num_frequencies; i++) {
        float freq = frequencies[i];
        DAC_Frequency_Control(DAC_CHANNEL_1, freq,8);

        Reset_Periods();
        EnableOutput(true);
        while (Get_Periods() < 5) {
			// Coleta após 1 ciclo completo
			Vsc = getVoltage();
			Csc = getCurrent();
			time = Get_Current_Time();

			snprintf(tx_buffer, sizeof(tx_buffer), "%.3f %.3f %lu %.3f", Csc, Vsc, time, freq);

        }
        HAL_Delay(200);  // tempo entre frequências (estabilização)
    }

}


void CiclicVoltametry(float vpp, float offset, float ScanRate_mVs, uint32_t cycles){
    uint16_t wave[4096];
    uint16_t off[4096];
    uint32_t time;
    float Vsc, Csc;

    // Frequência da onda triangular baseada na taxa de varredura
    // período = 2 * vpp / ScanRate => f = 1 / período
    float freq = ScanRate_mVs / (2*vpp * 1000); // Convertido para Hz

    uint32_t samples_per_cycle = 4096;

    // Gera a forma de onda triangular
    GenerateWaveform(TRIANGULAR_WAVE, vpp, offset, freq, 4096, wave, off);

    SourceOperation(VOLTAGE);
    EnableOutput(true);
    Reset_Periods();
    while(1) {
    	if (Get_Periods() == cycles){
    		break;
    	}
        Vsc = getVoltage();
        Csc = getCurrent();
        time = Get_Current_Time();

        snprintf(tx_buffer, sizeof(tx_buffer), "%.3f %.3f %lu", Csc, Vsc, time);
        if (HAL_I2C_Master_Transmit(&hi2c1, DEVICE_ADDRESS << 1, (uint8_t *)tx_buffer, strlen(tx_buffer), HAL_MAX_DELAY) != HAL_OK) {
            Error_Handler();
        }

        HAL_Delay((uint32_t)(1000.0 / (freq * samples_per_cycle))); // tempo entre amostras
    }

    EnableOutput(false);
	//StopGenerateWaveform();
}

void ConstantCurrent_ChargeDischarge(float current_mA, float res, float maxvoltage_V, float minvoltage_V, uint32_t cycles){
	uint16_t current[32];
	uint16_t offset[32];
	uint32_t time;

	float Vc = 2*current_mA*(res+0.235)/1000;
	float Vsc, Csc;
	GenerateWaveform(CONST_VALUE, Vc, 0.0062, 0, 32, current, offset);

	bool charge = true;

	SourceOperation(CURRENT);
	EnableOutput(true);

	for (uint32_t i = 0; i<cycles; i++){
		while(1){
			Vsc = getVoltage();
			Csc = getCurrent();
			time = Get_Current_Time();
			if (charge && Vsc >= maxvoltage_V) {
				GenerateWaveform(CONST_VALUE, -Vc, 0.0062, 0, 32, current, offset);
				charge = false;
			} else if (!charge && Vsc <= minvoltage_V) {
				GenerateWaveform(CONST_VALUE, Vc, 0.0062, 0, 32, current, offset);
				charge = true;
				break; // Termina um ciclo de carga e descarga
			}


			snprintf(tx_buffer, sizeof(tx_buffer), "%.3f %.3f %lu", Csc, Vsc, time);
			//HAL_I2C_Master_Transmit_DMA(&hi2c1, DEVICE_ADDRESS << 1, (uint8_t*)tx_buffer, strlen(tx_buffer));

			// Iniciar envio por I2C com DMA
			//HAL_I2C_Master_Transmit_DMA(&hi2c1, DEVICE_ADDRESS << 1, (uint8_t*)tx_buffer, strlen(tx_buffer));
			if (HAL_I2C_Master_Transmit(&hi2c1, DEVICE_ADDRESS << 1, (uint8_t *)tx_buffer, strlen(tx_buffer), HAL_MAX_DELAY) != HAL_OK) {
						Error_Handler();  // Trate erros na transmissão I2C
			}
			HAL_Delay(50);
		}
	}

	EnableOutput(false);
}
void ConstantCurrent_Charge_AutoDischarge(float current_mA, float res, float maxvoltage_V, float dischargetime_s){
	uint16_t current[32];
		uint16_t offset[32];
		uint32_t time;

		float Vc = 2*current_mA*(res+0.235)/1000;
		float Vsc, Csc;
		float discharge_time_init;
		GenerateWaveform(CONST_VALUE, Vc, 0.0062, 0, 32, current, offset);

		bool charge = true;

		SourceOperation(CURRENT);
		EnableOutput(true);

		while(1){
			Vsc = getVoltage();
			Csc = getCurrent();
			time = Get_Current_Time();
			if (charge && Vsc >= maxvoltage_V) {
				discharge_time_init = time;
				EnableOutput(false);
				charge = false;
			}
			if (!charge) {
				if (time - discharge_time_init >= (dischargetime_s*1000)){
					break;
				}
			}
			snprintf(tx_buffer, sizeof(tx_buffer), "%.3f %.3f %lu", Csc, Vsc, time);
			// Iniciar envio por I2C com DMA
			//HAL_I2C_Master_Transmit_DMA(&hi2c1, DEVICE_ADDRESS << 1, (uint8_t*)tx_buffer, strlen(tx_buffer));
			if (HAL_I2C_Master_Transmit(&hi2c1, DEVICE_ADDRESS << 1, (uint8_t *)tx_buffer, strlen(tx_buffer), HAL_MAX_DELAY) != HAL_OK) {
						Error_Handler();  // Trate erros na transmissão I2C
			}
			if (charge){
				HAL_Delay(10);
			} else{
				HAL_Delay(1000);
			}

		}

		EnableOutput(false);
    	//StopGenerateWaveform();
}

void ConstantCurrent_Charge_AutoDischarge1(float current_mA, float res, float maxvoltage_V, float dischargetime_s){
	uint16_t current[32];
		uint16_t offset[32];
		uint32_t time;

		float Vc = 2*current_mA*(res+0.235)/1000;
		float Vsc, Csc;
		float discharge_time_init;
		GenerateWaveform(CONST_VALUE, Vc, 0.0062, 0, 32, current, offset);

		bool charge = true;

		SourceOperation(CURRENT);
		EnableOutput(true);

		while(1){
			Vsc = getVoltage();
			Csc = getCurrent();
			time = Get_Current_Time();
			if (charge && Vsc >= maxvoltage_V) {
				discharge_time_init = time;
				GenerateWaveform(CONST_VALUE, 0, 0.0062, 0, 32, current, offset);
				charge = false;
			}
			if (!charge) {
				if (time - discharge_time_init >= (dischargetime_s*1000)){
					break;
				}
			}
			snprintf(tx_buffer, sizeof(tx_buffer), "%.3f %.3f %lu", Csc, Vsc, time);
			// Iniciar envio por I2C com DMA
			//HAL_I2C_Master_Transmit_DMA(&hi2c1, DEVICE_ADDRESS << 1, (uint8_t*)tx_buffer, strlen(tx_buffer));
			if (HAL_I2C_Master_Transmit(&hi2c1, DEVICE_ADDRESS << 1, (uint8_t *)tx_buffer, strlen(tx_buffer), HAL_MAX_DELAY) != HAL_OK) {
						Error_Handler();  // Trate erros na transmissão I2C
			}
			HAL_Delay(10);
		}

		EnableOutput(false);
    	//StopGenerateWaveform();
}
