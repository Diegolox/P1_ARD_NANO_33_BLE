# P1_LAB — Arduino Nano 33 BLE

Prácticas de microcontroladores realizadas con **PlatformIO** y el **Arduino Nano 33 BLE**. Cada carpeta `P1_x_...` es un proyecto independiente: desde el parpadeo de un LED y la lectura del ADC hasta la comunicación entre un Nano y un ESP32 para consultar muestras de la IMU.

## Proyectos

| Carpeta | Qué hace el programa principal |
| --- | --- |
| [`P1_1_BLINK_LED`](P1_1_BLINK_LED/) | Enciende y apaga el LED del pin 13 cada segundo. |
| [`P1_2_LECTURA_ADC`](P1_2_LECTURA_ADC/) | Lee `A0`, convierte la lectura a milivoltios y la muestra por `Serial` cada segundo. |
| [`P1_3_INTERRUPCION_Y_ADC`](P1_3_INTERRUPCION_Y_ADC/) | Usa una interrupción periódica de `TIMER3` para solicitar una lectura ADC cada 10 segundos. |
| [`P1_4_PWM_desde_ADC`](P1_4_PWM_desde_ADC/) | Convierte la lectura de `A0` en el *duty cycle* de una salida PWM en `A1`, actualizada cada segundo. |
| [`P1_5_COMUNICACION_UART`](P1_5_COMUNICACION_UART/) | Recibe comandos por `Serial` para consultar el ADC, programar lecturas periódicas y ajustar la PWM. |
| [`P1_6_COMUNICACION_I2C`](P1_6_COMUNICACION_I2C/) + [`P1_6_ESCLAVO_I2C_ESP32`](P1_6_ESCLAVO_I2C_ESP32/) | El Nano actúa como maestro I²C y envía `0` o `1` al ESP32 esclavo para apagar o encender su LED. |
| [`P1_7_LECTURA_SENSORES_INTEGRADOS`](P1_7_LECTURA_SENSORES_INTEGRADOS/) | Lee acelerómetro, giróscopo y magnetómetro mediante `Arduino_LSM9DS1` e intenta mostrar las lecturas cada segundo. |
| [`P1_8_ENVIO_I2C_COMANDADO_DE_DATOS`](P1_8_ENVIO_I2C_COMANDADO_DE_DATOS/) + [`P1_8_ENVIO_COMANDO_ESP_MASTER`](P1_8_ENVIO_COMANDO_ESP_MASTER/) | El Nano guarda cinco muestras de la IMU y responde a las peticiones I²C de un ESP32 maestro. |

## Estructura y organización del código

Tras las primeras pruebas, el código se separó en archivos de cabecera dentro de `include/` e implementaciones dentro de `src/`. En `P1_3` los módulos ADC y temporizador todavía están en `lib/`; a partir de `P1_4` se usa la estructura por capas:

<img src="docs/img/ESQUEMA_FICHEROS.svg" alt="Esquema de la organización de archivos del proyecto" width="800">

- `hal/`: acceso a ADC, PWM, temporizador y comunicaciones UART/I²C.
- `bsp/`: adaptación de la IMU integrada, presente en las prácticas con sensores.
- `app/`: interpretación de comandos y lógica de telemetría.
- `config.h`: pines y constantes usadas por cada proyecto.
- `main.cpp`: inicialización y ciclo principal de la práctica correspondiente.

Las carpetas son **ejercicios sucesivos**, por lo que algunas conservan módulos de prácticas anteriores aunque su `main.cpp` ya no los utilice. La descripción de la tabla se refiere al programa que se ejecuta en cada carpeta.

## ADC, temporizador y PWM

En `P1_2` se lee el pin `A0` y se calcula la tensión con `lectura * 3300 / 1023`, tomando 3,3 V como referencia. El valor aparece en milivoltios en el monitor serie.

**[Vídeo: lectura del ADC](docs/vid/ADC_READ.mp4)**

En `P1_3` se configura `TIMER3` del nRF52840 con un contador de 1 MHz. La rutina de interrupción activa una bandera y el `loop()` realiza la lectura del ADC cuando detecta esa bandera. Así se evita imprimir por `Serial` dentro de la interrupción.

En `P1_4` el ADC se configura a 12 bits (`0–4095`) y se escala a un duty de `0–255`. La salida PWM de `A1` se genera con `mbed::PwmOut` a **7 kHz**; el temporizador actualiza el duty una vez por segundo.

