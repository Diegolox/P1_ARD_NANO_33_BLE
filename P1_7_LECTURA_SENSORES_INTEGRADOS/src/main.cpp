#include <Arduino.h>
#include <Arduino_LSM9DS1.h>
#include <app/telemetria.h>
#include <bsp/IMU.h>

void setup()
{
  initIMU();
}

void loop()
{
  printIMU();
  delay(1000);
}