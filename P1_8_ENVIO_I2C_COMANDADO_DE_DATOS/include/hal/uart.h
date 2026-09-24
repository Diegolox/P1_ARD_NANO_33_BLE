/**
 * @file uart.h
 * @brief Declaraciones para inicializar y leer el puerto serie.
 */
#ifndef UART_H
#define UART_H
#include <Arduino.h>

/** @brief Inicia Serial a la velocidad definida por BAUDRATE. */
void initSerial();
/**
 * @brief Lee una línea de Serial y elimina los blancos de los extremos.
 * @return Mensaje recibido, o cadena vacía si no hay datos disponibles.
 * @note Confirma por Serial el mensaje leído.
 */
String leerSerial();
/**
 * @brief Declaración de una función de conversión de comandos serie.
 * @return Código entero del comando; su significado depende de la implementación.
 * @warning No hay definición de esta función en los archivos .cpp facilitados.
 */
int serialToCommand();

#endif
