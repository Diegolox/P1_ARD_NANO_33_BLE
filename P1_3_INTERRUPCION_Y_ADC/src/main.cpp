#include <Arduino.h>
#include "timer.h"
#include "adc.h"


#define PERIODO_TIMER_HW 10000000 // f reloj 1 MHz 


void setup()
{
  Serial.begin(115200);
  iniciarTimer(PERIODO_TIMER_HW);
  inicializarADC(ADC_RESOLUTION);
}

void loop()
{
  if (hayInterrupcionTimer())
  {
    leerADC(ADC_PIN);
  }
}