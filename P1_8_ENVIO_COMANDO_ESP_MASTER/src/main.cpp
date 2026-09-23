#include <Arduino.h>
#include <Wire.h>

constexpr uint8_t DIRECCION_NANO = 0x33;
constexpr uint8_t LED = 2; // Ajustar si tu placa usa otro pin.

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); // SDA, SCL del ESP32.
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  Serial.println("Escribe un comando (por ejemplo 2G) y pulsa Enter.");
}

void loop() {
  static unsigned long apagarLedEn = 0;
  if (apagarLedEn && static_cast<long>(millis() - apagarLedEn) >= 0) {
    digitalWrite(LED, LOW);
    apagarLedEn = 0;
  }

  if (!Serial.available()) return;
  String comando = Serial.readStringUntil('\n');
  comando.trim();
  if (comando.length() != 2 || comando[0] < '0' || comando[0] > '4' ||
      (comando[1] != 'A' && comando[1] != 'G' && comando[1] != 'M')) {
    Serial.println("Comando valido: 0A a 4A, 0G a 4G, o 0M a 4M");
    return;
  }

  Wire.beginTransmission(DIRECCION_NANO);
  Wire.write(reinterpret_cast<const uint8_t*>(comando.c_str()), 2);
  if (Wire.endTransmission() != 0) {
    Serial.println("Error al enviar el comando I2C");
    return;
  }
  delay(10); // Permite al loop del Nano preparar la respuesta.

  char respuesta[33] = {};
  int recibidos = Wire.requestFrom(DIRECCION_NANO, static_cast<uint8_t>(32));
  for (int i = 0; i < recibidos && i < 32; ++i) respuesta[i] = Wire.read();
  while (Wire.available()) Wire.read();
  if (recibidos == 0) {
    Serial.println("No se recibio respuesta I2C");
    return;
  }
  Serial.println(respuesta);
  digitalWrite(LED, HIGH);
  apagarLedEn = millis() + 1000;
}
