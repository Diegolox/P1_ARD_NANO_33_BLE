#include <Arduino.h>
#include "hal/timer.h"
#include "hal/adc.h"
#include "hal/pwm.h"
#include "config.h"

#define PERIODO_TIMER_HW 1000000 // f reloj 1 MHz 


void setup()
{
    Serial.begin(115200);

    while (!Serial) {
        // Espera a que el ordenador abra el puerto serie
    }
}

void loop()
{
    if (Serial.available() > 0)
    {
        String mensaje = Serial.readStringUntil('\n');

        Serial.print("Arduino ha recibido: ");
        Serial.println(mensaje);
    }
}



/*

void setup()
{
  Serial.begin(115200);
  iniciarTimer(PERIODO_TIMER_HW);
  inicializarADC(ADC_RESOLUTION);
  inicializarPWM(PWM_PIN, FRECUENCIA_PWM);
}

void loop()
{
  if (hayInterrupcionTimer())
  {
    ADC_to_PWM();
  }
}

*/