#include <Arduino.h>
#include "app/telemetria.h"
#include "hal/uart.h"
#include "hal/adc.h"
#include "hal/pwm.h"
#include "hal/timer.h"
#include "hal/I2C.h"

void procesarComandoSerial()
{
    String mensaje = leerSerial();

    if (mensaje.length() == 0) //no hago nada
        return;

    if(mensaje == "STOP"){
        stopTimer();
        actualizarPWM(0);
    }

    if (mensaje == "ADC"){ //devuelve lectura ADC actual
        stopTimer();
        printADC();
    }

    if (mensaje.startsWith("ADC(") && mensaje.endsWith(")")){ //devuelve cada x segundos lectura ADC
        int periodo = mensaje.substring(4, mensaje.length() - 1).toInt();
        setTimer(periodo * 1000000UL); // convierte de segundos a microsegundos
    }

    if (mensaje.startsWith("PWM(") && mensaje.endsWith(")")){
        int dutty = mensaje.substring(4, mensaje.length() - 1).toInt();

        if (dutty <= 0) dutty = 0;
        if (dutty >= 9) dutty = 9;
        actualizarPWM(255*dutty/9);
        
        char buffer[40];
        snprintf(buffer, sizeof(buffer), "El dutty de la PWM es: %d", dutty);
        Serial.println(buffer);
    }

}

void procesarComandoI2C_IMU() {

    String comando = leerComandoI2C();

    // No ha llegado ningún comando
    if (comando == "") return;

    // El comando debe tener exactamente dos caracteres
    if (comando.length() != 2) return;

    // Extraer los caracteres
    char numero = comando[0];
    char dato = comando[1];

    // Comprobar que el registro está entre '0' y '4'
    if (numero < '0' || numero > '4') return;

    // Comprobar el tipo de dato solicitado
    if (dato != 'A' && dato != 'G' && dato != 'M') return;

    // Convertir el carácter, por ejemplo '2', en el número 2
    int numRegistro = numero - '0';

    sendTelemetria(numRegistro, dato);
}
