#include <Arduino.h>
#include <Wire.h>

#define DIRECCION_ESP32 0x08

void setup()
{
    Serial.begin(115200);

    // Nano configurado como maestro
    Wire.begin();
}

void loop()
{
    // Solicita 4 bytes al ESP32
    Wire.requestFrom(DIRECCION_ESP32, 4);

    while (Wire.available())
    {
        char dato = Wire.read();
        Serial.print(dato);
    }

    Serial.println();
    delay(1000);
}




/*
#include <Arduino.h>
#include "hal/timer.h"
#include "hal/adc.h"
#include "hal/pwm.h"
#include "hal/uart.h"
#include "app/protocolo.h"
#include "config.h"

#define PERIODO_TIMER_HW 1000000 // f reloj 1 MHz 


void setup()
{
  initSerial();
  setTimer(PERIODO_TIMER_HW);
  stopTimer();
  initADC(ADC_RESOLUTION);
  initPWM(PWM_PIN, FRECUENCIA_PWM);
}

void loop()
{
  procesarComandoSerial();
  if(hayInterrupcionTimer())
  {
    printADC();
  }
}

*/

