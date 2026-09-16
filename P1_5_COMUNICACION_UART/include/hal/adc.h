#ifndef ADC_H
#define ADC_H


void initADC(int resolution);
int ADC_to_dutty(int pin, int scale, int resolution);

void printADC();

void ADC_to_PWM();

#endif