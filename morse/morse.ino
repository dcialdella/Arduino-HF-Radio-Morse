//
// Trigger de codigo morse para un Xiegu G90, usando un arduino como interfaz
// Sale sonido por el puerto 8
// Sale señal digital en puerto 10, una pata del relay
// Tomar GND de otro conector para conectar la otra pata del relay
// Boton en pin 3 para CQ automatico
//
// dac - dcialdella@gmail.com - ea4huk
//

const int buzzer = 8;
const int relay = 10;
const int cqkey = 3;
const int statusLed = 13;

const int note = 1000;
int timeUnit = 60;

// Morse code array: index 0-25 = A-Z, 26-35 = 0-9
const char* morseCode[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
  "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
  "..-", "...-", ".--", "-..-", "-.--", "--..",
  "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."
};

void setup() {
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(statusLed, OUTPUT);
  pinMode(cqkey, INPUT_PULLUP);
  digitalWrite(statusLed, LOW);
  Serial.println("Ready (!=CQ)...");
}

void loop() {
  if (digitalRead(cqkey) == LOW) {
    delay(50);
    if (digitalRead(cqkey) == LOW) {
      cqcqcq();
      while (digitalRead(cqkey) == LOW) delay(10);
    }
  }

  if (Serial.available()) {
    char input = Serial.read();

    if (input >= 'a' && input <= 'z') input = input - 32;

    if (input >= 'A' && input <= 'Z') {
      digitalWrite(statusLed, HIGH);
      playCode(morseCode[input - 'A']);
      digitalWrite(statusLed, LOW);
      Serial.println(input);
    } else if (input >= '0' && input <= '9') {
      digitalWrite(statusLed, HIGH);
      playCode(morseCode[input - '0' + 26]);
      digitalWrite(statusLed, LOW);
      Serial.println(input);
    } else if (input == '!') {
      digitalWrite(statusLed, HIGH);
      cqcqcq();
      digitalWrite(statusLed, LOW);
    } else if (input == ' ') {
      wordPause();
      Serial.println("_");
    } else {
      Serial.print("? ");
      Serial.println(input);
    }
  }
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
}

void dot() {
  digitalWrite(relay, HIGH);
  tone(buzzer, note);
  delay(timeUnit);
  digitalWrite(relay, LOW);
  noTone(buzzer);
  delay(timeUnit);
}

void dash() {
  digitalWrite(relay, HIGH);
  tone(buzzer, note);
  delay(timeUnit * 3);
  digitalWrite(relay, LOW);
  noTone(buzzer);
  delay(timeUnit);
}

void letterPause() {
  delay(timeUnit * 2);
}

void wordPause() {
  delay(timeUnit * 6);
}
