/**
 * @file main.cpp
 * @brief Inicialización del Nano como esclavo I2C y captura de cinco muestras IMU.
 */
#include <Arduino.h>
#include <Arduino_LSM9DS1.h>
#include <app/telemetria.h>
#include <app/protocolo.h>
#include <bsp/IMU.h>
#include <hal/I2C.h>

/** @brief Número de muestras almacenadas desde el arranque, hasta cinco. */
uint8_t numeroMuestras = 0;
/** @brief Marca de tiempo en milisegundos para la siguiente captura. */
unsigned long proximaMuestra;

/**
 * @brief Inicializa la IMU y el esclavo I2C en la dirección 0x33.
 * @details Programa la primera captura 200 ms después de la inicialización.
 */
void setup() {
    initIMU();
    initI2C(0x33);              // Nano como esclavo
    proximaMuestra = millis() + 200;
}

/**
 * @brief Captura cinco muestras IMU y atiende las solicitudes recibidas por I2C.
 * @details Guarda una muestra cada 200 ms hasta completar los cinco registros.
 *          Después sigue procesando comandos I2C sin volver a tomar muestras.
 */
void loop() {
    if (numeroMuestras < 5 && millis() >= proximaMuestra) {
        guardarMuestraIMU(numeroMuestras);
        numeroMuestras++;
        proximaMuestra += 200;
    }

    procesarComandoI2C_IMU();
}
