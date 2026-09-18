#include <Arduino.h>
#include <app/telemetria.h>
#include <bsp/IMU.h>
#include <hal/I2C.h>

Vector3D aceleracion;
Vector3D giroscopo;
Vector3D magnetometro;



float lecturasIMU[5][9];

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

void senIMU_I2C(uint8_t direccion){ // mandar por I2C
  sendMag_I2C(direccion);
  sendGir_I2C(direccion);
  sendAce_I2C(direccion);
}

void sendMag_I2C(uint8_t direccion){
  char buffer[120];
  leerMagnetometro(magnetometro);
  snprintf(buffer, sizeof(buffer), "Mag X:%.4f, Y:%.4f, Z:%.4f", magnetometro.x, magnetometro.y, magnetometro.z);
  escribirI2C(direccion, buffer); // deberíamos quitar esta función
}

void sendGir_I2C(uint8_t direccion){
  char buffer[120];
  leerGiroscopo(giroscopo);
  snprintf(buffer, sizeof(buffer), "Gir X:%.4f, Y:%.4f, Z:%.4f", giroscopo.x, giroscopo.y, giroscopo.z);
  escribirI2C(direccion, buffer); // deberíamos quitar esta función
}

void sendAce_I2C(uint8_t direccion){
  char buffer[120];
  leerAcelerometro(aceleracion);
  snprintf(buffer, sizeof(buffer), "Ace X: %.4f, Y: %.4f, Z: %.4f", aceleracion.x, aceleracion.y, aceleracion.z);
  escribirI2C(direccion, buffer); // deberíamos quitar esta función
}

void guardarPaqueteIMU(){
  for(int i = 0; i <5; i++){
  leerAcelerometro(aceleracion);
  leerGiroscopo(giroscopo);
  leerMagnetometro(magnetometro);

  lecturasIMU[i][0] = aceleracion.x;
  lecturasIMU[i][1] = aceleracion.y;
  lecturasIMU[i][2] = aceleracion.z;

  lecturasIMU[i][3] = giroscopo.x;
  lecturasIMU[i][4] = giroscopo.y;
  lecturasIMU[i][5] = giroscopo.z;

  lecturasIMU[i][6] = magnetometro.x;
  lecturasIMU[i][7] = magnetometro.y;
  lecturasIMU[i][8] = magnetometro.z;
  delay(200); // Se podría hacer de otra forma pero esto es simple y cumple el propósito
  }
}

void enviarPaqueteIMU(uint8_t direccion){
  char buffer[100];
  for(int i = 0; i <5; i++){

    // envia aceleracion i
    snprintf(buffer, sizeof(buffer), "A%d:%2.f;%2.f;%2.f;", i, lecturasIMU[i][0], lecturasIMU[i][1], lecturasIMU[i][2]);
    escribirI2C(direccion, buffer);

    // envia giroscopo i
    snprintf(buffer, sizeof(buffer), "G%d:%2.f;%2.f;%2.f;", i, lecturasIMU[i][3], lecturasIMU[i][4], lecturasIMU[i][5]);
    escribirI2C(direccion, buffer);

    // envia magnetometro i
    snprintf(buffer, sizeof(buffer), "M%d:%2.f;%2.f;%2.f;", i, lecturasIMU[i][6], lecturasIMU[i][7], lecturasIMU[i][8]);
    escribirI2C(direccion, buffer);
  }
}