**[Vídeo: PWM controlada desde el ADC](docs/vid/ADC_to_PWM.mp4)**

## Comandos por Serial

En `P1_5_COMUNICACION_UART`, el Nano recibe líneas terminadas en salto de línea a **115200 baudios**. El programa reconoce:

| Comando | Acción |
| --- | --- |
| `ADC` | Detiene el temporizador y envía una lectura actual del ADC. |
| `ADC(x)` | Configura una lectura periódica cada `x` segundos mediante `TIMER3` (`x` debe ser positivo). |
| `PWM(x)` | Ajusta el duty de `A1`, con `x` entre `0` y `9` (`0` = 0 %, `9` = 100 %). |
| `STOP` | Detiene el temporizador y fija la PWM a cero. |

Para detener el envío periódico hay que usar `STOP` o `ADC`: en el código actual, `ADC(0)` **no** llama a `stopTimer()`.

## I²C: Nano maestro y ESP32 esclavo

En la primera prueba I²C, el Nano envía alternativamente los bytes `0` y `1` cada 500 ms a la dirección **`0x08`**. El ESP32 recibe el byte con `Wire.onReceive()` y apaga o enciende su LED. En el ESP32 se usan **SDA = GPIO 21** y **SCL = GPIO 22**. Ambas placas deben compartir masa y las señales I²C deben trabajar a 3,3 V.

<img src="docs/img/FOTO_COMUNICACION_I2C_ESP_y_ARD.png" alt="Conexión I²C entre el ESP32 y el Arduino Nano 33 BLE" width="650">

## Lectura y consulta de la IMU

`P1_7` incorpora un módulo `bsp/IMU` para leer los tres ejes del acelerómetro, giróscopo y magnetómetro con `Arduino_LSM9DS1`. Su `loop()` llama a `printIMU()` una vez por segundo. **En esta versión falta inicializar `Serial` en `setup()`**, por lo que la impresión no queda preparada para verse de forma fiable en el monitor hasta añadir `Serial.begin(...)`.

La práctica `P1_8` separa los papeles de las placas:

| Placa y carpeta | Función |
| --- | --- |
| Nano, [`P1_8_ENVIO_I2C_COMANDADO_DE_DATOS`](P1_8_ENVIO_I2C_COMANDADO_DE_DATOS/) | Esclavo I²C `0x33`. Guarda cinco muestras de aceleración, giro y campo magnético, una cada 200 ms después de arrancar. |
| ESP32, [`P1_8_ENVIO_COMANDO_ESP_MASTER`](P1_8_ENVIO_COMANDO_ESP_MASTER/) | Maestro I²C. Lee un comando escrito por `Serial`, lo envía al Nano y solicita su respuesta. Utiliza GPIO 21/22 para SDA/SCL y GPIO 2 para el LED. |

El comando tiene **dos caracteres**: índice `0–4` seguido de `A` (acelerómetro), `G` (giróscopo) o `M` (magnetómetro). Por ejemplo, `2G` pide los tres ejes del giróscopo de la muestra 2. El Nano prepara una respuesta de texto como `G:0.12,0.34,0.56`; el ESP32 la imprime y enciende su LED durante un segundo. El maestro espera 10 ms entre el envío del comando y la solicitud de lectura.

Las cinco muestras se capturan **una sola vez al inicio**, no en un búfer que se actualice continuamente. Si se consulta antes de terminar la captura, pueden recibirse muestras aún no tomadas. Las funciones de lectura de la IMU devuelven si había datos disponibles, pero la aplicación actual no comprueba ese resultado al guardarlos.

**[Vídeo: petición de datos por I²C](docs/vid/PIDO_DATOS_I2C.mp4)**

## Cómo ejecutar una práctica

1. Abre en VS Code **la carpeta de la práctica concreta**, que contiene su propio `platformio.ini`.
2. Conecta y selecciona la placa correspondiente: `nano33ble` para el Arduino Nano 33 BLE y `upesy_wroom` para los ejemplos del ESP32.
3. Compila y carga el proyecto desde PlatformIO. Los proyectos con IMU (`P1_7` y el Nano de `P1_8`) declaran `Arduino_LSM9DS1` en `lib_deps`.
4. Cuando la práctica use `Serial`, abre el monitor a **115200 baudios**. Para enviar los comandos de `P1_5` o del ESP32 de `P1_8`, escribe el comando y pulsa Enter.

**[Vídeo: primera prueba del LED](docs/vid/BLINK_LED.mp4)**
