#include "hal/i2c.h"
#include <Wire.h>

void initI2C()
{
    // Sin dirección, el Nano funciona como maestro
    Wire.begin();
}

bool escribirI2C(uint8_t direccion, uint8_t dato)
{
    Wire.beginTransmission(direccion);
    Wire.write(dato);

    return Wire.endTransmission() == 0;
}

bool escribirI2C(uint8_t direccion, const char* texto)
{
    Wire.beginTransmission(direccion);
    Wire.print(texto);

    return Wire.endTransmission() == 0;
}

int leerI2C(uint8_t direccion)
{
    // Solicita un byte y comprueba si ha llegado
    if (Wire.requestFrom(direccion, 1) > 0)
    {
        return Wire.read();
    }

    return -1;
}