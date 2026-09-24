/**
 * @file adc.cpp
 * @brief Lectura del ADC y conversión de su valor a un ciclo de trabajo PWM.
 */
#include "hal/adc.h"
#include "hal/pwm.h"
#include "config.h"
#include <Arduino.h>

/**
 * @brief Configura la resolución de las lecturas analógicas.
 * @param resolution Número de bits utilizado por analogRead().
 */
void initADC(int resolution) {
  analogReadResolution(resolution);
}

/**
 * @brief Escala una lectura ADC al rango utilizado por la PWM.
 * @param pin Pin analógico del que se obtiene la lectura.
 * @param scale Valor máximo de la escala de salida.
 * @param resolution Valor máximo esperado de la lectura ADC.
 * @return Lectura escalada mediante aritmética entera.
 * @pre resolution debe ser distinto de cero.
 */
int ADC_to_dutty(int pin, int scale, int resolution) {
  return (analogRead(pin) * scale) / resolution;
}

/**
 * @brief Muestra por el puerto serie la lectura actual del pin ADC_PIN.
 * @pre El puerto serie debe estar inicializado.
 */
void printADC(){
  int adc = analogRead(ADC_PIN);
  char buffer[40];
  snprintf(buffer, sizeof(buffer), "El ADC es: %d", adc);
  Serial.println(buffer);
}

/**
 * @brief Aplica al PWM el valor leído en ADC_PIN y lo muestra por Serial.
 * @details Convierte el rango de lectura definido por ADC_MAX al rango
 *          de salida definido por PWM_MAX.
 * @pre El ADC, el PWM y el puerto serie deben estar inicializados.
 */
void ADC_to_PWM() {
  int duty = ADC_to_dutty(ADC_PIN, PWM_MAX, ADC_MAX);

  actualizarPWM(duty);

  char buffer[40];
  snprintf(buffer, sizeof(buffer), "El duty de la PWM es: %d", duty);
  Serial.println(buffer);
}
