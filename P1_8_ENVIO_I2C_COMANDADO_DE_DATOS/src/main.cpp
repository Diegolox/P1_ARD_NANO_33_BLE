#include <Arduino.h>
#include <Arduino_LSM9DS1.h>
#include <app/telemetria.h>
#include <app/protocolo.h>
#include <bsp/IMU.h>
#include <hal/I2C.h>

uint8_t numeroMuestras = 0;
unsigned long proximaMuestra;

void setup() {
    initIMU();
    initI2C(0x33);              // Nano como esclavo
    proximaMuestra = millis() + 200;
}

void loop() {
    if (numeroMuestras < 5 && millis() >= proximaMuestra) {
        guardarMuestraIMU(numeroMuestras);
        numeroMuestras++;
        proximaMuestra += 200;
    }

    procesarComandoI2C_IMU();
}