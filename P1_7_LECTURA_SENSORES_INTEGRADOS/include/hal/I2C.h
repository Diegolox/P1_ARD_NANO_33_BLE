#ifndef I2C_H
#define I2C_H

#include <Arduino.h>

void initI2C(); // Inicializa como master

bool escribirI2C(uint8_t direccion, uint8_t dato);


int leerI2C(uint8_t direccion);

#endif