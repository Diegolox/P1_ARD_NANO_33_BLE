#include "hal/i2c.h"
#include <Wire.h>

void initI2C()
{
    // Sin dirección: el Nano funciona como maestro
    Wire.begin();
}

bool escribirI2C(uint8_t direccion, uint8_t dato)
{
    // Comienza la comunicación con el esclavo
    Wire.beginTransmission(direccion);

    // Envía un byte
    Wire.write(dato);

    // Finaliza la comunicación y comprueba errores
    uint8_t error = Wire.endTransmission();

    return error == 0;
}

int leerI2C(uint8_t direccion)
{
    // Solicita un byte al esclavo
    Wire.requestFrom(direccion, (uint8_t)1);

    // Comprueba si el byte ha llegado
    if (Wire.available())
    {
        return Wire.read();
    }

    // Indica que ha ocurrido un error
    return -1;
}