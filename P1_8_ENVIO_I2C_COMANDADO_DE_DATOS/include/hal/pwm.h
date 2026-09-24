/**
 * @file pwm.h
 * @brief Declaraciones para configurar y controlar una salida PWM.
 */
#ifndef PWM_H
#define PWM_H

/**
 * @brief Crea la salida PWM en el pin indicado y configura su frecuencia.
 * @param pin Pin Arduino utilizado como salida.
 * @param frecuencia Frecuencia deseada en hercios.
 * @pre frecuencia debe ser mayor que cero.
 */
void initPWM(int pin, int frecuencia);
/**
 * @brief Ajusta el ciclo de trabajo de la PWM.
 * @param duty Valor limitado internamente al intervalo 0 a PWM_MAX.
 * @pre Se debe llamar antes a initPWM().
 */
void actualizarPWM(int duty);

#endif
