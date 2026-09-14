#ifndef ADC_H
#define ADC_H

#include <Arduino.h>

#define PWM_PIN A1
#define PWM_init 0
#define PWM_MAX 255

#define ADC_PIN A0
#define ADC_RESOLUTION 12 // Resolución ADC n bits, en este caso 4095
#define ADC_MAX 4095

void inicializarADC(int resolution);
int leerADC(int pin, int scale, int resolution);

void inicializarPWM(int pin, int dutty_init);
void actualizarPWM(int pin, int dutty);

void ADC_to_PWM();

#endif