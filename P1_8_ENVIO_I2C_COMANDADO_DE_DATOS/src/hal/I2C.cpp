/**
 * @file I2C.cpp
 * @brief Comunicación I2C como maestro o esclavo y gestión de comandos y respuestas.
 */
#include <Wire.h>
#include "hal/i2c.h"

/** @brief Indica si hay un comando I2C de dos caracteres pendiente de leer. */
volatile bool comandoDisponible = 0;
/** @brief Almacena el último comando recibido y su terminador nulo. */
char BufferI2C[10];
/** @brief Respuesta de tamaño fijo que envía el esclavo al maestro. */
char respuestaI2C[32] = "ESPERA";


//----------INICIALIZACION----------
/** @brief Inicia el bus I2C del Arduino en modo maestro. */
void initI2C(){

    // Sin dirección, el Nano funciona como maestro
    Wire.begin();
}

/**
 * @brief Inicia el bus I2C en modo esclavo y registra las funciones de respuesta.
 * @param direccion Dirección I2C asignada al esclavo.
 */
void initI2C(uint8_t direccion){

    Wire.begin(direccion);
    Wire.onRequest(enviarRespuestaI2C);
    Wire.onReceive(recibirI2C); // se ejecuta cuando llega un mensaje por I2C

}

//----------MAESTRO----------
/**
 * @brief Envía un byte a un dispositivo I2C.
 * @param direccion Dirección I2C del destinatario.
 * @param dato Byte que se envía.
 * @return true si la transmisión finaliza sin error; false en caso contrario.
 */
bool escribirI2C(uint8_t direccion, uint8_t dato){

    Wire.beginTransmission(direccion);
    Wire.write(dato);

    return Wire.endTransmission() == 0;
}

/**
 * @brief Envía el contenido de una cadena de caracteres por I2C.
 * @param direccion Dirección I2C del destinatario.
 * @param texto Cadena terminada en nulo que se envía sin el terminador.
 * @return true si la transmisión finaliza sin error; false en caso contrario.
 */
bool escribirI2C(uint8_t direccion, const char* texto){

    Wire.beginTransmission(direccion);
    Wire.print(texto);

    return Wire.endTransmission() == 0;
}

/**
 * @brief Solicita y lee un byte de un esclavo I2C.
 * @param direccion Dirección I2C del esclavo.
 * @return Valor del byte recibido (0 a 255), o -1 si no se recibe ninguno.
 */
int leerEsclavoI2C(uint8_t direccion){

    // Solicita un byte y comprueba si ha llegado
    if (Wire.requestFrom(direccion, 1) > 0)
    {
        return Wire.read();
    }

    return -1;
}

//----------ESCLAVO----------
/**
 * @brief Recibe un comando I2C de dos caracteres y lo deja pendiente de procesar.
 * @details Se utiliza como función de recepción registrada con Wire.onReceive().
 *          El primer carácter identifica el registro y el segundo el sensor.
 * @param numeroBytes Número de bytes indicado por la biblioteca Wire.
 */
void recibirI2C(int numeroBytes){ // Wire indica el número de bytes recibidos.
    if (numeroBytes == 2 && Wire.available() >= 2) {
        BufferI2C[0] = Wire.read();  // Número del registro
        BufferI2C[1] = Wire.read();  // A, G o M
        BufferI2C[2] = '\0';         // Final de cadena

        comandoDisponible = true;
    }
}


/**
 * @brief Obtiene el último comando recibido y limpia su indicador de disponibilidad.
 * @return Comando de dos caracteres, o una cadena vacía si no hay uno pendiente.
 */
String leerComandoI2C(){
    if (!comandoDisponible) {
        return "";
    }

    String comando = BufferI2C;
    comandoDisponible = false;

    return comando;
}

/**
 * @brief Copia una cadena al búfer de respuesta I2C del esclavo.
 * @details Se conservan como máximo 31 caracteres y se completa con ceros
 *          el resto del búfer de 32 bytes.
 * @param texto Cadena terminada en nulo que se prepara para el envío.
 */
void prepararRespuestaI2C(const char* texto) {
    char copia[32] = {};
    strncpy(copia, texto, sizeof(copia) - 1);

    noInterrupts();
    memcpy(respuestaI2C, copia, sizeof(copia));
    interrupts();
}

/**
 * @brief Envía los 32 bytes del búfer de respuesta cuando el maestro los solicita.
 * @details Función registrada como callback mediante Wire.onRequest().
 */
void enviarRespuestaI2C() {
    Wire.write((const uint8_t*)respuestaI2C, sizeof(respuestaI2C));
}
