#include <Arduino.h>

#define ADC_PIN A0
#define T 1000

int lecturaADC(int pin);

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.print("Valor ADC: ");
  Serial.println(lecturaADC(ADC_PIN));
  delay(T);
}

int lecturaADC(int pin) {
  return analogRead(pin);
}