//
// Trigger de codigo morse para un Xiagu g90, usando un arduino como interfaz
// Sale sonido por el puerto 8
// Sale Señal digital en puerto 10, una pata del relay
// Tomar GND de otro conector para conectar la otra pata del relay
//
// dac - dcialdella@gmail.com - ea4-huk
//
//


int buzzer = 8; // Assign buzzer to pin 8
int relay = 10;  // Assign relay to pin 10
int cqkey = 3 ; // send CQ CQ CQ ea4huk cq cq cq
int note = 1000; // Set the pitch for the buzzer tone

int timeUnit = 60; // 75 is FINE This variable will be used to measure dots, dashes, breaks, and pauses
char input; // Variable to save the input to

String code = "";

void setup () {
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(cqkey, INPUT);
  digitalWrite(cqkey, LOW);
  Serial.println("Ready (!=CQ)...");
}


//  while (Serial.available())
//  {
//    code = Serial.readString();
//    Serial.print(code);
//    Serial.print(" = ");
//    String2Morse();
//    Serial.println("");
//  }
//  delay(1000);

 
void loop () {

if (Serial.available()) {
  input = Serial.read();
 
  if (input == 'a' || input == 'A') {lA();}     // mayuscula ominuscula es igual
  if (input == 'b' || input == 'B') {lB();}      
  if (input == 'c' || input == 'C') {lC();}
  if (input == 'd' || input == 'D') {lD();}
  if (input == 'e' || input == 'E') {lE();}
  if (input == 'f' || input == 'F') {lF();}
  if (input == 'g' || input == 'G') {lG();}
  if (input == 'h' || input == 'H') {lH();}
  if (input == 'i' || input == 'I') {lI();}
  if (input == 'j' || input == 'J') {lJ();}
  if (input == 'k' || input == 'K') {lK();}
  if (input == 'l' || input == 'L') {lL();}
  if (input == 'm' || input == 'M') {lM();}
  if (input == 'n' || input == 'N') {lN();}
  if (input == 'o' || input == 'O') {lO();}
  if (input == 'p' || input == 'P') {lP();}
  if (input == 'q' || input == 'Q') {lQ();}
  if (input == 'r' || input == 'R') {lR();}
  if (input == 's' || input == 'S') {lS();}
  if (input == 't' || input == 'T') {lT();}
  if (input == 'u' || input == 'U') {lU();}
  if (input == 'v' || input == 'V') {lV();}
  if (input == 'w' || input == 'W') {lW();}
  if (input == 'x' || input == 'X') {lX();}
  if (input == 'y' || input == 'Y') {lY();}
  if (input == 'z' || input == 'Z') {lZ();}
  if (input == '0' )  {l0();}
  if (input == '1' )  {l1();}
  if (input == '2' )  {l2();}
  if (input == '3' )  {l3();}
  if (input == '4' )  {l4();}
  if (input == '5' )  {l5();}
  if (input == '6' )  {l6();}
  if (input == '7' )  {l7();}
  if (input == '8' )  {l8();}
  if (input == '9' )  {l9();}

  if (input == '!' )  {cqcqcq();}

  if (input == ' ') {wordPause();}
 
  Serial.println (input);

  }
}


void cqcqcq()
{
 lC(); lQ(); lC(); lQ(); lC(); lQ();
 lE(); lA(); l4(); lH(); lU(); lK();
 lC(); lQ(); lC(); lQ(); lC(); lQ();
}

//Letter functions
void lA () {dot();dash();letterPause();} //letter A in morse code!
void lB () {dash();dot();dot();dot();letterPause();} //same for B
void lC () {dash();dot();dash();dot();letterPause();}
void lD () {dash();dot();dot();letterPause();}
void lE () {dot();letterPause();}
void lF () {dot();dot();dash();dot();letterPause();}
void lG () {dash();dash();dot();letterPause();}
void lH () {dot();dot();dot();dot();letterPause();}
void lI () {dot();dot();letterPause();}
void lJ () {dot();dash();dash();dash();letterPause();}
void lK () {dash();dot();dash();letterPause();}
void lL () {dot();dash();dot();dot();letterPause();}
void lM () {dash();dash();letterPause();}
void lN () {dash();dot();letterPause();}
void lO () {dash();dash();dash();letterPause();}
void lP () {dot();dash();dash();dot();letterPause();}
void lQ () {dash();dash();dot();dash();letterPause();}
void lR () {dot();dash();dot();letterPause();}
void lS () {dot();dot();dot();letterPause();}
void lT () {dash();letterPause();}
void lU () {dot();dot();dash();letterPause();}
void lV () {dot();dot();dot();dash();letterPause();}
void lW () {dot();dash();dash();letterPause();}
void lX () {dash();dot();dot();dash();letterPause();}
void lY () {dash();dot();dash();dash();letterPause();}
void lZ () {dash();dash();dot();dot();letterPause();}

void l1 () {dot();dash();dash();dash();dash();letterPause();}  //  1
void l2 () {dot();dot();dash();dash();dash();;letterPause();}
void l3 () {dot();dot();dot();dash();dash();letterPause();}
void l4 () {dot();dot();dot();dot();dash();letterPause();}
void l5 () {dot();dot();dot();dot();dot();letterPause();}
void l6 () {dash();dot();dot();dot();dot();letterPause();}
void l7 () {dash();dash();dot();dot();dot();letterPause();}
void l8 () {dash();dash();dash();dot();dot();letterPause();}
void l9 () {dash();dash();dash();dash();dot();letterPause();}  //  9
void l0 () {dash();dash();dash();dash();dash();letterPause();} //  NUMBER 0

void dot() //Emit sound for NN milliseconds
{
  digitalWrite(relay, HIGH); 
  tone(buzzer, note);
  delay(timeUnit);
  digitalWrite(relay, LOW); 
  noTone(buzzer);
  delay(timeUnit * 2);
}

void dash() //Emit sound for NN * 3 milliseconds
{
  digitalWrite(relay, HIGH); 
  tone(buzzer, note);
  delay(timeUnit * 3);
  digitalWrite(relay, LOW); 
  noTone(buzzer);
  delay(timeUnit * 4);
}

void letterPause() //Delay between letters for NN * 3 milliseconds
{
  delay(timeUnit * 3);
}

void wordPause()
{
  delay (timeUnit * 7);
}
