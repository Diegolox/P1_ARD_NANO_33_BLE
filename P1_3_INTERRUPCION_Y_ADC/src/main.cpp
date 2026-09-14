#include <Arduino.h>
#include "timer.h"

#define ADC_PIN A0
#define PERIODO_TIMER_HW 1000000 // f reloj 1 MHz 
#define PWM_max 200

volatile int dutty = 0; //[0-255]

int leerADC(int pin);

void setup()
{
  Serial.begin(115200);
  iniciarTimer(PERIODO_TIMER_HW);
  analogReadResolution(12); // Resolución ADC n bits, en este caso 4095
}

void loop()
{
  if (hayInterrupcionTimer())
  {
    dutty = leerADC(ADC_PIN);

    char buffer[40];

    snprintf(buffer, sizeof(buffer), "El dutty de la PWM es: %d", dutty);

    Serial.println(buffer);
  }
}

int leerADC(int pin) {
  return (analogRead(pin) * 255L) / 4095;
}