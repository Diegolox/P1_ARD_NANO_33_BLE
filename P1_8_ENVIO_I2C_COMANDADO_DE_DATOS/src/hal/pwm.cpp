/**
 * @file pwm.cpp
 * @brief Configuración de la salida PWM y actualización de su ciclo de trabajo.
 */
#include "hal/pwm.h"
#include "config.h"
#include <Arduino.h>
#include <mbed.h>

// Puntero al objeto que controlará el PWM.
// static: solo se puede usar dentro de pwm.cpp y existe todo el programa.
// nullptr: al empezar todavía no se ha creado ningún PWM.
static mbed::PwmOut* pwm = nullptr;

/**
 * @brief Crea la salida PWM en un pin y establece su frecuencia.
 * @param pin Pin Arduino utilizado como salida PWM.
 * @param frecuencia Frecuencia solicitada en hercios.
 * @pre frecuencia debe ser mayor que cero.
 * @note El periodo se calcula en microsegundos mediante división entera.
 */
void initPWM(int pin, int frecuencia) {
  
  // Crea el PWM hardware asociado al pin Arduino indicado.
  // digitalPinToPinName() convierte, por ejemplo, A1 al pin interno del microcontrolador.
  pwm = new mbed::PwmOut(digitalPinToPinName(pin));

  // Configura el periodo de la señal PWM en microsegundos.
  // Como T = 1 / f, para 5000 Hz: T = 1 000 000 / 5000 = 200 µs.
  pwm->period_us(1000000UL / frecuencia);

  // Limita el duty al intervalo permitido: entre 0 y PWM_MAX (255).
  actualizarPWM(0);
}

/**
 * @brief Establece el ciclo de trabajo de la salida PWM.
 * @param duty Valor de ciclo de trabajo; se limita al intervalo 0 a PWM_MAX.
 * @pre La salida PWM debe haberse creado mediante initPWM().
 */
void actualizarPWM(int duty) {
  duty = constrain(duty, 0, PWM_MAX);
  
  // Actualiza el duty cycle de la PWM.
  // PwmOut usa un número entre 0.0 (0 %) y 1.0 (100 %).
  // Se convierte el duty de 0–255 a ese intervalo.
  pwm->write((float)duty / PWM_MAX);
}
