#include <Arduino.h>
#include <app/app.h>
#include <bsp/IMU.h>

Vector3D aceleracion;
Vector3D giroscopo;
Vector3D magnetometro;

void printIMU(){

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