#include <Arduino.h>
#include "config.h"

void initSerial()
{
    Serial.begin(BAUDRATE);
}

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

