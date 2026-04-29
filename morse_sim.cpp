//
// Simulador de morse.cpp para verificar funcionamiento
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
const int note = 1000;
int timeUnit = 60;

// Estado simulado
bool relayState = false;
bool buzzerState = false;
char input;

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
    std::cout << "  [LETTER PAUSE 3x]" << std::endl;
    delay(timeUnit * 3);
}

void wordPause() {
    std::cout << "[WORD PAUSE 7x]" << std::endl;
    delay(timeUnit * 7);
}

// Funciones de letras
void lA() { dot(); dash(); letterPause(); }
void lB() { dash(); dot(); dot(); dot(); letterPause(); }
void lC() { dash(); dot(); dash(); dot(); letterPause(); }
void lD() { dash(); dot(); dot(); letterPause(); }
void lE() { dot(); letterPause(); }
void lF() { dot(); dot(); dash(); dot(); letterPause(); }
void lG() { dash(); dash(); dot(); letterPause(); }
void lH() { dot(); dot(); dot(); dot(); letterPause(); }
void lI() { dot(); dot(); letterPause(); }
void lJ() { dot(); dash(); dash(); dash(); letterPause(); }
void lK() { dash(); dot(); dash(); letterPause(); }
void lL() { dot(); dash(); dot(); dot(); letterPause(); }
void lM() { dash(); dash(); letterPause(); }
void lN() { dash(); dot(); letterPause(); }
void lO() { dash(); dash(); dash(); letterPause(); }
void lP() { dot(); dash(); dash(); dot(); letterPause(); }
void lQ() { dash(); dash(); dot(); dash(); letterPause(); }
void lR() { dot(); dash(); dot(); letterPause(); }
void lS() { dot(); dot(); dot(); letterPause(); }
void lT() { dash(); letterPause(); }
void lU() { dot(); dot(); dash(); letterPause(); }
void lV() { dot(); dot(); dot(); dash(); letterPause(); }
void lW() { dot(); dash(); dash(); letterPause(); }
void lX() { dash(); dot(); dot(); dash(); letterPause(); }
void lY() { dash(); dot(); dash(); dash(); letterPause(); }
void lZ() { dash(); dash(); dot(); dot(); letterPause(); }

void l0() { dash(); dash(); dash(); dash(); dash(); letterPause(); }
void l1() { dot(); dash(); dash(); dash(); dash(); letterPause(); }
void l2() { dot(); dot(); dash(); dash(); dash(); letterPause(); }
void l3() { dot(); dot(); dot(); dash(); dash(); letterPause(); }
void l4() { dot(); dot(); dot(); dot(); dash(); letterPause(); }
void l5() { dot(); dot(); dot(); dot(); dot(); letterPause(); }
void l6() { dash(); dot(); dot(); dot(); dot(); letterPause(); }
void l7() { dash(); dash(); dot(); dot(); dot(); letterPause(); }
void l8() { dash(); dash(); dash(); dot(); dot(); letterPause(); }
void l9() { dash(); dash(); dash(); dash(); dot(); letterPause(); }

void cqcqcq() {
    std::cout << "=== ENVIANDO CQ CQ CQ EA4HUK CQ CQ CQ ===" << std::endl;
    lC(); lQ(); lC(); lQ(); lC(); lQ();
    lE(); lA(); l4(); lH(); lU(); lK();
    lC(); lQ(); lC(); lQ(); lC(); lQ();
    std::cout << "=== FIN CQ ===" << std::endl;
}

// Setup y Loop simulados
void setup() {
    Serial_begin(9600);
    pinMode(buzzer, 1); // OUTPUT = 1
    pinMode(relay, 1);  // OUTPUT = 1
    pinMode(cqkey, 2);  // INPUT_PULLUP = 2
    std::cout << "Ready (!=CQ)..." << std::endl;
}

