//
// Simulador de Morse - Version simplificada
// Compilar: g++ -o morse_sim morse_sim.cpp
// Ejecutar: ./morse_sim
//

#include <iostream>
#include <unistd.h>

int timeUnit = 60;

const char* morseCode[] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
    "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
    "..-", "...-", ".--", "-..-", "-.--", "--..",
    "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."
};

void dot() {
    std::cout << "." << std::flush;
    usleep(timeUnit * 2000);
}

void dash() {
    std::cout << "-" << std::flush;
    usleep(timeUnit * 4000);
}

void letterPause() {
    std::cout << " " << std::flush;
    usleep(timeUnit * 2000);
}

void wordPause() {
    std::cout << "  " << std::flush;
    usleep(timeUnit * 6000);
}

void playCode(const char* code) {
    while (*code) {
        if (*code == '.') dot();
        else if (*code == '-') dash();
        code++;
    }
    letterPause();
}

void cqcqcq() {
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
}

void processInput(char c) {
    if (c >= 'a' && c <= 'z') c -= 32;
    if (c >= 'A' && c <= 'Z') playCode(morseCode[c - 'A']);
    else if (c >= '0' && c <= '9') playCode(morseCode[c - '0' + 26]);
    else if (c == '!') cqcqcq();
    else if (c == ' ') wordPause();
    std::cout << std::endl;
}

int main() {
    char input;
    while (std::cin >> input) {
        processInput(input);
    }
    return 0;
}