#ifndef APP_H
#define APP_H

void printIMU();

void senIMU_I2C(uint8_t direccion);

void sendMag_I2C(uint8_t direccion);

void sendGir_I2C(uint8_t direccion);

void sendAce_I2C(uint8_t direccion);

#endif