void loop() {
    if (Serial_available()) {
        std::cout << "\n>> Ingresar caracter: " << std::flush;
        std::cin >> input;
        
        if (input >= 'a' && input <= 'z') input -= 32;
        
        switch (input) {
            case 'A': std::cout << "[MORSE] A = .-" << std::endl; lA(); break;
            case 'B': std::cout << "[MORSE] B = -..." << std::endl; lB(); break;
            case 'C': std::cout << "[MORSE] C = -.-." << std::endl; lC(); break;
            case 'D': std::cout << "[MORSE] D = -.." << std::endl; lD(); break;
            case 'E': std::cout << "[MORSE] E = ." << std::endl; lE(); break;
            case 'F': std::cout << "[MORSE] F = ..-." << std::endl; lF(); break;
            case 'G': std::cout << "[MORSE] G = --." << std::endl; lG(); break;
            case 'H': std::cout << "[MORSE] H = ...." << std::endl; lH(); break;
            case 'I': std::cout << "[MORSE] I = .." << std::endl; lI(); break;
            case 'J': std::cout << "[MORSE] J = .---" << std::endl; lJ(); break;
            case 'K': std::cout << "[MORSE] K = -.-" << std::endl; lK(); break;
            case 'L': std::cout << "[MORSE] L = .-.." << std::endl; lL(); break;
            case 'M': std::cout << "[MORSE] M = --" << std::endl; lM(); break;
            case 'N': std::cout << "[MORSE] N = -." << std::endl; lN(); break;
            case 'O': std::cout << "[MORSE] O = ---" << std::endl; lO(); break;
            case 'P': std::cout << "[MORSE] P = .--." << std::endl; lP(); break;
            case 'Q': std::cout << "[MORSE] Q = --.-" << std::endl; lQ(); break;
            case 'R': std::cout << "[MORSE] R = .-." << std::endl; lR(); break;
            case 'S': std::cout << "[MORSE] S = ..." << std::endl; lS(); break;
            case 'T': std::cout << "[MORSE] T = -" << std::endl; lT(); break;
            case 'U': std::cout << "[MORSE] U = ..-" << std::endl; lU(); break;
            case 'V': std::cout << "[MORSE] V = ...-" << std::endl; lV(); break;
            case 'W': std::cout << "[MORSE] W = .--" << std::endl; lW(); break;
            case 'X': std::cout << "[MORSE] X = -..-" << std::endl; lX(); break;
            case 'Y': std::cout << "[MORSE] Y = -.--" << std::endl; lY(); break;
            case 'Z': std::cout << "[MORSE] Z = --.." << std::endl; lZ(); break;
            case '0': std::cout << "[MORSE] 0 = -----" << std::endl; l0(); break;
            case '1': std::cout << "[MORSE] 1 = .----" << std::endl; l1(); break;
            case '2': std::cout << "[MORSE] 2 = ..---" << std::endl; l2(); break;
            case '3': std::cout << "[MORSE] 3 = ...--" << std::endl; l3(); break;
            case '4': std::cout << "[MORSE] 4 = ....-" << std::endl; l4(); break;
            case '5': std::cout << "[MORSE] 5 = ....." << std::endl; l5(); break;
            case '6': std::cout << "[MORSE] 6 = -...." << std::endl; l6(); break;
            case '7': std::cout << "[MORSE] 7 = --..." << std::endl; l7(); break;
            case '8': std::cout << "[MORSE] 8 = ---.." << std::endl; l8(); break;
            case '9': std::cout << "[MORSE] 9 = ----." << std::endl; l9(); break;
            case '!': cqcqcq(); break;
            case ' ': wordPause(); break;
            default: std::cout << "[ERROR] Caracter no soportado: " << input << std::endl;
        }
        
        Serial_println(input);
    }
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "  SIMULADOR Arduino Morse Keyer" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "timeUnit = " << timeUnit << "ms" << std::endl;
    std::cout << "Velocidad aproximada: 20 WPM" << std::endl;
    std::cout << "========================================" << std::endl;
    
    setup();
    
    char continuar = 's';
    while (continuar != 'n' && continuar != 'N') {
        loop();
        std::cout << "\n¿Continuar? (s/n): " << std::flush;
        std::cin >> continuar;
    }
    
    std::cout << "Simulacion terminada." << std::endl;
    return 0;
}
