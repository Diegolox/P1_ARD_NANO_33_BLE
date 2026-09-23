#include <Arduino.h>
#include <app/telemetria.h>
#include <bsp/IMU.h>
#include <hal/I2C.h>

Vector3D aceleracion;
Vector3D giroscopo;
Vector3D magnetometro;

IMU bufferIMU[5]; // se crea un buffer para guardar 5 muestras del IMU



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