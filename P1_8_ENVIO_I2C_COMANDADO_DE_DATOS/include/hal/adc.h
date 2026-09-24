/**
 * @file adc.h
 * @brief Declaraciones para leer el ADC y usar su lectura en una salida PWM.
 */
#ifndef ADC_H
#define ADC_H


/**
 * @brief Configura la resolución de analogRead().
 * @param resolution Número de bits de la lectura analógica.
 */
void initADC(int resolution);
/**
 * @brief Convierte una lectura ADC al rango de ciclo de trabajo indicado.
 * @param pin Pin analógico del que se toma la lectura.
 * @param scale Valor máximo de la escala de salida.
 * @param resolution Valor máximo esperado de la lectura ADC.
 * @return Valor escalado con división entera.
 * @pre resolution debe ser distinto de cero.
 */
int ADC_to_dutty(int pin, int scale, int resolution);

/** @brief Imprime por Serial la lectura del pin ADC_PIN. */
void printADC();

/**
 * @brief Convierte la lectura de ADC_PIN en un ciclo de trabajo PWM.
 * @note Actualiza la salida PWM e imprime el ciclo de trabajo por Serial.
 * @pre El ADC, la PWM y Serial deben estar inicializados.
 */
void ADC_to_PWM();

#endif
