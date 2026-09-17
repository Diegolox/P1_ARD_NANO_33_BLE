#include <Arduino_LSM9DS1.h>
#include "bsp/IMU.h"

bool initIMU()
{
    return IMU.begin();
}

bool leerAcelerometro(Vector3D &aceleracion)
{
    if (!IMU.accelerationAvailable())
    {
        return false;
    }

    IMU.readAcceleration(aceleracion.x, aceleracion.y, aceleracion.z);

    return true;
}

bool leerGiroscopo(Vector3D &giroscopio)
{
    if (!IMU.gyroscopeAvailable())
    {
        return false;
    }

    IMU.readGyroscope(giroscopio.x, giroscopio.y, giroscopio.z);

    return true;
}

bool leerMagnetometro(Vector3D &campoMagnetico)
{
    if (!IMU.magneticFieldAvailable())
    {
        return false;
    }

    IMU.readMagneticField(campoMagnetico.x, campoMagnetico.y, campoMagnetico.z);

    return true;
}