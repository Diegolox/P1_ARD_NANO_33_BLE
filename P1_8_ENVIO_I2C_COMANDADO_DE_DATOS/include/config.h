/**
 * @file config.h
 * @brief Pines y constantes generales de configuración del proyecto.
 */
#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

/** @brief Pin analógico utilizado para leer el ADC. */
#define ADC_PIN A0
/** @brief Pin utilizado como salida PWM. */
#define PWM_PIN A1

/** @brief Resolución de la lectura ADC, en bits. */
#define ADC_RESOLUTION 12
/** @brief Valor máximo de una lectura ADC de 12 bits. */
#define ADC_MAX 4095

/** @brief Valor máximo utilizado para expresar el ciclo de trabajo PWM. */
#define PWM_MAX 255
/** @brief Periodo de referencia del temporizador, en microsegundos. */
#define TIMER_PERIOD_US 1000000
/** @brief Frecuencia solicitada para la salida PWM, en hercios. */
#define FRECUENCIA_PWM 7000

/** @brief Velocidad de comunicación del puerto serie, en baudios. */
#define BAUDRATE 115200

/** @brief Dirección I2C configurada para el ESP32 cuando actúa como esclavo. */
#define ESP_SLAVE 0x08

#endif
