#ifndef SIGNAL_GENERATOR_HANDLER_H
#define SIGNAL_GENERATOR_HANDLER_H

#include "main.h"
#include <stdint.h>
#include <math.h>
#include "dac_handler.h"
#include "stm32f1xx_hal.h"

extern float ScaleOff, ScaleVpp;

typedef enum {
    SINE_WAVE,
    SQUARE_WAVE,
    TRIANGULAR_WAVE,
    CONST_VALUE
} WaveformType;

typedef enum {
    WAVEFORM,
	OFFSET
} OutputType;

typedef enum {
    CURRENT,
    VOLTAGE,
    EN_OFF
} OperationMode;

// Funções para manipulação do sinal
void SetScale(int Scale);
void GenerateWaveform (WaveformType waveform, float vpp, float offset, float frequency, uint16_t DAC_BUFFER_SIZE, uint16_t* dacBuffer1, uint16_t* dacBuffer2);
void GenerateVector(WaveformType waveform, uint16_t* dacuffer, uint16_t DAC_BUFFER_SIZE, float vpp, OutputType type);
void StopGenerateWaveform();

#endif // SIGNAL_CONTROL_HANDLER_H
