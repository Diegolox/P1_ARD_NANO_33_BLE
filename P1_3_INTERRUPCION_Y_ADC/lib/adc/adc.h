#ifndef ADC_H
#define ADC_H

#include <Arduino.h>

#define ADC_PIN A0
#define ADC_RESOLUTION 12 // Resolución ADC n bits, en este caso 4095
#define ADC_MAX 4095

void inicializarADC(int resolution);
int leerADC(int pin);

#endif