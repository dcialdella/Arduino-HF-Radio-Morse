# Arduino HF Radio Morse Keyer

Codigo para Arduino que actua como interfaz Morse entre una computadora y un transceptor HF (probado con Xiegu G90).

## Descripcion

El Arduino recibe caracteres por puerto serie y genera codigo Morse mediante:
- Sonido por buzzer (para monitoreo audible)
- Señal digital que activa un relay para keyear la radio

## Conexiones

```
                    Arduino Uno
                 +---------------+
                 |               |
                 |           +5V |----+
                 |               |    |
                 |            GND |----+-- GND del relay
                 |               |    |
                 |            Pin 8 |----+-- Buzzer (+)
                 |               |    |
                 |           Pin 10 |----+-- Relay IN1
                 |               |    |
                 |            Pin 3 |----+-- Boton CQ (otro lado a +5V)
                 |               |
                 +---------------+

                    Relay Module
                 +---------------+
                 |               |
                 |           VCC |----+-- +5V Arduino
                 |           GND |----+-- GND Arduino
                 |           IN1 |----+-- Pin 10 Arduino
                 |               |
                 |       NO (NC) |----+-- Keyer Tip (Radio)
                 |       COM (C) |----+-- Keyer Sleeve/GND (Radio)
                 +---------------+

                    Xiegu G90
                 +---------------+
                 |               |
                 |        KEYER + |----+-- Relay NO
                 |        KEYER - |----+-- Relay COM (GND)
                 |               |
                 +---------------+
```

## Pines

| Pin Arduino | Funcion          | Conexion                |
|-------------|------------------|-------------------------|
| 8           | Buzzer           | Altavoz/Piezo           |
| 10          | Relay Keying     | IN1 del modulo relay    |
| 3           | Boton CQ         | Boton (pull-up interno) |
| GND         | Tierra           | GND relay y radio       |

## Uso

1. Cargar el codigo en el Arduino
2. Abrir el monitor serie (9600 baudios)
3. Escribir texto y enviar - el Arduino genera Morse automaticamente
4. Presionar el boton en pin 3 para enviar CQ automatico (CQ CQ CQ EA4HUK...)
5. Enviar `!` por serie tambien dispara CQ

## Timing

- Punto (dot): 1x unidad de tiempo
- Raya (dash): 3x unidad de tiempo
- Espacio entre elementos: 1x unidad
- Espacio entre letras: 3x unidad
- Espacio entre palabras: 7x unidad

La variable `timeUnit` (default 60ms) controla la velocidad. Ajustar segun necesidad:
- 50ms = ~24 WPM
- 60ms = ~20 WPM
- 100ms = ~12 WPM

## Caracteres Soportados

- Letras A-Z
- Numeros 0-9
- Espacio (pausa entre palabras)
- `!` dispara secuencia CQ automatica

## Autor

dac - dcialdella@gmail.com - EA4HUK
