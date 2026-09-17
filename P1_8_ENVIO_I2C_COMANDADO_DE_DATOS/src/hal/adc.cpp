#include "hal/adc.h"
#include "hal/pwm.h"
#include "config.h"
#include <Arduino.h>

void initADC(int resolution) {
  analogReadResolution(resolution);
}

int ADC_to_dutty(int pin, int scale, int resolution) {
  return (analogRead(pin) * scale) / resolution;
}

void printADC(){
  int adc = analogRead(ADC_PIN);
  char buffer[40];
  snprintf(buffer, sizeof(buffer), "El ADC es: %d", adc);
  Serial.println(buffer);
}

void ADC_to_PWM() {
  int duty = ADC_to_dutty(ADC_PIN, PWM_MAX, ADC_MAX);

  actualizarPWM(duty);

  char buffer[40];
  snprintf(buffer, sizeof(buffer), "El duty de la PWM es: %d", duty);
  Serial.println(buffer);
}