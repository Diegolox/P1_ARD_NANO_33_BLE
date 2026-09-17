#include <Arduino.h>
#include <Wire.h>
#include "hal/I2C.h"
#include "hal/uart.h"

#define DIRECCION_ESP32 0x08

void setup()
{
    initSerial();
    initI2C();
}

void loop()
{
    char enviado = '0';
    escribirI2C(DIRECCION_ESP32, uint8_t(enviado));
    delay(500);
    
    char recibido = char(leerI2C(DIRECCION_ESP32));
    Serial.println(recibido);
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

