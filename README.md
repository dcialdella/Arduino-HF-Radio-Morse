# Arduino HF Radio Morse Keyer

Código para Arduino que actúa como interfaz Morse entre una computadora y un transceptor HF (probado con Xiegu G90).

## Descripción

El Arduino recibe caracteres por puerto serie y genera código Morse mediante:
- **Sonido por buzzer** (para monitoreo audible)
- **Señal digital** que activa un relay para keyear la radio

## Diagrama de Conexiones

```
+----------------------------------------------------------------------+
|                            ARDUINO UNO                               |
|                                                                      |
|   +5V  o------------------------------> Relay VCC                    |
|                                                                      |
|   GND  o--------------------+--------> Relay GND                    |
|         |                    |--------> G90 KEYER -                  |
|         |                    |                                      |
|  Pin 8 o-------[Buzzer]-----+                                      |
|         |           (+)      |                                      |
|         |           (-)      |                                      |
|         |                    |                                      |
|  Pin 10 o------------------------> Relay IN1 (Keying signal)       |
|         |                    |                                      |
|  Pin 3  o---[CQ Button]--- GND                                    |
|             (INPUT_PULLUP,                                        |
|              no resistor needed)                                   |
+----------------------------------------------------------------------+
            |                  |                    |
            v                  v                    v
+----------------------------------------------------------------------+
|                           RELAY MODULE                               |
|                                                                      |
|  VCC o<--------------------- Arduino +5V                              |
|                                                                      |
|  GND o<--------------------- Arduino GND                              |
|                                                                      |
|  IN1 o<--------------------- Arduino Pin 10 (Active HIGH)            |
|                                                                      |
|  NO  o----------------------------------------------------> G90 KEYER +
|  (Normalmente Abierto)                                               |
|                                                                      |
|  COM o----------------------------------------------------> G90 KEYER -
|  (Común / GND)                                                       |
+----------------------------------------------------------------------+
            |                  |
            v                  v
+----------------------------------------------------------------------+
|                            XIEGU G90                                 |
|                                                                      |
|  KEYER + o<-------------------- Relay NO (Key line)                  |
|                                                                      |
|  KEYER - o<-------------------- Relay COM / Arduino GND              |
|                                                                      |
+----------------------------------------------------------------------+
```

### Módulo Relay 5V (Imagen de referencia)

![Relay 5V Module](relay-5v-arduino-mega.png)

**Especificaciones del Relay:**
- Voltaje de operación: 5V DC
- Señal de control: 3.3V / 5V compatible
- Pines: VCC, GND, IN1 (señal)
- Salidas: NO (Normalmente Abierto), COM (Común), NC (Normalmente Cerrado)

## Tabla de Pines

| Pin Arduino | Función         | Conexión                   | Modo           |
|-------------|-----------------|----------------------------|----------------|
| 8           | Buzzer          | Altavoz/Piezo (+)          | OUTPUT         |
| 10          | Relay Keying    | IN1 del módulo relay       | OUTPUT         |
| 3           | Botón CQ        | Botón a GND                | INPUT_PULLUP   |
| GND         | Tierra          | GND relay y radio          | -              |
| +5V         | Alimentación    | VCC del relay              | -              |

## Uso

1. Cargar el código `morse.cpp` en el Arduino usando el IDE de Arduino
2. Abrir el monitor serie (9600 baudios)
3. Escribir texto y enviar - el Arduino genera Morse automáticamente
4. Presionar el botón en pin 3 para enviar CQ automático (CQ CQ CQ EA4HUK...)
5. Enviar `!` por serie también dispara CQ

## Timing y Velocidad

Configuración de tiempos según estándar internacional Morse:

| Elemento                  | Unidades | Tiempo (60ms/unit) |
|---------------------------|----------|---------------------|
| Punto (dot)               | 1x       | 60ms               |
| Raya (dash)               | 3x       | 180ms              |
| Espacio entre elementos   | 1x       | 60ms               |
| Espacio entre letras      | 3x       | 180ms              |
| Espacio entre palabras    | 7x       | 420ms              |

La variable `timeUnit` (default 60ms) controla la velocidad. Ajustar según necesidad:
- 50ms = ~24 WPM (palabras por minuto)
- 60ms = ~20 WPM
- 100ms = ~12 WPM

## Caracteres Soportados

- **Letras:** A-Z (mayúsculas y minúsculas)
- **Números:** 0-9
- **Espacio:** Pausa entre palabras (7 unidades)
- **Comando:** `!` dispara secuencia CQ automática (CQ CQ CQ EA4HUK CQ CQ CQ)

## Simulador (Pruebas sin Hardware)

Se incluye `morse_sim.cpp` - un simulador en C++ para probar la lógica Morse sin necesidad del hardware Arduino:

```bash
# Compilar
g++ -o morse_sim morse_sim.cpp

# Ejecutar
./morse_sim
```

El simulador muestra:
- Activación del relay (KEY DOWN/UP)
- Activación del buzzer (ON/OFF)
- Pausas entre elementos y letras
- Conversión de caracteres a código Morse

## Estructura del Proyecto

```
Arduino-HF-Radio-Morse/
├── morse.cpp                    # Código principal para Arduino
├── morse_sim.cpp                # Simulador para pruebas en PC
├── relay-5v-arduino-mega.png   # Imagen del módulo relay
└── README.md                    # Esta documentación
```

## Solución de Problemas

**El botón CQ no funciona:**
- Verificar que el botón conecta pin 3 a GND (no a +5V)
- El código usa `INPUT_PULLUP`, no necesita resistencia externa

**La radio no keyea:**
- Verificar conexiones NO/COM del relay a KEYER +/- de la radio
- Comprobar que el relay hace "clic" al enviar código
- Revisar que +5V y GND lleguen correctamente al módulo relay

**Audio del buzzer muy bajo:**
- Verificar polaridad del buzzer (alguns son polarizados)
- Ajustar `note` (frecuencia) en el código (default: 1000 Hz)

## Autor

**dac** - dcialdella@gmail.com - **EA4HUK**

Proyecto para la comunidad de radioaficionados.
