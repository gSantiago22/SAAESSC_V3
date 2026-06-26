#include "acquisition_handler.h"

/** 
 * @brief Conversion coefficients for voltage output
 * Voltage and current most usual conversion coefficients
 * If you want to change the scale, you can use the setScalleVoltage and setScalleCurrent functions to adjust the coefficients accordingly.
 * For this, you can use the polynomial approximation to determine the appropriate coefficients for your specific setup.
 * Than, change the coefficients in the respective switch statements.
 */ 

double a1 = 19.7338;      
double a3 = -22.6679;     
double a4 = 43.6774;     
double a5 = -40.6009;
double a6 = 12.7643;
double b1 = 6.84603;

double c9 = 87.36799784;
double c8 = -947.22687347;
double c7 = 2725.84803523;
double c6 = -3633.70725805;
double c5 = 2611.35887564;
double c4 = -1048.17233718;
double c3 = 226.21425662;
double c2 = -23.13681849;
double c1 = 3.13926366;
double c0 = -1.00838969;

float ConvertOutputVoltage(uint16_t DigitalDataVoltageIn){
	float DigitalDataVoltage = (float)DigitalDataVoltageIn/4095;
	float y = a6;
	    y = (y * DigitalDataVoltage) + a5;
	    y = (y * DigitalDataVoltage) + a4;
	    y = (y * DigitalDataVoltage) + a3;
	    y = (y * DigitalDataVoltage) + a1;
	    y = (y * DigitalDataVoltage) - b1;
	return y;
}

float ConvertOutputCurrent(uint16_t DigitalDataCurrentIn){
	float DigitalDataCurrent = (float)DigitalDataCurrentIn/4095;
	float y = c9;
	    y = (y * DigitalDataCurrent) + c8;
	    y = (y * DigitalDataCurrent) + c7;
	    y = (y * DigitalDataCurrent) + c6;
	    y = (y * DigitalDataCurrent) + c5;
	    y = (y * DigitalDataCurrent) + c4;
	    y = (y * DigitalDataCurrent) + c3;
	    y = (y * DigitalDataCurrent) + c2;
	    y = (y * DigitalDataCurrent) + c1;
	    y = (y * DigitalDataCurrent) + c0;
	return y;
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
			a1 = 19.7338;      
			a3 = -22.6679;     
			a4 = 43.6774;     
			a5 = -40.6009;
			a6 = 12.7643;
			b1 = 6.84603;
			break;
	}
}

void setScalleCurrent(int i){
	switch (i) {
		case 0://1V
			c9 = 87.36799784;
			c8 = -947.22687347;
			c7 = 2725.84803523;
			c6 = -3633.70725805;
			c5 = 2611.35887564;
			c4 = -1048.17233718;
			c3 = 226.21425662;
			c2 = -23.13681849;
			c1 = 3.13926366;
			c0 = -1.00838969;
			break;
		case 1:
			c1 = 0.0003;
			c0 = -0.8349;
			break;
	}
}
