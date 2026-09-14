#include <Arduino.h>

#define ADC_PIN A0
#define T 1000

float leerTension(int pin);

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.print("Tensión: ");
  Serial.println(leerTension(ADC_PIN));
  delay(T);
}

float leerTension(int pin) {
  return (analogRead(pin) * 3.3) / 1023;
}