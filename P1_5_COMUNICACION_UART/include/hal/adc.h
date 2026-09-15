#ifndef ADC_H
#define ADC_H

void inicializarADC(int resolution);
int leerADC(int pin, int scale, int resolution);

void inicializarPWM(int pin, int frecuencia);
void actualizarPWM(int duty);

void ADC_to_PWM();

#endif