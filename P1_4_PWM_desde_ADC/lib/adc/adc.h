#ifndef ADC_H
#define ADC_H

#include <Arduino.h>

#define PWM_PIN A1
#define PWM_MAX 255
#define FRECUENCIA_PWM 5000   // Hz

#define ADC_PIN A0
#define ADC_RESOLUTION 12
#define ADC_MAX 4095

void inicializarADC(int resolution);
int leerADC(int pin, int scale, int resolution);

void inicializarPWM(int pin, int frecuencia);
void actualizarPWM(int duty);

void ADC_to_PWM();

#endif