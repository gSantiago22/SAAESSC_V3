#ifndef GPIO_HANDLER_H
#define GPIO_HANDLER_H

#include "main.h"
#include "stdbool.h"
#include "signal_generator_handler.h"
#include "acquisition_handler.h"

void EnableOutput(bool en);
void SourceOperation(OperationMode source);
void ScaleControlOutput(float Vpp);
void ScaleControlinput(int scalecurrent, int scalevoltage);

#endif
