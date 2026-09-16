#include <Arduino.h>
#include "hal/uart.h"
#include "hal/adc.h"
#include "hal/pwm.h"

void procesarComando()
{
    String mensaje = leerSerial();

    if (mensaje.length() == 0) //no hago nada
        return;

    if (mensaje == "ADC") //devuelve lectura ADC actual
    {
        printADC();
    }

    if (mensaje.startsWith("ADC(") && mensaje.endsWith(")")) //devuelve cada x segundos lectura ADC
    {
        int periodo = mensaje.substring(4, mensaje.length() - 1).toInt();
        //CONFIGURAR ADC PERIODICAMENTE!!!
        printADC();
    }

    if (mensaje.startsWith("PWM(") && mensaje.endsWith(")"))
    {
        int dutty = mensaje.substring(4, mensaje.length() - 1).toInt();

        if (dutty <= 0) dutty = 0;
        if (dutty >= 9) dutty = 9;
        actualizarPWM(255*dutty/9);
    }

}