#ifndef ACQUISITION_HANDLER_H
#define ACQUISITION_HANDLER_H

#include "main.h"

extern float a1, a2, b1, b2;

float ConvertOutputVoltage(uint16_t DigitaDataVoltage);
float ConvertOutputCurrent(uint16_t DigitaDataCurrent);
void setScalleVoltage(int i);
void setScalleCurrent(int i);

#endif
