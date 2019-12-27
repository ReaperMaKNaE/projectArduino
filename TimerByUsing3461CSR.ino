/*
 *  --------------  3461CSR  -----------------
 * |         |          |          |          |
 * |  FIRST  |  SECOND  |   THIRD  |  FOURTH  |
 * |         |          |          |          |
 *  ------------------------------------------
 *  
 *   LOW (Screen)   ==>    HIGH (Segment)
 *  
 */

#include <MsTimer2.h>

int first3461CSR = 2;
int second3461CSR = 3;
int third3461CSR = 4;
int fourth3461CSR = 5;

/*
 *         A
 *        ---
 *     F |   | B
 *        --- <== G
 *     E |   | C
 *        ---
 *         D
 */


int segmentA = 6;
int segmentB = 7;
int segmentC = 8;
int segmentD = 9;
int segmentE = 10;
int segmentF = 11;
int segmentG = 12;
int segmentDOT = 13;

int timer = 0;
int mode = 0;
int conditionVariable = 0;
int timeSet;

int initializePin = A0;

void setup() {
  Serial.begin(9600);
  pinMode(first3461CSR, OUTPUT);
  pinMode(second3461CSR, OUTPUT);
  pinMode(third3461CSR, OUTPUT);
  pinMode(fourth3461CSR, OUTPUT);
  pinMode(segmentA, OUTPUT);
  pinMode(segmentB, OUTPUT);
  pinMode(segmentC, OUTPUT);
  pinMode(segmentD, OUTPUT);
  pinMode(segmentE, OUTPUT);
  pinMode(segmentF, OUTPUT);
  pinMode(segmentG, OUTPUT);
  pinMode(initializePin, INPUT_PULLUP);

  MsTimer2::set(97, Timer);
  MsTimer2::start();
}

void loop() {  
  if(digitalRead(initializePin) == LOW) {
    if(conditionVariable == 0) {
      if(mode == 2) {
        mode = 0;
        conditionVariable = 1;
      } else {
        mode++;
        conditionVariable = 1;
      }
    }
  } else {
    if(conditionVariable == 1) {
      conditionVariable = 0;
    }
  }

  if(mode == 0) {
    timer = 0;
    print3461CSR(timer);
  }
  else if (mode == 1 ) {
    print3461CSR(timer);
    timeSet = timer;
  }
  else {
    print3461CSR(timeSet);
  }
}

void Timer() {
  timer++;
}

int print3461CSR(int number) {
  int firstNum = number / 1000;
  int secondNum = ( number % 1000 ) / 100;
  int thirdNum = ( number % 100 ) / 10;
  int fourthNum = number % 10;
  
  turnOnFirstNumber();
  print3461CSRNumber(firstNum);
  delay(4);
  turnOffAll();
  turnOnSecondNumber();
  print3461CSRNumber(secondNum);
  delay(4);
  turnOffAll();
  turnOnThirdNumber();
  print3461CSRNumber(thirdNum);
  delay(4);
  turnOffAll();
  turnOnFourthNumber();
  print3461CSRNumber(fourthNum);
  delay(4);
  turnOffAll();
}

