#include <Arduino.h>
#include "timer.h"
#include "adc.h"

#define PERIODO_TIMER_HW 1000000 // f reloj 1 MHz 

void setup()
{
  Serial.begin(115200);
  iniciarTimer(PERIODO_TIMER_HW);
  inicializarADC(ADC_RESOLUTION);
  inicializarPWM(PWM_PIN, FRECUENCIA_PWM);
}

void loop()
{
  if (hayInterrupcionTimer())
  {
    ADC_to_PWM();
  }
}