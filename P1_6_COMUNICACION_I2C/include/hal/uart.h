#ifndef UART_H
#define UART_H
#include <Arduino.h>

void initSerial();
String leerSerial();
int serialToCommand();

#endif