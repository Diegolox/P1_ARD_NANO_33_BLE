#include <Arduino.h>
#include "hal/uart.h"
#include "hal/adc.h"
#include "hal/pwm.h"
#include "hal/timer.h"

void procesarComando()
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