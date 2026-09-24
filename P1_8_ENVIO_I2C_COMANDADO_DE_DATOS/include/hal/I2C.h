/**
 * @file I2C.h
 * @brief Declaraciones de comunicación I2C en modo maestro y esclavo.
 */
#ifndef I2C_H
#define I2C_H

#include <Arduino.h>

// inicialización
/** @brief Inicializa el bus I2C en modo maestro. */
void initI2C(); // master
/**
 * @brief Inicializa el bus I2C en modo esclavo y registra sus callbacks.
 * @param direccion Dirección I2C asignada al dispositivo.
 */
void initI2C(uint8_t direccion); // slave

// funciones maestro
/**
 * @brief Envía un byte a un dispositivo I2C.
 * @param direccion Dirección del destinatario.
 * @param dato Byte que se envía.
 * @return true si la transmisión finaliza sin error; false en caso contrario.
 */
bool escribirI2C(uint8_t direccion, uint8_t dato);
/**
 * @brief Envía el contenido de una cadena a un dispositivo I2C.
 * @param direccion Dirección del destinatario.
 * @param texto Cadena terminada en nulo; el terminador no se envía.
 * @return true si la transmisión finaliza sin error; false en caso contrario.
 */
bool escribirI2C(uint8_t direccion, const char* texto);
/**
 * @brief Solicita un byte a un esclavo I2C.
 * @param direccion Dirección del esclavo.
 * @return Byte recibido (0 a 255), o -1 si no se ha recibido ninguno.
 */
int leerEsclavoI2C(uint8_t direccion);

// funciones esclavo
/**
 * @brief Guarda un comando I2C de dos caracteres recibido por el esclavo.
 * @param numeroBytes Número de bytes notificado por Wire.onReceive().
 * @note Solo guarda el comando si numeroBytes es 2 y ambos bytes están disponibles.
 */
void recibirI2C(int numeroBytes);
/**
 * @brief Declaración de una función para responder al maestro I2C.
 * @param buffer Puntero a los datos previstos para la respuesta.
 * @warning No hay definición de esta función en los archivos .cpp facilitados.
 */
void responderMasterI2C(const char* buffer);
/**
 * @brief Obtiene el comando recibido y limpia la marca de disponibilidad.
 * @return Comando de dos caracteres, o cadena vacía si no hay uno pendiente.
 */
String leerComandoI2C();
/**
 * @brief Prepara el búfer de 32 bytes que se enviará al maestro I2C.
 * @param texto Cadena terminada en nulo; se copian hasta 31 caracteres.
 */
void prepararRespuestaI2C(const char* texto);
/**
 * @brief Envía el búfer de 32 bytes cuando el maestro solicita datos.
 * @note Función registrada con Wire.onRequest().
 */
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
