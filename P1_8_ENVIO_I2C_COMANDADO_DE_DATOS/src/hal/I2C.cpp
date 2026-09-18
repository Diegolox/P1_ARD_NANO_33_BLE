#include <Wire.h>
#include "hal/i2c.h"

volatile bool datoDisponible = 0;
char BufferI2C[10];


//----------INICIALIZACION----------
void initI2C(){

    // Sin dirección, el Nano funciona como maestro
    Wire.begin();
}

void initI2C(uint8_t direccion){

    Wire.begin(direccion);
    Wire.onReceive(recibirI2C); // se ejecuta cuando llega un mensaje por I2C

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
void recibirI2C(){ // funcion que se ejecuta al recibir algo por I2C
    

}


String leerComandoI2C(){


}

void responderMasterI2C(const char* buffer) {
    Wire.write(buffer);
}

