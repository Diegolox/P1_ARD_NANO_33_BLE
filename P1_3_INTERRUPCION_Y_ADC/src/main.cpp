#include <Arduino.h>

//Constantes globales
#define ADC_PIN A0
#define T 1000

// Variables globales
float tension = 0.0;

// Prototipos de funciones
float leerTension(int pin);

void setup() {
  Serial.begin(115200);
}

void loop() {
  tension = leerTension(ADC_PIN);
  char buffer[40];
  sprintf(buffer, "La tensión del adc es: %s V", tension);
  Serial.println(buffer);
  delay(T);
}

float leerTension(int pin) {
  return (analogRead(pin) * 3.3) / 1023;
}