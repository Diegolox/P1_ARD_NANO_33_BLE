#ifndef I2C_H
#define I2C_H

#include <Arduino.h>

// inicialización
void initI2C(); // master
void initI2C(uint8_t direccion); // slave

// funciones maestro
bool escribirI2C(uint8_t direccion, uint8_t dato);
bool escribirI2C(uint8_t direccion, const char* texto);
int leerEsclavoI2C(uint8_t direccion);

// funciones esclavo
void recibirI2C(int numeroBytes);
void responderMasterI2C(const char* buffer);
String leerComandoI2C();
void prepararRespuestaI2C(const char* texto);
void enviarRespuestaI2C();

#endif


/*
    --- EJEMPLOS MASTER ---

    // Enviar un byte
    escribirI2C(0x08, static_cast<uint8_t>('A'));

    // Enviar el buffer de snprintf
    char buffer[100];

    snprintf(buffer, sizeof(buffer), "Valor: %d", 25);

    escribirI2C(0x08, buffer);

    // Leer un byte
    int recibido = leerI2C(0x08);

    if (recibido != -1)
    {
        Serial.println(static_cast<char>(recibido));
    }

*/