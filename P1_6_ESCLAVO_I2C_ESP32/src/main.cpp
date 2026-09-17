#include <Arduino.h>
#include <Wire.h>

#define DIRECCION_I2C 0x08
#define SDA_PIN 21
#define SCL_PIN 22
#define LED_PIN LED_BUILTIN

volatile int comando = -1;

// Se ejecuta automáticamente cuando llegan datos del maestro
void recibirI2C(int cantidad)
{
    if (Wire.available())
    {
        comando = Wire.read();
    }
}

void setup()
{
    Serial.begin(115200);

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    // Configura la función de recepción
    Wire.onReceive(recibirI2C);

    // Inicia el ESP32 como esclavo I2C
    Wire.begin(
        (uint8_t)DIRECCION_I2C,
        SDA_PIN,
        SCL_PIN,
        100000
    );
}

void loop()
{
    if (comando == 1)
    {
        digitalWrite(LED_PIN, HIGH);
        comando = -1;
    }
    else if (comando == 0)
    {
        digitalWrite(LED_PIN, LOW);
        comando = -1;
    }
}