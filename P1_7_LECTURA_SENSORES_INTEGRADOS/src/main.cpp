#include <Arduino.h>
#include <Arduino_LSM9DS1.h>

void setup()
{
    Serial.begin(115200);

    while (!Serial);

    if (!IMU.begin())
    {
        Serial.println("Error al iniciar la IMU");

        while (true);
    }

    Serial.println("IMU inicializada correctamente");
}

void loop()
{
    float accX, accY, accZ;
    float gyroX, gyroY, gyroZ;
    float magX, magY, magZ;

    // Leer acelerómetro
    if (IMU.accelerationAvailable())
    {
        IMU.readAcceleration(accX, accY, accZ);

        Serial.print("ACC [g]: ");
        Serial.print(accX);
        Serial.print("; ");
        Serial.print(accY);
        Serial.print("; ");
        Serial.println(accZ);
    }

    // Leer giroscopio
    if (IMU.gyroscopeAvailable())
    {
        IMU.readGyroscope(gyroX, gyroY, gyroZ);

        Serial.print("GYRO [grados/s]: ");
        Serial.print(gyroX);
        Serial.print("; ");
        Serial.print(gyroY);
        Serial.print("; ");
        Serial.println(gyroZ);
    }

    // Leer magnetómetro
    if (IMU.magneticFieldAvailable())
    {
        IMU.readMagneticField(magX, magY, magZ);

        Serial.print("MAG [uT]: ");
        Serial.print(magX);
        Serial.print("; ");
        Serial.print(magY);
        Serial.print("; ");
        Serial.println(magZ);
    }

    Serial.println("----------------------------");
    delay(500);
}