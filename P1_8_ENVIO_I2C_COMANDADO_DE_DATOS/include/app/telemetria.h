/**
 * @file telemetria.h
 * @brief Declaraciones para mostrar, guardar y responder con datos de la IMU.
 */
#ifndef APP_H
#define APP_H

/**
 * @brief Muestra por Serial las últimas lecturas de los tres sensores de la IMU.
 * @note Si alguna lectura no está disponible, se conserva el valor anterior
 *       del vector correspondiente.
 */
void printIMU();

/**
 * @brief Prepara en el búfer I2C la lectura de un registro de la IMU.
 * @param numRegistro Índice de registro comprendido entre 0 y 4.
 * @param dato Sensor solicitado: 'A' (acelerómetro), 'G' (giroscopio)
 *             o 'M' (magnetómetro).
 * @pre numRegistro debe estar entre 0 y 4; la función no valida ese índice.
 */
void sendTelemetria(int numRegistro, char dato);

/**
 * @brief Guarda las lecturas actuales de la IMU en un registro del búfer.
 * @param numRegistro Índice del registro, entre 0 y 4.
 * @note Ignora los índices fuera del rango y conserva los valores previos
 *       de un sensor cuando no hay una nueva muestra disponible.
 */
void guardarMuestraIMU(int numRegistro);

#endif
