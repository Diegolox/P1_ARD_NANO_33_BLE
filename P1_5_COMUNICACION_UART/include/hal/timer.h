#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

void initTimer(uint32_t periodoMicrosegundos);
bool hayInterrupcionTimer();

#endif