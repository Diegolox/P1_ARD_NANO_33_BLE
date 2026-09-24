/**
 * @file telemetria.cpp
 * @brief Almacenamiento de muestras de la IMU y preparación de su telemetría.
 */
#include <Arduino.h>
#include <app/telemetria.h>
#include <bsp/IMU.h>
#include <hal/I2C.h>

/** @brief Último vector de aceleración utilizado por este módulo. */
Vector3D aceleracion;
/** @brief Último vector de velocidad angular utilizado por este módulo. */
Vector3D giroscopo;
/** @brief Último vector de campo magnético utilizado por este módulo. */
Vector3D magnetometro;

/** @brief Cinco registros disponibles para almacenar muestras de la IMU. */
IMU bufferIMU[5]; // se crea un buffer para guardar 5 muestras del IMU



/**
 * @brief Lee los tres sensores de la IMU y muestra sus ejes por Serial.
 * @note No comprueba el resultado de las funciones de lectura; si no hay
 *       muestra nueva, se imprimen los valores que conserve cada vector.
 */
void printIMU(){ // mandar por uart
  char buffer[120];
  leerMagnetometro(magnetometro);
  snprintf(buffer, sizeof(buffer), "Magnetómetro X: %.4f, Y: %.4f, Z: %.4f", magnetometro.x, magnetometro.y, magnetometro.z);
  Serial.print(buffer);

  leerGiroscopo(giroscopo);
  snprintf(buffer, sizeof(buffer), " | Giróscopo X: %.4f, Y: %.4f, Z: %.4f", giroscopo.x, giroscopo.y, giroscopo.z);
  Serial.print(buffer);

  leerAcelerometro(aceleracion);
  snprintf(buffer, sizeof(buffer), " | Aceleración X: %.4f, Y: %.4f, Z: %.4f", aceleracion.x, aceleracion.y, aceleracion.z);
  Serial.println(buffer);
}

/**
 * @brief Prepara una respuesta I2C con los datos de un registro de la IMU.
 * @param numRegistro Índice del registro solicitado, de 0 a 4.
 * @param dato Sensor solicitado: 'A' (aceleración), 'G' (giroscopio)
 *             o 'M' (campo magnético).
 * @pre numRegistro debe estar entre 0 y 4; esta función no valida el índice.
 * @note Ante un tipo de sensor desconocido, conserva la respuesta anterior.
 */
void sendTelemetria(int numRegistro, char dato){
  // crea el buffer char que recopila del array de struct los datos
  char buffer[32];

  if(dato == 'A'){ // coge aceleracion
    snprintf(buffer, sizeof(buffer), "A:%.2f,%.2f,%.2f", bufferIMU[numRegistro].ax, bufferIMU[numRegistro].ay, bufferIMU[numRegistro].az);
  }

  else if(dato == 'G'){ // coge giroscopo
    snprintf(buffer, sizeof(buffer), "G:%.2f,%.2f,%.2f", bufferIMU[numRegistro].gx, bufferIMU[numRegistro].gy, bufferIMU[numRegistro].gz);
  }

  else if(dato == 'M'){ // coge magnetometro
    snprintf(buffer, sizeof(buffer), "M:%.2f,%.2f,%.2f", bufferIMU[numRegistro].mx, bufferIMU[numRegistro].my, bufferIMU[numRegistro].mz);
  }
  else return;

  prepararRespuestaI2C(buffer);
}

/**
 * @brief Lee la IMU y copia los valores en una posición del búfer de muestras.
 * @param numRegistro Índice del registro que se actualiza, de 0 a 4.
 * @note Ignora índices fuera del rango. No comprueba si hay datos nuevos
 *       antes de copiar los valores conservados en los vectores.
 */
void guardarMuestraIMU(int numRegistro) {

    // Comprobar que el registro está entre 0 y 4
    if (numRegistro < 0 || numRegistro >= 5) {
        return;
    }

    // Leer los sensores
    leerAcelerometro(aceleracion);
    leerGiroscopo(giroscopo);
    leerMagnetometro(magnetometro);

    // Guardar acelerómetro
    bufferIMU[numRegistro].ax = aceleracion.x;
    bufferIMU[numRegistro].ay = aceleracion.y;
    bufferIMU[numRegistro].az = aceleracion.z;

    // Guardar giroscopio
    bufferIMU[numRegistro].gx = giroscopo.x;
    bufferIMU[numRegistro].gy = giroscopo.y;
    bufferIMU[numRegistro].gz = giroscopo.z;

    // Guardar magnetómetro
    bufferIMU[numRegistro].mx = magnetometro.x;
    bufferIMU[numRegistro].my = magnetometro.y;
    bufferIMU[numRegistro].mz = magnetometro.z;
}
