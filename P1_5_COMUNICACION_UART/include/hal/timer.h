#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

void setTimer(uint32_t periodoMicrosegundos);
void stopTimer();
bool hayInterrupcionTimer();

#endif