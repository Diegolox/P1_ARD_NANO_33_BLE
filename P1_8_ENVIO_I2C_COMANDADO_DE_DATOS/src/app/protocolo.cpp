/**
 * @file protocolo.cpp
 * @brief Interpretación de comandos recibidos por Serial y por I2C.
 */
#include <Arduino.h>
#include "app/telemetria.h"
#include "hal/uart.h"
#include "hal/adc.h"
#include "hal/pwm.h"
#include "hal/timer.h"
#include "hal/I2C.h"

/**
 * @brief Procesa un comando recibido por el puerto serie.
 * @details Reconoce STOP, ADC, ADC(x) y PWM(x). STOP detiene el temporizador
 *          y pone la PWM a cero. ADC imprime una lectura y detiene el temporizador.
 *          ADC(x) inicia un temporizador con x segundos de periodo; PWM(x)
 *          ajusta el ciclo de trabajo a uno de diez niveles, de 0 a 9.
 * @note La conversión de x se realiza con String::toInt(); no se valida
 *       expresamente si el contenido entre paréntesis es numérico.
 */
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

/**
 * @brief Interpreta el último comando I2C dirigido a los registros de la IMU.
 * @details Acepta dos caracteres: un índice de '0' a '4' seguido de 'A'
 *          (acelerómetro), 'G' (giroscopio) o 'M' (magnetómetro).
 *          Si el comando es válido, prepara la respuesta con sendTelemetria().
 *          Los comandos ausentes o inválidos se descartan sin respuesta nueva.
 */
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
