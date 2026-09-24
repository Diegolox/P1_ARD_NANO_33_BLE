/**
 * @file IMU.h
 * @brief Tipos de datos y funciones de lectura de la IMU.
 */
#ifndef IMU_H
#define IMU_H

/** @brief Vector de tres componentes utilizado para las lecturas de sensores. */
struct Vector3D
{
    /** @brief Componente del eje X. */
    float x;
    /** @brief Componente del eje Y. */
    float y;
    /** @brief Componente del eje Z. */
    float z;
};

/**
 * @brief Registro de una muestra de acelerómetro, giroscopio y magnetómetro.
 * @details ax, ay y az se expresan en g; gx, gy y gz en °/s;
 *          mx, my y mz en µT.
 */
struct IMU
{
    float ax, ay, az;
    float gx, gy, gz;
    float mx, my, mz;

};

/**
 * @brief Inicializa la IMU.
 * @return true si la inicialización tiene éxito; false en caso contrario.
 */
bool initIMU();

/**
 * @brief Lee la aceleración de los tres ejes si hay una muestra disponible.
 * @param[out] aceleracion Vector de salida en g.
 * @return true si se ha leído una muestra; false si no había datos disponibles.
 * @note Si devuelve false, el vector no se modifica.
 */
bool leerAcelerometro(Vector3D &aceleracion);

/**
 * @brief Lee la velocidad angular de los tres ejes si hay una muestra disponible.
 * @param[out] giroscopio Vector de salida en °/s.
 * @return true si se ha leído una muestra; false si no había datos disponibles.
 * @note Si devuelve false, el vector no se modifica.
 */
bool leerGiroscopo(Vector3D &giroscopio);

/**
 * @brief Lee el campo magnético de los tres ejes si hay una muestra disponible.
 * @param[out] campoMagnetico Vector de salida en µT.
 * @return true si se ha leído una muestra; false si no había datos disponibles.
 * @note Si devuelve false, el vector no se modifica.
 */
bool leerMagnetometro(Vector3D &campoMagnetico);



#endif
