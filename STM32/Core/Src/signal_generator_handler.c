#include "signal_generator_handler.h"
#include "gpio_handler.h"
#define DAC_MAX_VALUE 4096
// Função para inicializar a configuração do sinal

float ScaleOff = 696.4409;
float ScaleWave = 696.9758;

void SetScale(int Scale){
	switch (Scale){	//in=Vout*ScaleWave+ScaleOff (in = 0 - 4095)
		case 0:
			ScaleOff = 696.4409;
			ScaleWave = 696.9758;
			break;
		case 1:
			ScaleOff = 992.5011;//1032.2012
			ScaleWave = 1001.7532;//1048.5017
			break;
		case 2:
			ScaleOff = 2084.1471;
			ScaleWave = 3174.7238;
			break;
		case 3:
			ScaleOff = 18162.6691;
			ScaleWave = 18342.5667;
			break;
	}
}

void GenerateWaveform (WaveformType waveform, float vpp, float offset, float frequency, uint16_t DAC_BUFFER_SIZE,  uint16_t* dacBuffer1, uint16_t* dacBuffer2){
	ScaleControlOutput(vpp);
	GenerateVector(waveform, dacBuffer1, DAC_BUFFER_SIZE, vpp, WAVEFORM);
	GenerateVector(CONST_VALUE, dacBuffer2, DAC_BUFFER_SIZE, offset, OFFSET);
	if (waveform == CONST_VALUE){
		DAC_ChannelConfTypeDef sConfig = {0};

	  // Pare o DAC antes de alterar o trigger
		  HAL_DAC_Stop(&hdac, DAC_CHANNEL_1);
		  HAL_DAC_Stop(&hdac, DAC_CHANNEL_2);

		  // Configure o novo trigger
		  sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
		  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE; // Retém a configuração de buffer

		  // Reconfigure o canal com o novo trigger
		  if (HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_1) != HAL_OK)
		  {
			  // Caso ocorra erro, execute a função de tratamento de erro
			  Error_Handler();
		  }

		  // Reinicie o DAC com a nova configuração

		HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, (uint32_t)dacBuffer1[0]);
		HAL_DAC_SetValue(&hdac, DAC_CHANNEL_2, DAC_ALIGN_12B_R, (uint32_t)dacBuffer2[0]);

		HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
		HAL_DAC_Start(&hdac, DAC_CHANNEL_2);
	} else {
		HAL_DAC_Stop_DMA(&hdac, DAC_CHANNEL_1);
		DAC_Start_DMA(DAC_CHANNEL_1, (uint32_t*)dacBuffer1, DAC_BUFFER_SIZE);
		DAC_Frequency_Control(DAC_CHANNEL_1,frequency,DAC_BUFFER_SIZE);
		HAL_DAC_Stop(&hdac, DAC_CHANNEL_2);
		HAL_DAC_SetValue(&hdac, DAC_CHANNEL_2, DAC_ALIGN_12B_R, (uint32_t)dacBuffer2[0]);
		HAL_DAC_Start(&hdac, DAC_CHANNEL_2);
	}
}

void StopGenerateWaveform(){
	HAL_DAC_Stop_DMA(&hdac, DAC_CHANNEL_1);
	HAL_DAC_Stop_DMA(&hdac, DAC_CHANNEL_2);
}

void GenerateVector(WaveformType waveform, uint16_t* dacBuffer, uint16_t DAC_BUFFER_SIZE, float vpp, OutputType type) {
	float Scale;
	switch (type){
		case OFFSET:
			Scale = ScaleOff;
			vpp = -2*vpp;
			break;
		case WAVEFORM:
			Scale = ScaleWave;
			break;
	}

	uint16_t centerValue = DAC_MAX_VALUE / 2; // Valor central (2048)

    switch (waveform) {
        case SINE_WAVE:
            for (uint16_t i = 0; i < DAC_BUFFER_SIZE; i++) {
                // O sinal senoidal é normalizado para variar de 0 a 4095
                // Ajustado para oscilar em torno de 2048
                dacBuffer[i] = (uint16_t)(centerValue +
                                          (((vpp/2) * Scale) * sin(2 * M_PI * i / DAC_BUFFER_SIZE)));
            }
            break;

        case SQUARE_WAVE:
            for (uint16_t i = 0; i < DAC_BUFFER_SIZE; i++) {
                // Metade do sinal em nível alto (acima de 2048), metade em nível baixo (abaixo de 2048)
                if (i < DAC_BUFFER_SIZE / 2) {
                    dacBuffer[i] = (uint16_t)(centerValue + ((vpp/2) * Scale)); // Nível alto
                } else {
                    dacBuffer[i] = (uint16_t)(centerValue - ((vpp/2) * Scale)); // Nível baixo
                }
            }
            break;

        case TRIANGULAR_WAVE:
            for (uint16_t i = 0; i < DAC_BUFFER_SIZE; i++) {
                if (i < DAC_BUFFER_SIZE / 2) {
                    //Crescimento linear na primeira metade, ajustado para oscilar em torno de 2048
                    dacBuffer[i] = (uint16_t)((centerValue - (vpp/2) * Scale) +
                                              ((vpp * Scale * i) / (DAC_BUFFER_SIZE/2)));
                } else {
                    // Decrescimento linear na segunda metade
                    dacBuffer[i] = (uint16_t)((centerValue + (vpp/2) * Scale) -
                                              ((vpp * Scale * (i - DAC_BUFFER_SIZE / 2)) / (DAC_BUFFER_SIZE/2)));
                }
            }
            break;

        case CONST_VALUE:
            for (uint16_t i = 0; i < DAC_BUFFER_SIZE; i++) {
                // Valor constante em 2048 (meio da faixa) ajustado pelo ScaleVpp
                dacBuffer[i] = (uint16_t)(centerValue + ((vpp/2) * Scale));
                if (dacBuffer[i]>4095){
                	dacBuffer[i] = 4095;
                }
            }
            break;

        default:
            // Buffer zerado para casos inválidos
            for (uint16_t i = 0; i < DAC_BUFFER_SIZE; i++) {
                dacBuffer[i] = 0;
            }
            break;
    }
}




// Função para atualizar o erro do sinal gerado

void DigitalControl(OperationMode Operation){
	switch (Operation) {
		case CURRENT:
			break;
		case VOLTAGE:
			break;
		case EN_OFF:
			break;
	}
}
