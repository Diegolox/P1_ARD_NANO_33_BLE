#include "hal/adc.h"
#include "hal/pwm.h"
#include "config.h"
#include <Arduino.h>

void inicializarADC(int resolution) {
  analogReadResolution(resolution);
}

int leerADC(int pin, int scale, int resolution) {
  return (analogRead(pin) * scale) / resolution;
}

void ADC_to_PWM() {
  int duty = leerADC(ADC_PIN, PWM_MAX, ADC_MAX);

  actualizarPWM(duty);

  char buffer[40];
  snprintf(buffer, sizeof(buffer), "El duty de la PWM es: %d", duty);
  Serial.println(buffer);
}