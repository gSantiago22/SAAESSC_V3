#include "acquisition_handler.h"

float a1 = 0.0027;
float b1 = 5.3897;
float a2 = 0.0017;
float b2 = 4.3150;

float ConvertOutputVoltage(uint16_t DigitalDataVoltage){
	return a1*DigitalDataVoltage - b1;
}

float ConvertOutputCurrent(uint16_t DigitalDataCurrent){
	return a2*DigitalDataCurrent - b2;
}

void setScalleVoltage(int i){
	switch (i) {
		case 0: //conferir
			a1 = 0.0000001137;
			b1 = 0.1201794601;
			break;
		case 1:
			a1 = 0.0005;
			b1 = 0.9326;
			break;
		case 2:
			a1 = 0.0015810725552;
			b1 = 2.925538170347;
			break;
		case 3:
			a1 = 0.0029166228;
			b1 = 5.416929825;
			break;
	}
}

void setScalleCurrent(int i){
	switch (i) {
		case 0://1V
			a2 = 0.0005290675;
			b2 = 0.957205;
			break;
		case 1:
			a2 = 0.0003;
			b2 = 0.8349;
			break;
	}
}