int print3461CSRNumber(int number) {
  if(number == 0) {
    digitalWrite(segmentA, HIGH);
    digitalWrite(segmentB, HIGH);
    digitalWrite(segmentC, HIGH);
    digitalWrite(segmentD, HIGH);
    digitalWrite(segmentE, HIGH);
    digitalWrite(segmentF, HIGH);
    digitalWrite(segmentG, LOW);
  } else if(number == 1) {
    digitalWrite(segmentA, LOW);
    digitalWrite(segmentB, HIGH);
    digitalWrite(segmentC, HIGH);
    digitalWrite(segmentD, LOW);
    digitalWrite(segmentE, LOW);
    digitalWrite(segmentF, LOW);
    digitalWrite(segmentG, LOW);
  } else if(number == 2) {
    digitalWrite(segmentA, HIGH);
    digitalWrite(segmentB, HIGH);
    digitalWrite(segmentC, LOW);
    digitalWrite(segmentD, HIGH);
    digitalWrite(segmentE, HIGH);
    digitalWrite(segmentF, LOW);
    digitalWrite(segmentG, HIGH);
  } else if(number == 3) {
    digitalWrite(segmentA, HIGH);
    digitalWrite(segmentB, HIGH);
    digitalWrite(segmentC, HIGH);
    digitalWrite(segmentD, HIGH);
    digitalWrite(segmentE, LOW);
    digitalWrite(segmentF, LOW);
    digitalWrite(segmentG, HIGH);
  } else if(number == 4) {
    digitalWrite(segmentA, LOW);
    digitalWrite(segmentB, HIGH);
    digitalWrite(segmentC, HIGH);
    digitalWrite(segmentD, LOW);
    digitalWrite(segmentE, LOW);
    digitalWrite(segmentF, HIGH);
    digitalWrite(segmentG, HIGH);
  } else if(number == 5) {
    digitalWrite(segmentA, HIGH);
    digitalWrite(segmentB, LOW);
    digitalWrite(segmentC, HIGH);
    digitalWrite(segmentD, HIGH);
    digitalWrite(segmentE, LOW);
    digitalWrite(segmentF, HIGH);
    digitalWrite(segmentG, HIGH);
  } else if(number == 6) {
    digitalWrite(segmentA, HIGH);
    digitalWrite(segmentB, LOW);
    digitalWrite(segmentC, HIGH);
    digitalWrite(segmentD, HIGH);
    digitalWrite(segmentE, HIGH);
    digitalWrite(segmentF, HIGH);
    digitalWrite(segmentG, HIGH);
  } else if(number == 7) {
    digitalWrite(segmentA, HIGH);
    digitalWrite(segmentB, HIGH);
    digitalWrite(segmentC, HIGH);
    digitalWrite(segmentD, LOW);
    digitalWrite(segmentE, LOW);
    digitalWrite(segmentF, HIGH);
    digitalWrite(segmentG, LOW);
  } else if(number == 8) {
    digitalWrite(segmentA, HIGH);
    digitalWrite(segmentB, HIGH);
    digitalWrite(segmentC, HIGH);
    digitalWrite(segmentD, HIGH);
    digitalWrite(segmentE, HIGH);
    digitalWrite(segmentF, HIGH);
    digitalWrite(segmentG, HIGH);
  } else if(number == 9) {
    digitalWrite(segmentA, HIGH);
    digitalWrite(segmentB, HIGH);
    digitalWrite(segmentC, HIGH);
    digitalWrite(segmentD, LOW);
    digitalWrite(segmentE, LOW);
    digitalWrite(segmentF, HIGH);
    digitalWrite(segmentG, HIGH);
  }
}

void turnOffAll(){
    digitalWrite(segmentA, HIGH);
    digitalWrite(segmentB, HIGH);
    digitalWrite(segmentC, HIGH);
    digitalWrite(segmentD, HIGH);
    digitalWrite(segmentE, HIGH);
    digitalWrite(segmentF, HIGH);
    digitalWrite(segmentG, HIGH);
}

void turnOnFirstNumber(){
  digitalWrite(first3461CSR, LOW);
  digitalWrite(second3461CSR, HIGH);
  digitalWrite(third3461CSR, HIGH);
  digitalWrite(fourth3461CSR, HIGH);
}

void turnOnSecondNumber(){
  digitalWrite(first3461CSR, HIGH);
  digitalWrite(second3461CSR, LOW);
  digitalWrite(third3461CSR, HIGH);
  digitalWrite(fourth3461CSR, HIGH);
}

void turnOnThirdNumber(){
  digitalWrite(first3461CSR, HIGH);
  digitalWrite(second3461CSR, HIGH);
  digitalWrite(third3461CSR, LOW);
  digitalWrite(fourth3461CSR, HIGH);
}

void turnOnFourthNumber(){
  digitalWrite(first3461CSR, HIGH);
  digitalWrite(second3461CSR, HIGH);
  digitalWrite(third3461CSR, HIGH);
  digitalWrite(fourth3461CSR, LOW);
}
