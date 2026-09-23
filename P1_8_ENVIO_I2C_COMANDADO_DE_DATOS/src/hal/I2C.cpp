#include <Wire.h>
#include "hal/i2c.h"

volatile bool comandoDisponible = 0;
char BufferI2C[10];
char respuestaI2C[32] = "ESPERA";


//----------INICIALIZACION----------
void initI2C(){

    // Sin dirección, el Nano funciona como maestro
    Wire.begin();
}

void initI2C(uint8_t direccion){

    Wire.begin(direccion);
    Wire.onRequest(enviarRespuestaI2C);
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
void recibirI2C(int numeroBytes){ // funcion que se ejecuta al recibir algo por I2C y mediante puntero indica el número de bytes recibidos
    if (numeroBytes == 2 && Wire.available() >= 2) {
        BufferI2C[0] = Wire.read();  // Número del registro
        BufferI2C[1] = Wire.read();  // A, G o M
        BufferI2C[2] = '\0';         // Final de cadena

        comandoDisponible = true;
    }
}


String leerComandoI2C(){
    if (!comandoDisponible) {
        return "";
    }

    String comando = BufferI2C;
    comandoDisponible = false;

    return comando;
}

void prepararRespuestaI2C(const char* texto) {
    char copia[32] = {};
    strncpy(copia, texto, sizeof(copia) - 1);

    noInterrupts();
    memcpy(respuestaI2C, copia, sizeof(copia));
    interrupts();
}

void enviarRespuestaI2C() {
    Wire.write((const uint8_t*)respuestaI2C, sizeof(respuestaI2C));
}