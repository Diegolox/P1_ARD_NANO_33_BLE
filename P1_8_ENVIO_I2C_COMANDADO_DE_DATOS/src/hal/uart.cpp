/**
 * @file uart.cpp
 * @brief Inicialización y lectura de mensajes por el puerto serie.
 */
#include <Arduino.h>
#include "config.h"

/** @brief Inicia el puerto serie a la velocidad definida por BAUDRATE. */
void initSerial()
{
    Serial.begin(BAUDRATE);
}

/**
 * @brief Lee una línea recibida por Serial, elimina blancos en los extremos y la confirma.
 * @return Mensaje recibido sin blancos en los extremos, o una cadena vacía
 *         si no hay datos disponibles.
 * @note La lectura espera hasta el salto de línea o hasta el tiempo de espera
 *       configurado para Serial.
 */
String leerSerial()
{
    if (Serial.available() == 0)
        return "";

    String mensaje = Serial.readStringUntil('\n');
    mensaje.trim();

    Serial.print("Arduino ha recibido: ");
    Serial.println(mensaje);

    return mensaje;
}

