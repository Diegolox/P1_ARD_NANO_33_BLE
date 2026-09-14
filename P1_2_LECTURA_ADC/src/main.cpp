#include <Arduino.h>

#define ADC_PIN A0
#define T 1000

int tension = 0;

int leerTension(int pin);

void setup() {
  Serial.begin(115200);
}

void loop() {
  tension = leerTension(ADC_PIN);

  char buffer[40];

  snprintf(buffer, sizeof(buffer), "La tension del ADC es: %d mV", tension);

  Serial.println(buffer);

  delay(T);
}

int leerTension(int pin) {
  return (analogRead(pin) * 3300L) / 1023;
}