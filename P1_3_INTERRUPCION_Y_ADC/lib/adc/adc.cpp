#include "adc.h"
#include <Arduino.h>

void inicializarADC(int resolution) {
  analogReadResolution(resolution); // Resolución ADC n bits, en este caso 4095
}

int leerADC(int pin) {
  int ADC_value = analogRead(pin);  
  char buffer[40];
  snprintf(buffer, sizeof(buffer), "El valor del ADC es: %d", ADC_value);
  Serial.println(buffer);
  return ADC_value;
}