#include <Arduino.h>
#include "timer.h"

#define ADC_PIN A0
#define PERIODO_TIMER_HW 1000000 // f reloj 1 MHz 

void setup()
{
  Serial.begin(115200);
  iniciarTimer(PERIODO_TIMER_HW);
}

void loop()
{
  if (hayInterrupcionTimer())
  {
      int lectura = analogRead(ADC_PIN);

      Serial.print("Lectura ADC: ");
      Serial.println(lectura);
  }
}