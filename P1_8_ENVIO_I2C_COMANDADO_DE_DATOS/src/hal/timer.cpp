#include "hal/timer.h"
#include <nrf_timer.h>

volatile bool interrupcionTimer = false;

// Esta función se ejecuta al cumplirse el periodo del TIMER3
static void isrTimer3() {
  if (NRF_TIMER3->EVENTS_COMPARE[0] == 1) {
    NRF_TIMER3->EVENTS_COMPARE[0] = 0;  // Borra el evento pendiente
    interrupcionTimer = true;           // Avisa a loop()
  }
}

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


void stopTimer()
{
    NRF_TIMER3->TASKS_STOP = 1;
    NRF_TIMER3->INTENCLR =
        1UL << TIMER_INTENCLR_COMPARE0_Pos;

    noInterrupts();
    interrupcionTimer = false;
    interrupts();
}

bool hayInterrupcionTimer() {
  bool hayInterrupcion;

  noInterrupts();
  hayInterrupcion = interrupcionTimer;
  interrupcionTimer = false;
  interrupts();

  return hayInterrupcion;
}
