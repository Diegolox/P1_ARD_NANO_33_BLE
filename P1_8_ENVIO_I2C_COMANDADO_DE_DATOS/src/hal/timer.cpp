/**
 * @file timer.cpp
 * @brief Configuración del TIMER3 y comunicación de sus eventos al programa.
 */
#include "hal/timer.h"
#include <nrf_timer.h>

/** @brief Señala que TIMER3 ha alcanzado el valor de comparación. */
volatile bool interrupcionTimer = false;

// Esta función se ejecuta al cumplirse el periodo del TIMER3
/**
 * @brief Atiende la interrupción de comparación del TIMER3.
 * @details Limpia el evento de hardware y activa una marca para el programa.
 */
static void isrTimer3() {
  if (NRF_TIMER3->EVENTS_COMPARE[0] == 1) {
    NRF_TIMER3->EVENTS_COMPARE[0] = 0;  // Borra el evento pendiente
    interrupcionTimer = true;           // Avisa a loop()
  }
}

/**
 * @brief Configura y arranca TIMER3 para generar eventos periódicos.
 * @param periodoMicrosegundos Periodo en microsegundos cargado en CC[0].
 * @note El temporizador utiliza una frecuencia de 1 MHz y reinicia el contador
 *       automáticamente tras cada comparación con CC[0].
 */
void setTimer(uint32_t periodoMicrosegundos) {

  NRF_TIMER3->TASKS_STOP = 1;    // Detiene el timer por seguridad
  NRF_TIMER3->TASKS_CLEAR = 1;   // Reinicia el contador a cero

  NRF_TIMER3->BITMODE = 3UL;     // Contador de 32 bits
  NRF_TIMER3->MODE = 0UL;        // Modo temporizador, no contador externo
  NRF_TIMER3->PRESCALER = 4UL;   // 16 MHz / 2^4 = 1 MHz → 1 tick = 1 us

  NRF_TIMER3->CC[0] = periodoMicrosegundos;

  // Genera interrupción al llegar al valor CC[0]
  NRF_TIMER3->INTENSET = 1UL << TIMER_INTENSET_COMPARE0_Pos;

  // Al comparar, reinicia automáticamente el contador: timer periódico
  NRF_TIMER3->SHORTS = 1UL << TIMER_SHORTS_COMPARE0_CLEAR_Pos;

  // Asocia nuestra ISR al vector de interrupción del TIMER3
  NVIC_SetVector(TIMER3_IRQn, (uint32_t)isrTimer3);
  NVIC_ClearPendingIRQ(TIMER3_IRQn);
  NVIC_EnableIRQ(TIMER3_IRQn);

  NRF_TIMER3->TASKS_START = 1;   // Inicia el timer
}


/**
 * @brief Detiene TIMER3, deshabilita su interrupción y borra la marca pendiente.
 */
void stopTimer()
{
    NRF_TIMER3->TASKS_STOP = 1;
    NRF_TIMER3->INTENCLR =
        1UL << TIMER_INTENCLR_COMPARE0_Pos;

    noInterrupts();
    interrupcionTimer = false;
    interrupts();
}

/**
 * @brief Consulta y consume la marca de interrupción del TIMER3.
 * @return true si se produjo al menos una comparación desde la última consulta;
 *         false si no hay ninguna pendiente.
 * @note Varias comparaciones antes de la consulta se representan con una sola marca.
 */
bool hayInterrupcionTimer() {
  bool hayInterrupcion;

  noInterrupts();
  hayInterrupcion = interrupcionTimer;
  interrupcionTimer = false;
  interrupts();

  return hayInterrupcion;
}
