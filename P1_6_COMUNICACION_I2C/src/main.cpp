#include <Arduino.h>
#include "hal/timer.h"
#include "hal/adc.h"
#include "hal/pwm.h"
#include "hal/uart.h"
#include "app/protocolo.h"
#include "config.h"

#define PERIODO_TIMER_HW 1000000 // f reloj 1 MHz 


void setup()
{
  initSerial();
  setTimer(PERIODO_TIMER_HW);
  stopTimer();
  initADC(ADC_RESOLUTION);
  initPWM(PWM_PIN, FRECUENCIA_PWM);
}

void loop()
{
  procesarComandoSerial();
  if(hayInterrupcionTimer())
  {
    printADC();
  }
}



/*

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

*/