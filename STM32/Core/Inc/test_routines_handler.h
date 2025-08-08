#ifndef TEST_ROUTINES_HANDLER_H
#define TEST_ROUTINES_HANDLER_H

#include "main.h"
#include "stm32f1xx_hal.h"
#include "stdbool.h"
#include "signal_generator_handler.h"
#include "adc_handler.h"
#include "dac_handler.h"
#include "gpio_handler.h"

// Tipos de forma de onda
void ImpedanceSpectroscopy(float min_frequency, float max_frequency, int num_frequencies);
void Test (WaveformType waveform, uint16_t vpp, uint16_t offset, float frequency, uint16_t SMP, uint16_t* dacBuffer);
void CiclicVoltametry(float vpp, float offset, float ScanRate_mVs, uint32_t cycles);
void ConstantCurrent_ChargeDischarge(float current_mA, float res, float maxvoltage_V, float minvoltage_V, uint32_t cycles);
void ConstantCurrent_Charge_AutoDischarge(float current_mA, float res, float maxvoltage_V, float dischargetime_s);
void ConstantCurrent_Charge_AutoDischarge1(float current_mA, float res, float maxvoltage_V, float dischargetime_s);

#endif
