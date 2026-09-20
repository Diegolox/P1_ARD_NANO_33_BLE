

https://github.com/user-attachments/assets/64fd90c6-5b77-41a2-89e9-29abb89e6d79

# P1_LAB

### ESTRUCTURA Y ORGANIZACIÓN DEL CÓDIGO

Tras realizar unas primeras pruebas con el **Arduino Nano 33 BLE** mediante **PlatformIO**, en las que se comprobó el funcionamiento del ADC y del LED integrado, en el tercer programa se estableció una estructura de código más limpia, modular y escalable.

<img src="docs/img/ESQUEMA_FICHEROS.svg" alt="Estructura de archivos del proyecto">

Como se observa en la imagen, los archivos de cabecera `.h` se encuentran en la carpeta `include`, mientras que sus implementaciones `.cpp` están en `src`.

La capa `hal` contiene las funciones relacionadas directamente con el hardware, como el ADC, el PWM, los temporizadores y los periféricos de comunicación. Por otro lado, la capa `app` contiene la lógica de más alto nivel, como la máquina de estados (MEF), interpretación de mensajes recibidos y funcionamiento general de la aplicación.

Por otro lado, `config.h` agrupa los pines que se utilizan, variables globales y otras constantes de interñes.

Y `main.cpp` se encarga de inicializar los diferentes módulos y ejecutar la aplicación a alto nivel.

Esta organización permite obtener un código más comprensible, mantenible y escalable.

### LECTURA DEL ADC
Se ha realizado la lectura del ADC con la función `analogRead` de Arduino. El código únicamente llama de forma periódica a esta función y calcula cuantos milivoltios equivalen la lectura del adc. Para este caso el ADC estaba configurado en 9 bit, de forma que si lee 1023 la tensión en el pin será de 3V3.


<p align="center">
  <video
    src="https://github.com/user-attachments/assets/f342f998-d296-4981-8266-427102643efc"
    controls
    width="75%">
  </video>
</p>

Se muestra en el video cómo al mover el potenciómetro se actualiza en el terminal la tensión leída.

### TEMPORIZADOR HARDWARE

### SALIDA PWM A PARTIR DEL ADC
