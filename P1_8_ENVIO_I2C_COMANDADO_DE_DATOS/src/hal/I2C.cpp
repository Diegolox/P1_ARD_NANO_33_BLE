#include "hal/i2c.h"
#include <Wire.h>

volatile char datoRecibidoI2C = '\0';


//----------INICIALIZACION----------
void initI2C(){

    // Sin dirección, el Nano funciona como maestro
    Wire.begin();
}

void initI2C(uint8_t direccion){

    Wire.begin(direccion);
}

//----------MAESTRO----------
bool escribirI2C(uint8_t direccion, uint8_t dato){

    Wire.beginTransmission(direccion);
    Wire.write(dato);

    return Wire.endTransmission() == 0;
}

bool escribirI2C(uint8_t direccion, const char* texto){

    Wire.beginTransmission(direccion);
    Wire.print(texto);

    return Wire.endTransmission() == 0;
}

int leerEsclavoI2C(uint8_t direccion){

    // Solicita un byte y comprueba si ha llegado
    if (Wire.requestFrom(direccion, 1) > 0)
    {
        return Wire.read();
    }

    return -1;
}

//----------ESCLAVO----------

