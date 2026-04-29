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

const int note = 1000;
int timeUnit = 60;

char input;

void setup() {
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(cqkey, INPUT_PULLUP);
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
    input = Serial.read();

    if (input >= 'a' && input <= 'z') input -= 32;

    switch (input) {
      case 'A': lA(); break;
      case 'B': lB(); break;
      case 'C': lC(); break;
      case 'D': lD(); break;
      case 'E': lE(); break;
      case 'F': lF(); break;
      case 'G': lG(); break;
      case 'H': lH(); break;
      case 'I': lI(); break;
      case 'J': lJ(); break;
      case 'K': lK(); break;
      case 'L': lL(); break;
      case 'M': lM(); break;
      case 'N': lN(); break;
      case 'O': lO(); break;
      case 'P': lP(); break;
      case 'Q': lQ(); break;
      case 'R': lR(); break;
      case 'S': lS(); break;
      case 'T': lT(); break;
      case 'U': lU(); break;
      case 'V': lV(); break;
      case 'W': lW(); break;
      case 'X': lX(); break;
      case 'Y': lY(); break;
      case 'Z': lZ(); break;
      case '0': l0(); break;
      case '1': l1(); break;
      case '2': l2(); break;
      case '3': l3(); break;
      case '4': l4(); break;
      case '5': l5(); break;
      case '6': l6(); break;
      case '7': l7(); break;
      case '8': l8(); break;
      case '9': l9(); break;
      case '!': cqcqcq(); break;
      case ' ': wordPause(); break;
    }

    Serial.println(input);
  }
}

void cqcqcq() {
  lC(); lQ(); lC(); lQ(); lC(); lQ();
  lE(); lA(); l4(); lH(); lU(); lK();
  lC(); lQ(); lC(); lQ(); lC(); lQ();
}

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
  delay(timeUnit * 3);
}

void wordPause() {
  delay(timeUnit * 7);
}
