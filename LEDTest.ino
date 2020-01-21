int switchForNumOfLed = 9;
int switchForCol = 10;
int switchForRow = 11;

int NumOfLed = 0;
int Col = 0;
int Row = 0;

/*    
 *        Col1        Col2
 * Row1
 * Row2
 * Row3
 * Row4
 * Row5
 * Row6
 * Row7
 * Row8
 * 
 * 
 */


int decoderRow1 = 8;
int decoderRow2 = 7;
int decoderRow3 = 6;

int decoderCol1 = 2;
int decoderCol2 = 3;

int cond_switchForNumOfLed = 1;
int cond_switchForCol = 1;
int cond_switchForRow = 1;

int delayForLed = 2000;

void setup() {
  Serial.begin(9600);
  pinMode(switchForNumOfLed, INPUT_PULLUP);
  pinMode(switchForCol, INPUT_PULLUP);
  pinMode(switchForRow, INPUT_PULLUP);
  
  pinMode(decoderRow1, OUTPUT);
  pinMode(decoderRow2, OUTPUT);
  pinMode(decoderRow3, OUTPUT);
  
  pinMode(decoderCol1, OUTPUT);
  pinMode(decoderCol2, OUTPUT);
}

void loop() {
  if(digitalRead(switchForNumOfLed) == LOW) {
    if(cond_switchForNumOfLed == 0) {
      if(NumOfLed == 3) {
        NumOfLed = 0;
        cond_switchForNumOfLed = 1;
      } else {
        NumOfLed++;
        cond_switchForNumOfLed = 1;
      }
    }
  } else {
    if(cond_switchForNumOfLed == 1) {
      cond_switchForNumOfLed = 0;
    }
  }
  
  if(digitalRead(switchForCol) == LOW) {
    if(cond_switchForCol == 0) {
      if(Col == 2) {
        Col = 0;
        cond_switchForCol = 1;
      } else {
        Col++;
        cond_switchForCol = 1;
      }
    }
  } else {
    if(cond_switchForCol == 1) {
      cond_switchForCol = 0;
    }
  }
  
  if(digitalRead(switchForRow) == LOW) {
    if(cond_switchForRow == 0) {
      if(Row == 7) {
        Row = 0;
        cond_switchForRow = 1;
      } else {
        Row++;
        cond_switchForRow = 1;
      }
    }
  } else {
    if(cond_switchForRow == 1) {
      cond_switchForRow = 0;
    }
  }

  if(NumOfLed == 0) {
    if(Row == 0) {
       if(Col == 0) { // single LED on 1st Col
         //Row는 decoder에 따라 행동.
         //Col은 HIGH가 꺼지는 것, LOW가 켜지는 것
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, HIGH);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 1) { // single LED on 2nd Col
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else { // single LED line on all Col
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
    }
    else if(Row == 1) {
       if(Col == 0) { // single LED on 1st Col
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, HIGH);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 1) { // single LED on 2nd Col
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else { // single LED line on all Col
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
    }
    else if(Row == 2) {
       if(Col == 0) { // single LED on 1st Col
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, HIGH);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 1) { // single LED on 2nd Col
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else { // single LED line on all Col
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
    }
    else if(Row == 3) {
       if(Col == 0) { // single LED on 1st Col
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, HIGH);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 1) { // single LED on 2nd Col
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else { // single LED line on all Col
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
    }
    else if(Row == 4) {
       if(Col == 0) { // single LED on 1st Col
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, HIGH);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 1) { // single LED on 2nd Col
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else { // single LED line on all Col
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
    }
    else if(Row == 5) {
       if(Col == 0) { // single LED on 1st Col
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, HIGH);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 1) { // single LED on 2nd Col
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else { // single LED line on all Col
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
    }
    else if(Row == 6) {
       if(Col == 0) { // single LED on 1st Col
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, HIGH);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 1) { // single LED on 2nd Col
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else { // single LED line on all Col
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
    }
    else {
       if(Col == 0) { // single LED on 1st Col
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, HIGH);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 1) { // single LED on 2nd Col
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else { // single LED line on all Col
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
    }
  }
  else if(NumOfLed == 1) {
    if(Row == 0 || Row == 4) {
       if(Col == 0) { // single LED on 1st Col
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, HIGH);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, HIGH);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 1) { // single LED on 2nd Col
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else { // single LED line on all Col
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
    }
    else if(Row == 1 || Row == 5) {
       if(Col == 0) { // single LED on 1st Col
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, HIGH);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, HIGH);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 1) { // single LED on 2nd Col
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else { // single LED line on all Col
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
    }
    else if(Row == 2 || Row == 6) {
       if(Col == 0) { // single LED on 1st Col
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, HIGH);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, HIGH);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 1) { // single LED on 2nd Col
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else { // single LED line on all Col
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
    }
    else {
       if(Col == 0) { // single LED on 1st Col
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, HIGH);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, HIGH);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 1) { // single LED on 2nd Col
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else { // single LED line on all Col
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
    }
  }
  else if(NumOfLed == 2) {
    if( Row == 0 || Row == 2 || Row == 4 || Row == 6) {
       if(Col == 0) { // single LED on 1st Col
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, HIGH);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, HIGH);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, HIGH);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, HIGH);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 1) { // single LED on 2nd Col
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else { // single LED line on all Col
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
    }
    else { // 4개씩 켜지는 경우 위쪽 Row
       if(Col == 0) { // single LED on 1st Col
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, HIGH);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, HIGH);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, HIGH);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, HIGH);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 1) { // single LED on 2nd Col
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else { // single LED line on all Col
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
    }
  }
  else { // Turn 8 LEDs On
    if(Col == 0) {
         //0
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, HIGH);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         //1
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, HIGH);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         //2
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, HIGH);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         //3
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, HIGH);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         //4
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, HIGH);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         //5
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, HIGH);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         //6
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, HIGH);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         //7
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, HIGH);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
    }
    else if(Col == 1) {
         //0
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         //1
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         //2
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         //3
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         //4
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         //5
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         //6
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         //7
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
    }
    else {
         //0
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         //1
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         //2
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         //3
         digitalWrite(decoderRow1, LOW);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         //4
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         //5
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, LOW);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         //6
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, LOW);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
         //7
         digitalWrite(decoderRow1, HIGH);
         digitalWrite(decoderRow2, HIGH);
         digitalWrite(decoderRow3, HIGH);
         digitalWrite(decoderCol1, LOW);
         digitalWrite(decoderCol2, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
    }
  }
}

int TurnOffAll(){
  digitalWrite(decoderRow1, LOW);
  digitalWrite(decoderRow2, LOW);
  digitalWrite(decoderRow3, LOW);
  digitalWrite(decoderCol1, HIGH);
  digitalWrite(decoderCol1, HIGH);
}
