/**
 * @file timer.h
 * @brief Declaraciones para controlar los eventos periódicos de TIMER3.
 */
#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

/**
 * @brief Configura y arranca TIMER3 con interrupciones periódicas.
 * @param periodoMicrosegundos Periodo en microsegundos cargado en CC[0].
 * @note TIMER3 trabaja a 1 MHz: un incremento del contador equivale a 1 µs.
 */
void setTimer(uint32_t periodoMicrosegundos);
/** @brief Detiene TIMER3 y borra la marca de interrupción pendiente. */
void stopTimer();
/**
 * @brief Consulta y limpia la marca de interrupción pendiente.
 * @return true si ocurrió al menos una comparación desde la última consulta;
 *         false si no ocurrió ninguna.
 * @note Varias comparaciones pendientes se representan mediante una sola marca.
 */
bool hayInterrupcionTimer();

#endif
