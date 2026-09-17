#include <Arduino.h>
#include <app/telemetria.h>
#include <bsp/IMU.h>
#include <hal/I2C.h>

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

void senIMU_I2C(uint8_t direccion){
  sendMag_I2C(direccion);
  sendGir_I2C(direccion);
  sendAce_I2C(direccion);
}

void sendMag_I2C(uint8_t direccion){
  char buffer[120];
  leerMagnetometro(magnetometro);
  snprintf(buffer, sizeof(buffer), "Mag X:%.4f, Y:%.4f, Z:%.4f", magnetometro.x, magnetometro.y, magnetometro.z);
  escribirI2C(direccion, buffer);
}

void sendGir_I2C(uint8_t direccion){
  char buffer[120];
  leerGiroscopo(giroscopo);
  snprintf(buffer, sizeof(buffer), "Gir X:%.4f, Y:%.4f, Z:%.4f", giroscopo.x, giroscopo.y, giroscopo.z);
  escribirI2C(direccion, buffer);
}

void sendAce_I2C(uint8_t direccion){
  char buffer[120];
  leerAcelerometro(aceleracion);
  snprintf(buffer, sizeof(buffer), "Ace X: %.4f, Y: %.4f, Z: %.4f", aceleracion.x, aceleracion.y, aceleracion.z);
  escribirI2C(direccion, buffer);
}