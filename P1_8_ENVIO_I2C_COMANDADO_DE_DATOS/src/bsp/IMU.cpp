/**
 * @file IMU.cpp
 * @brief Inicialización y lectura de los sensores de la IMU.
 */
#include <Arduino_LSM9DS1.h>
#include "bsp/IMU.h"

/**
 * @brief Inicializa la IMU mediante la biblioteca Arduino_LSM9DS1.
 * @return true si la inicialización tiene éxito; false en caso contrario.
 */
bool initIMU()
{
    return IMU.begin();
}

/**
 * @brief Lee los tres ejes del acelerómetro cuando hay datos disponibles.
 * @param[out] aceleracion Vector donde se guardan los valores X, Y y Z, en g.
 * @return true si había una muestra disponible; false en caso contrario.
 * @note Si no hay muestra, el vector no se modifica.
 */
bool leerAcelerometro(Vector3D &aceleracion)
{
    if (!IMU.accelerationAvailable())
    {
        return false;
    }

    IMU.readAcceleration(aceleracion.x, aceleracion.y, aceleracion.z);

    return true;
}

/**
 * @brief Lee los tres ejes del giroscopio cuando hay datos disponibles.
 * @param[out] giroscopio Vector donde se guardan los valores X, Y y Z, en °/s.
 * @return true si había una muestra disponible; false en caso contrario.
 * @note Si no hay muestra, el vector no se modifica.
 */
bool leerGiroscopo(Vector3D &giroscopio)
{
    if (!IMU.gyroscopeAvailable())
    {
        return false;
    }

    IMU.readGyroscope(giroscopio.x, giroscopio.y, giroscopio.z);

    return true;
}

/**
 * @brief Lee los tres ejes del magnetómetro cuando hay datos disponibles.
 * @param[out] campoMagnetico Vector donde se guardan los valores X, Y y Z, en µT.
 * @return true si había una muestra disponible; false en caso contrario.
 * @note Si no hay muestra, el vector no se modifica.
 */
bool leerMagnetometro(Vector3D &campoMagnetico)
{
    if (!IMU.magneticFieldAvailable())
    {
        return false;
    }

    IMU.readMagneticField(campoMagnetico.x, campoMagnetico.y, campoMagnetico.z);

    return true;
}
