/**
 * @file protocolo.h
 * @brief Declaraciones para interpretar comandos recibidos por Serial e I2C.
 */
#ifndef PROTOCOLO_H
#define PROTOCOLO_H


/**
 * @brief Procesa los comandos serie STOP, ADC, ADC(x) y PWM(x).
 * @details Permite detener el temporizador, leer el ADC, iniciar lecturas
 *          periódicas o ajustar el ciclo de trabajo de la PWM.
 */
void procesarComandoSerial();
/**
 * @brief Procesa un comando I2C de consulta de un registro de la IMU.
 * @details Acepta un índice de '0' a '4' seguido de 'A', 'G' o 'M'.
 *          Si es válido, prepara la respuesta I2C correspondiente.
 */
void procesarComandoI2C_IMU();


#endif
