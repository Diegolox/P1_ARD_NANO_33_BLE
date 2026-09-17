#include <Arduino.h>
#include <Arduino_LSM9DS1.h>
#include <app/telemetria.h>
#include <bsp/IMU.h>
#include <hal/I2C.h>


void setup(){

  initI2C(0x33);
  initIMU();
}

void loop(){

// si leo un comando de lectura, L por ejemplo, empiezo rutina, si no, sigo con lo mío
  


}