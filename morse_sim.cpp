//
// Simulador de morse.ino para verificar funcionamiento
// Compilar: g++ -o morse_sim morse_sim.cpp
// Ejecutar: ./morse_sim
//

#include <iostream>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <ctime>

// Simulacion de pines
const int buzzer = 8;
const int relay = 10;
const int cqkey = 3;
const int statusLed = 13;
const int note = 1000;
int timeUnit = 60;

// Estado simulado
bool relayState = false;
bool buzzerState = false;
bool ledState = false;
char input;

// Morse code array: index 0-25 = A-Z, 26-35 = 0-9
const char* morseCode[] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
    "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
    "..-", "...-", ".--", "-..-", "-.--", "--..",
    "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."
};

// Funciones simuladas de Arduino
void pinMode(int pin, int mode) {
    std::cout << "[SETUP] pinMode(" << pin << ", " << (mode == 1 ? "OUTPUT" : "INPUT_PULLUP") << ")" << std::endl;
    // mode: 0=INPUT, 1=OUTPUT, 2=INPUT_PULLUP
}

void digitalWrite(int pin, int value) {
    if (pin == relay) {
        if (value == 1 && !relayState) {
            std::cout << "[RELAY] HIGH (key down)" << std::endl;
            relayState = true;
        } else if (value == 0 && relayState) {
            std::cout << "[RELAY] LOW (key up)" << std::endl;
            relayState = false;
        }
    } else if (pin == statusLed) {
        if (value == 1 && !ledState) {
            std::cout << "[LED] ON" << std::endl;
            ledState = true;
        } else if (value == 0 && ledState) {
            std::cout << "[LED] OFF" << std::endl;
            ledState = false;
        }
    }
}

void tone(int pin, int frequency) {
    if (!buzzerState) {
        std::cout << "[BUZZER] ON (" << frequency << " Hz)" << std::endl;
        buzzerState = true;
    }
}

void noTone(int pin) {
    if (buzzerState) {
        std::cout << "[BUZZER] OFF" << std::endl;
        buzzerState = false;
    }
}

void delay(int ms) {
    usleep(ms * 1000); // Sleep for ms milliseconds
}

int digitalRead(int pin) {
    // Simular boton CQ - retorna LOW si se presiona (INPUT_PULLUP)
    return 1; // Normalmente HIGH (no presionado)
}

void Serial_begin(int baud) {
    std::cout << "[SETUP] Serial.begin(" << baud << ")" << std::endl;
}

void Serial_println(const char* msg) {
    std::cout << "[SERIAL] " << msg << std::endl;
}

void Serial_println(char c) {
    std::cout << "[SERIAL] " << c << std::endl;
}

bool Serial_available() {
    return true; // Siempre disponible en simulacion
}

char Serial_read() {
    return input;
}

// Funciones Morse
void dot() {
    std::cout << "  [DOT] " << std::flush;
    digitalWrite(relay, 1);
    tone(buzzer, note);
    delay(timeUnit);
    digitalWrite(relay, 0);
    noTone(buzzer);
    delay(timeUnit);
    std::cout << std::endl;
}

void dash() {
    std::cout << "  [DASH] " << std::flush;
    digitalWrite(relay, 1);
    tone(buzzer, note);
    delay(timeUnit * 3);
    digitalWrite(relay, 0);
    noTone(buzzer);
    delay(timeUnit);
    std::cout << std::endl;
}

void letterPause() {
    std::cout << "  [LETTER PAUSE 2x+1x]" << std::endl;
    delay(timeUnit * 2);
}

void wordPause() {
    std::cout << "[WORD PAUSE 6x+1x]" << std::endl;
    delay(timeUnit * 6);
}

void playCode(const char* code) {
    while (*code) {
        if (*code == '.') {
            dot();
        } else if (*code == '-') {
            dash();
        }
        code++;
    }
    letterPause();
}

void cqcqcq() {
    std::cout << "=== ENVIANDO CQ CQ CQ EA4HUK CQ CQ CQ ===" << std::endl;
    playCode(morseCode['C' - 'A']);
    playCode(morseCode['Q' - 'A']);
    playCode(morseCode['C' - 'A']);
    playCode(morseCode['Q' - 'A']);
    playCode(morseCode['C' - 'A']);
    playCode(morseCode['Q' - 'A']);
    playCode(morseCode['E' - 'A']);
    playCode(morseCode['A' - 'A']);
    playCode(morseCode['4' - '0' + 26]);
    playCode(morseCode['H' - 'A']);
    playCode(morseCode['U' - 'A']);
    playCode(morseCode['K' - 'A']);
    playCode(morseCode['C' - 'A']);
    playCode(morseCode['Q' - 'A']);
    playCode(morseCode['C' - 'A']);
    playCode(morseCode['Q' - 'A']);
    playCode(morseCode['C' - 'A']);
    playCode(morseCode['Q' - 'A']);
    std::cout << "=== FIN CQ ===" << std::endl;
}

// Setup y Loop simulados
void setup() {
    Serial_begin(9600);
    pinMode(buzzer, 1); // OUTPUT = 1
    pinMode(relay, 1);  // OUTPUT = 1
    pinMode(statusLed, 1); // OUTPUT = 1
    pinMode(cqkey, 2);  // INPUT_PULLUP = 2
    digitalWrite(statusLed, 0); // LED OFF
    std::cout << "Ready (!=CQ)..." << std::endl;
}

void processInput(char input) {
    if (input >= 'a' && input <= 'z') input = input - 32;

    if (input >= 'A' && input <= 'Z') {
        std::cout << "[MORSE] " << input << " = " << morseCode[input - 'A'] << std::endl;
        digitalWrite(statusLed, 1);
        playCode(morseCode[input - 'A']);
        digitalWrite(statusLed, 0);
        Serial_println(input);
    } else if (input >= '0' && input <= '9') {
        std::cout << "[MORSE] " << input << " = " << morseCode[input - '0' + 26] << std::endl;
        digitalWrite(statusLed, 1);
        playCode(morseCode[input - '0' + 26]);
        digitalWrite(statusLed, 0);
        Serial_println(input);
    } else if (input == '!') {
        digitalWrite(statusLed, 1);
        cqcqcq();
        digitalWrite(statusLed, 0);
    } else if (input == ' ') {
        wordPause();
        Serial_println("_");
    } else {
        std::cout << "? Caracter no soportado: " << input << std::endl;
    }
}

void loop() {
    if (Serial_available()) {
        std::cout << "\n>> Ingresar caracter: " << std::flush;
        std::cin >> input;
        processInput(input);
    }
    usleep(100000);
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "  SIMULADOR Arduino Morse Keyer" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "timeUnit = " << timeUnit << "ms" << std::endl;
    std::cout << "Velocidad aproximada: 20 WPM" << std::endl;
    std::cout << "========================================" << std::endl;

    setup();

    while (true) {
        loop();
    }

    return 0;
}
