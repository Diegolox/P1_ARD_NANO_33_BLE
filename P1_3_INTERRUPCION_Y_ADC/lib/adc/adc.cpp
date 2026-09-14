#include "adc.h"
#include <Arduino.h>

void inicializarPWM(){
  actualizarPWM(PWM_PIN, PWM_init);
}

void inicializarADC(){
  analogReadResolution(ADC_RESOLUTION); // Resolución ADC n bits, en este caso 4095
}

int leerADC(int pin, int scale, int resolution) {
    return (analogRead(pin) * scale) / resolution;
}

void actualizarPWM(int pin, int dutty){
  analogWrite(pin, dutty);
}

void ADC_to_PWM(){
    int dutty = leerADC(ADC_PIN, 255L, ADC_MAX);
    if (dutty < 0) dutty = 0;
    if (dutty > PWM_MAX) dutty = PWM_MAX;
    actualizarPWM(PWM_PIN, dutty);

    char buffer[40];
    snprintf(buffer, sizeof(buffer), "El dutty de la PWM es: %d", dutty);
    Serial.println(buffer);
}