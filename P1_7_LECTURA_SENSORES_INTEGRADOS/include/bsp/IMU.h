#ifndef IMU_H
#define IMU_H

struct Vector3D
{
    float x;
    float y;
    float z;
};

bool initIMU();

bool leerAcelerometro(Vector3D &aceleracion);

bool leerGiroscopo(Vector3D &giroscopio);

bool leerMagnetometro(Vector3D &campoMagnetico);



#endif