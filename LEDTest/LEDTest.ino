int switchForNumOfLed = 9;
int switchForCol = 10;
int switchForRow = 11;

int NumOfLed = 0;
int Col = 0;
int Row = 0;

/*    
 *        Col1        Col2        col3        col4
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

int row1 = 2;
int row2 = 3;
int row3 = 4;
int row4 = 5;
int row5 = 6;
int row6 = 7;
int row7 = 8;
int row8 = 9;

int col1 = 24;
int col2 = 26;
int col3 = 28;
int col4 = 30;

int cond_switchForNumOfLed = 1;
int cond_switchForCol = 1;
int cond_switchForRow = 1;

int delayForLed = 2000;

void setup() {
  Serial.begin(9600);
  pinMode(switchForNumOfLed, INPUT_PULLUP);
  pinMode(switchForCol, INPUT_PULLUP);
  pinMode(switchForRow, INPUT_PULLUP);
  
  pinMode(row1, OUTPUT);
  pinMode(row2, OUTPUT);
  pinMode(row3, OUTPUT);
  pinMode(row4, OUTPUT);
  pinMode(row5, OUTPUT);
  pinMode(row6, OUTPUT);
  pinMode(row7, OUTPUT);
  pinMode(row8, OUTPUT);
  
  pinMode(col1, OUTPUT);
  pinMode(col2, OUTPUT);
  pinMode(col3, OUTPUT);
  pinMode(col4, OUTPUT);
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
      if(Col == 4) {
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
         //Row는 decoder에 따라 행동. => Update하면서 decoder 사용 X
         //Col은 Low가 꺼지는 것, High가 켜지는 것
         digitalWrite(row1, LOW);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, HIGH);
         digitalWrite(col2, LOW);
         digitalWrite(col3, LOW);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 1) { // single LED on 2nd Col
         digitalWrite(row1, LOW);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, LOW);
         digitalWrite(col2, HIGH);
         digitalWrite(col3, LOW);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 2) { // single LED line on all Col
         digitalWrite(row1, LOW);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, LOW);
         digitalWrite(col2, LOW);
         digitalWrite(col3, HIGH);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 3) { // single LED line on all Col
         digitalWrite(row1, LOW);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, LOW);
         digitalWrite(col2, LOW);
         digitalWrite(col3, LOW);
         digitalWrite(col4, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 4) { // single LED line on all Col
         digitalWrite(row1, LOW);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, HIGH);
         digitalWrite(col2, HIGH);
         digitalWrite(col3, HIGH);
         digitalWrite(col4, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
    }
    else if(Row == 1) {
       if(Col == 0) { // single LED on 1st Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, LOW);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, HIGH);
         digitalWrite(col2, LOW);
         digitalWrite(col3, LOW);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 1) { // single LED on 2nd Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, LOW);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, LOW);
         digitalWrite(col2, HIGH);
         digitalWrite(col3, LOW);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 2) { // single LED line on all Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, LOW);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, LOW);
         digitalWrite(col2, LOW);
         digitalWrite(col3, HIGH);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 3) { // single LED line on all Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, LOW);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, LOW);
         digitalWrite(col2, LOW);
         digitalWrite(col3, LOW);
         digitalWrite(col4, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 4) { // single LED line on all Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, LOW);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, HIGH);
         digitalWrite(col2, HIGH);
         digitalWrite(col3, HIGH);
         digitalWrite(col4, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
    }
    else if(Row == 2) {
       if(Col == 0) { // single LED on 1st Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, LOW);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, HIGH);
         digitalWrite(col2, LOW);
         digitalWrite(col3, LOW);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 1) { // single LED on 2nd Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, LOW);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, LOW);
         digitalWrite(col2, HIGH);
         digitalWrite(col3, LOW);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 2) { // single LED on 2nd Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, LOW);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, LOW);
         digitalWrite(col2, LOW);
         digitalWrite(col3, HIGH);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 3) { // single LED on 2nd Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, LOW);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, LOW);
         digitalWrite(col2, LOW);
         digitalWrite(col3, HIGH);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 4) { // single LED on 2nd Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, LOW);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, HIGH);
         digitalWrite(col2, HIGH);
         digitalWrite(col3, HIGH);
         digitalWrite(col4, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
    }
    else if(Row == 3) {
       if(Col == 0) { // single LED on 1st Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, LOW);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, HIGH);
         digitalWrite(col2, LOW);
         digitalWrite(col3, LOW);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 1) { // single LED on 2nd Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, LOW);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, LOW);
         digitalWrite(col2, HIGH);
         digitalWrite(col3, LOW);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 2) { // single LED on 2nd Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, LOW);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, LOW);
         digitalWrite(col2, LOW);
         digitalWrite(col3, HIGH);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 3) { // single LED on 2nd Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, LOW);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, LOW);
         digitalWrite(col2, LOW);
         digitalWrite(col3, LOW);
         digitalWrite(col4, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 4) { // single LED on 2nd Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, LOW);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, HIGH);
         digitalWrite(col2, HIGH);
         digitalWrite(col3, HIGH);
         digitalWrite(col4, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
    }
    else if(Row == 4) {
       if(Col == 0) { // single LED on 1st Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, LOW);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, HIGH);
         digitalWrite(col2, LOW);
         digitalWrite(col3, LOW);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 1) { // single LED on 2nd Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, LOW);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, LOW);
         digitalWrite(col2, HIGH);
         digitalWrite(col3, LOW);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 2) { // single LED on 2nd Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, LOW);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, LOW);
         digitalWrite(col2, LOW);
         digitalWrite(col3, HIGH);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 3) { // single LED on 2nd Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, LOW);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, LOW);
         digitalWrite(col2, LOW);
         digitalWrite(col3, LOW);
         digitalWrite(col4, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 4) { // single LED on 2nd Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, LOW);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, HIGH);
         digitalWrite(col2, HIGH);
         digitalWrite(col3, HIGH);
         digitalWrite(col4, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
    }
    else if(Row == 5) {
       if(Col == 0) { // single LED on 1st Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, LOW);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, HIGH);
         digitalWrite(col2, LOW);
         digitalWrite(col3, LOW);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 1) { // single LED on 2nd Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, LOW);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, LOW);
         digitalWrite(col2, HIGH);
         digitalWrite(col3, LOW);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 2) { // single LED on 2nd Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, LOW);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, LOW);
         digitalWrite(col2, LOW);
         digitalWrite(col3, HIGH);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 3) { // single LED on 2nd Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, LOW);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, LOW);
         digitalWrite(col2, LOW);
         digitalWrite(col3, LOW);
         digitalWrite(col4, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 4) { // single LED on 2nd Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, LOW);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, HIGH);
         digitalWrite(col2, HIGH);
         digitalWrite(col3, HIGH);
         digitalWrite(col4, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
    }
    else if(Row == 6) {
       if(Col == 0) { // single LED on 1st Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, LOW);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, HIGH);
         digitalWrite(col2, LOW);
         digitalWrite(col3, LOW);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 1) { // single LED on 2nd Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, LOW);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, LOW);
         digitalWrite(col2, HIGH);
         digitalWrite(col3, LOW);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 2) { // single LED on 2nd Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, LOW);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, LOW);
         digitalWrite(col2, LOW);
         digitalWrite(col3, HIGH);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 3) { // single LED on 2nd Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, LOW);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, LOW);
         digitalWrite(col2, LOW);
         digitalWrite(col3, LOW);
         digitalWrite(col4, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 4) { // single LED on 2nd Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, LOW);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, HIGH);
         digitalWrite(col2, HIGH);
         digitalWrite(col3, HIGH);
         digitalWrite(col4, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
    }
    else {
       if(Col == 0) { // single LED on 1st Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, LOW);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, HIGH);
         digitalWrite(col2, LOW);
         digitalWrite(col3, LOW);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 1) { // single LED on 2nd Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, LOW);
         digitalWrite(col1, LOW);
         digitalWrite(col2, HIGH);
         digitalWrite(col3, LOW);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 2) { // single LED on 2nd Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, LOW);
         digitalWrite(col1, LOW);
         digitalWrite(col2, LOW);
         digitalWrite(col3, HIGH);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 3) { // single LED on 2nd Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, LOW);
         digitalWrite(col1, LOW);
         digitalWrite(col2, LOW);
         digitalWrite(col3, LOW);
         digitalWrite(col4, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 4) { // single LED on 2nd Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, LOW);
         digitalWrite(col1, HIGH);
         digitalWrite(col2, HIGH);
         digitalWrite(col3, HIGH);
         digitalWrite(col4, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
    }
  }
  else if(NumOfLed == 1) {
    if(Row == 0 || Row == 4) {
       if(Col == 0) { // single LED on 1st Col
         digitalWrite(row1, LOW);
         digitalWrite(row2, LOW);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, HIGH);
         digitalWrite(col2, LOW);
         digitalWrite(col3, LOW);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 1) { // single LED on 2nd Col
         digitalWrite(row1, LOW);
         digitalWrite(row2, LOW);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, LOW);
         digitalWrite(col2, HIGH);
         digitalWrite(col3, LOW);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 2) { // single LED on 2nd Col
         digitalWrite(row1, LOW);
         digitalWrite(row2, LOW);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, LOW);
         digitalWrite(col2, LOW);
         digitalWrite(col3, HIGH);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 3) { // single LED on 2nd Col
         digitalWrite(row1, LOW);
         digitalWrite(row2, LOW);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, LOW);
         digitalWrite(col2, LOW);
         digitalWrite(col3, LOW);
         digitalWrite(col4, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 4) { // single LED on 2nd Col
         digitalWrite(row1, LOW);
         digitalWrite(row2, LOW);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, HIGH);
         digitalWrite(col2, HIGH);
         digitalWrite(col3, HIGH);
         digitalWrite(col4, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
    }
    else if(Row == 1 || Row == 5) {
       if(Col == 0) { // single LED on 1st Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, LOW);
         digitalWrite(row4, LOW);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, HIGH);
         digitalWrite(col2, LOW);
         digitalWrite(col3, LOW);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 1) { // single LED on 2nd Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, LOW);
         digitalWrite(row4, LOW);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, LOW);
         digitalWrite(col2, HIGH);
         digitalWrite(col3, LOW);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 2){ // single LED line on all Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, LOW);
         digitalWrite(row4, LOW);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, LOW);
         digitalWrite(col2, LOW);
         digitalWrite(col3, HIGH);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 3){ // single LED line on all Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, LOW);
         digitalWrite(row4, LOW);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, LOW);
         digitalWrite(col2, LOW);
         digitalWrite(col3, LOW);
         digitalWrite(col4, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 4){ // single LED line on all Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, LOW);
         digitalWrite(row4, LOW);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, HIGH);
         digitalWrite(col2, HIGH);
         digitalWrite(col3, HIGH);
         digitalWrite(col4, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
    }
    else if(Row == 2 || Row == 6) {
       if(Col == 0) { // single LED on 1st Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, LOW);
         digitalWrite(row6, LOW);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, HIGH);
         digitalWrite(col2, LOW);
         digitalWrite(col3, LOW);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 1) { // single LED on 2nd Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, LOW);
         digitalWrite(row6, LOW);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, LOW);
         digitalWrite(col2, HIGH);
         digitalWrite(col3, LOW);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 2) { // single LED line on all Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, LOW);
         digitalWrite(row6, LOW);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, LOW);
         digitalWrite(col2, LOW);
         digitalWrite(col3, HIGH);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 3) { // single LED line on all Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, LOW);
         digitalWrite(row6, LOW);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, LOW);
         digitalWrite(col2, LOW);
         digitalWrite(col3, LOW);
         digitalWrite(col4, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 4) { // single LED line on all Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, LOW);
         digitalWrite(row6, LOW);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, HIGH);
         digitalWrite(col2, HIGH);
         digitalWrite(col3, HIGH);
         digitalWrite(col4, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
    }
    else {
       if(Col == 0) { // single LED on 1st Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, LOW);
         digitalWrite(row8, LOW);
         digitalWrite(col1, HIGH);
         digitalWrite(col2, LOW);
         digitalWrite(col3, LOW);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 1) { // single LED on 2nd Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, LOW);
         digitalWrite(row8, LOW);
         digitalWrite(col1, LOW);
         digitalWrite(col2, HIGH);
         digitalWrite(col3, LOW);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 2) { // single LED on 2nd Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, LOW);
         digitalWrite(row8, LOW);
         digitalWrite(col1, LOW);
         digitalWrite(col2, LOW);
         digitalWrite(col3, HIGH);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 3) { // single LED on 2nd Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, LOW);
         digitalWrite(row8, LOW);
         digitalWrite(col1, LOW);
         digitalWrite(col2, LOW);
         digitalWrite(col3, LOW);
         digitalWrite(col4, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 4) { // single LED on 2nd Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, LOW);
         digitalWrite(row8, LOW);
         digitalWrite(col1, HIGH);
         digitalWrite(col2, HIGH);
         digitalWrite(col3, HIGH);
         digitalWrite(col4, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
    }
  }
  else if(NumOfLed == 2) {
    if( Row == 0 || Row == 2 || Row == 4 || Row == 6) {
       if(Col == 0) { // single LED on 1st Col
         digitalWrite(row1, LOW);
         digitalWrite(row2, LOW);
         digitalWrite(row3, LOW);
         digitalWrite(row4, LOW);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, HIGH);
         digitalWrite(col2, LOW);
         digitalWrite(col3, LOW);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 1) { // single LED on 2nd Col
         digitalWrite(row1, LOW);
         digitalWrite(row2, LOW);
         digitalWrite(row3, LOW);
         digitalWrite(row4, LOW);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, LOW);
         digitalWrite(col2, HIGH);
         digitalWrite(col3, LOW);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 2) { // single LED line on all Col
         digitalWrite(row1, LOW);
         digitalWrite(row2, LOW);
         digitalWrite(row3, LOW);
         digitalWrite(row4, LOW);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, LOW);
         digitalWrite(col2, LOW);
         digitalWrite(col3, HIGH);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 3) { // single LED line on all Col
         digitalWrite(row1, LOW);
         digitalWrite(row2, LOW);
         digitalWrite(row3, LOW);
         digitalWrite(row4, LOW);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, LOW);
         digitalWrite(col2, LOW);
         digitalWrite(col3, LOW);
         digitalWrite(col4, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 4) { // single LED line on all Col
         digitalWrite(row1, LOW);
         digitalWrite(row2, LOW);
         digitalWrite(row3, LOW);
         digitalWrite(row4, LOW);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, HIGH);
         digitalWrite(col2, HIGH);
         digitalWrite(col3, HIGH);
         digitalWrite(col4, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
    }
    else { // 4개씩 켜지는 경우 위쪽 Row
       if(Col == 0) { // single LED on 1st Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, LOW);
         digitalWrite(row6, LOW);
         digitalWrite(row7, LOW);
         digitalWrite(row8, LOW);
         digitalWrite(col1, HIGH);
         digitalWrite(col2, LOW);
         digitalWrite(col3, LOW);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 1) { // single LED on 2nd Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, LOW);
         digitalWrite(row6, LOW);
         digitalWrite(row7, LOW);
         digitalWrite(row8, LOW);
         digitalWrite(col1, LOW);
         digitalWrite(col2, HIGH);
         digitalWrite(col3, LOW);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 2) { // single LED on 2nd Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, LOW);
         digitalWrite(row6, LOW);
         digitalWrite(row7, LOW);
         digitalWrite(row8, LOW);
         digitalWrite(col1, LOW);
         digitalWrite(col2, LOW);
         digitalWrite(col3, HIGH);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 3) { // single LED on 2nd Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, LOW);
         digitalWrite(row6, LOW);
         digitalWrite(row7, LOW);
         digitalWrite(row8, LOW);
         digitalWrite(col1, LOW);
         digitalWrite(col2, LOW);
         digitalWrite(col3, LOW);
         digitalWrite(col4, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
       else if(Col == 4) { // single LED on 2nd Col
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, LOW);
         digitalWrite(row6, LOW);
         digitalWrite(row7, LOW);
         digitalWrite(row8, LOW);
         digitalWrite(col1, HIGH);
         digitalWrite(col2, HIGH);
         digitalWrite(col3, HIGH);
         digitalWrite(col4, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
       }
    }
  }
  else { // Turn 8 LEDs On
    if(Col == 0) {
         digitalWrite(row1, LOW);
         digitalWrite(row2, LOW);
         digitalWrite(row3, LOW);
         digitalWrite(row4, LOW);
         digitalWrite(row5, LOW);
         digitalWrite(row6, LOW);
         digitalWrite(row7, LOW);
         digitalWrite(row8, LOW);
         digitalWrite(col1, HIGH);
         digitalWrite(col2, LOW);
         digitalWrite(col3, LOW);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
    }
    else if(Col == 1) {
         digitalWrite(row1, LOW);
         digitalWrite(row2, LOW);
         digitalWrite(row3, LOW);
         digitalWrite(row4, LOW);
         digitalWrite(row5, LOW);
         digitalWrite(row6, LOW);
         digitalWrite(row7, LOW);
         digitalWrite(row8, LOW);
         digitalWrite(col1, LOW);
         digitalWrite(col2, HIGH);
         digitalWrite(col3, LOW);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
    }
    else if(Col == 2) {
         digitalWrite(row1, LOW);
         digitalWrite(row2, LOW);
         digitalWrite(row3, LOW);
         digitalWrite(row4, LOW);
         digitalWrite(row5, LOW);
         digitalWrite(row6, LOW);
         digitalWrite(row7, LOW);
         digitalWrite(row8, LOW);
         digitalWrite(col1, LOW);
         digitalWrite(col2, LOW);
         digitalWrite(col3, HIGH);
         digitalWrite(col4, LOW);
         delayMicroseconds(delayForLed);
         TurnOffAll();
    }
    else if(Col == 3) {
         digitalWrite(row1, LOW);
         digitalWrite(row2, LOW);
         digitalWrite(row3, LOW);
         digitalWrite(row4, LOW);
         digitalWrite(row5, LOW);
         digitalWrite(row6, LOW);
         digitalWrite(row7, LOW);
         digitalWrite(row8, LOW);
         digitalWrite(col1, LOW);
         digitalWrite(col2, LOW);
         digitalWrite(col3, LOW);
         digitalWrite(col4, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
    }
    else if(Col == 4) {
         digitalWrite(row1, LOW);
         digitalWrite(row2, LOW);
         digitalWrite(row3, LOW);
         digitalWrite(row4, LOW);
         digitalWrite(row5, LOW);
         digitalWrite(row6, LOW);
         digitalWrite(row7, LOW);
         digitalWrite(row8, LOW);
         digitalWrite(col1, HIGH);
         digitalWrite(col2, HIGH);
         digitalWrite(col3, HIGH);
         digitalWrite(col4, HIGH);
         delayMicroseconds(delayForLed);
         TurnOffAll();
    }
  }
}

int TurnOffAll(){
         digitalWrite(row1, HIGH);
         digitalWrite(row2, HIGH);
         digitalWrite(row3, HIGH);
         digitalWrite(row4, HIGH);
         digitalWrite(row5, HIGH);
         digitalWrite(row6, HIGH);
         digitalWrite(row7, HIGH);
         digitalWrite(row8, HIGH);
         digitalWrite(col1, HIGH);
         digitalWrite(col2, HIGH);
         digitalWrite(col3, HIGH);
         digitalWrite(col4, HIGH);
}
