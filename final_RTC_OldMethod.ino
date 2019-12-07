#include <Wire.h>
#include "RTClib.h"
#define DEL 4000

int k;

RTC_DS1307 RTC;

//SDA should be A4, SCL should be A5
////////////////////////////////////////////////////////
//
//         col[0]    col[1]    col[2]   col[3]   col[4]
// row[0]    열        한        다       세       네
// row[1]    두        여        섯       일       곱
// row[2]    여        덟        아       홉       시
// row[3]    정        각        이       삼       십
// row[4]    사        오        십       오       분
//
//////////////////////////////////////////////////////////

//Highest Lux : 470[Ohm] For Diode
int col[5] = {2,3,4,5,6};
int row[5] = {8,9,10,11,12};

int i,j;

int hoursColumn [12][3][5] = {
  {{1,0,0,0,0},{1,0,0,0,0},{0,0,0,0,1}}, // 12h
  {{0,1,0,0,0},{0,0,0,0,0},{0,0,0,0,1}}, // 1h
  {{0,0,0,0,0},{1,0,0,0,0},{0,0,0,0,1}}, // 2h
  {{0,0,0,1,0},{0,0,0,0,0},{0,0,0,0,1}}, // 3h
  {{0,0,0,0,1},{0,0,0,0,0},{0,0,0,0,1}}, // 4h
  {{0,0,1,0,0},{0,0,1,0,0},{0,0,0,0,1}}, // 5h
  {{0,0,0,0,0},{0,1,1,0,0},{0,0,0,0,1}}, // 6h
  {{0,0,0,0,0},{0,0,0,1,1},{0,0,0,0,1}}, // 7h
  {{0,0,0,0,0},{0,0,0,0,0},{1,1,0,0,1}}, // 8h
  {{0,0,0,0,0},{0,0,0,0,0},{0,0,1,1,1}}, // 9h
  {{1,0,0,0,0},{0,0,0,0,0},{0,0,0,0,1}}, // 10h
  {{1,1,0,1,0},{0,0,0,0,0},{0,0,0,0,1}}  // 11h
};

int minutesColumn [12][2][5] = {
  {{1,1,0,0,0},{0,0,0,0,0}}, //00
  {{0,0,0,0,0},{0,0,0,1,1}}, //05
  {{0,0,0,0,1},{0,0,0,0,1}}, //10
  {{0,0,0,0,0},{0,0,1,1,1}}, //15
  {{0,0,1,0,0},{0,0,1,0,1}}, //20
  {{0,0,1,0,0},{0,0,1,1,1}}, //25
  {{0,0,0,1,1},{0,0,0,0,1}}, //30
  {{0,0,0,1,1},{0,0,0,1,1}}, //35
  {{0,0,0,0,0},{1,0,1,0,1}}, //40
  {{0,0,0,0,0},{1,0,1,1,1}}, //45
  {{0,0,0,0,0},{0,1,1,0,1}}, //50
  {{0,0,0,0,0},{0,1,1,1,1}} //55
};

int timeRowForHour[5][5] = {
  {0,1,1,1,1},
  {1,0,1,1,1},
  {1,1,0,1,1},
  {1,1,1,1,1},
  {1,1,1,1,1}
};


int timeRowForMinute[5][5] = {
  {1,1,1,1,1},
  {1,1,1,1,1},
  {1,1,1,1,1},
  {1,1,1,0,1},
  {1,1,1,1,0}
};
void setup() {
  Serial.begin(9600);
  Wire.begin();
  RTC.begin();
  for(i = 0; i < 5; i++){
    pinMode(col[i],OUTPUT);
    pinMode(row[i],OUTPUT);
  }
  //RTC.adjust(DateTime("Dec 7 2019", "17:55:40"));  
  TurnOffAll();
}

void loop() {
  // put your main code here, to run repeatedly:
  DateTime now = RTC.now();
  
    Serial.print(now.hour(),DEC);
    Serial.print(" : ");
    Serial.print(now.minute(),DEC);
    Serial.print(" : ");
    Serial.print(now.second(),DEC);
    Serial.println();

    if(now.hour()==0 || now.hour()==12){
      TurnOffAll();
      digitalWrite(col[0],HIGH);
      digitalWrite(row[0],LOW);
      digitalWrite(row[1],LOW);
      delayMicroseconds(DEL);
      TurnOffAll();
      digitalWrite(col[4],HIGH);
      digitalWrite(row[2],LOW);
      delayMicroseconds(DEL);
      TurnOnLightForMinute();
    }
    else if(now.hour()==1 || now.hour()== 13){
      TurnOffAll();
      digitalWrite(col[1],HIGH);
      digitalWrite(row[0],LOW);
      delayMicroseconds(DEL);
      TurnOffAll();
      digitalWrite(col[4],HIGH);
      digitalWrite(row[2],LOW);
      delayMicroseconds(DEL);
      TurnOnLightForMinute();
    }
    else if(now.hour()==2 || now.hour() ==14){
      TurnOffAll();
      digitalWrite(col[0],HIGH);
      digitalWrite(row[1],LOW);
      delayMicroseconds(DEL);
      TurnOffAll();
      digitalWrite(col[4],HIGH);
      digitalWrite(row[2],LOW);
      delayMicroseconds(DEL);
      TurnOnLightForMinute();
    }
    else if(now.hour()==3 || now.hour() ==15){
      TurnOffAll();
      digitalWrite(col[3],HIGH);
      digitalWrite(row[0],LOW);
      digitalWrite(row[2],LOW);
      delayMicroseconds(DEL);
      TurnOnLightForMinute();
    }
    else if(now.hour()==4 || now.hour() ==16){
      TurnOffAll();
      digitalWrite(col[4],HIGH);
      digitalWrite(row[0],LOW);
      digitalWrite(row[2],LOW);
      delayMicroseconds(DEL);
      TurnOnLightForMinute();
    }
    else if(now.hour()==5 || now.hour() ==17){
      TurnOffAll();
      digitalWrite(col[1],HIGH);
      digitalWrite(row[1],LOW);
      digitalWrite(row[2],LOW);
      delayMicroseconds(DEL);
      TurnOffAll();
      digitalWrite(col[4],HIGH);
      digitalWrite(row[2],LOW);
      delayMicroseconds(DEL);
      TurnOnLightForMinute();
    }
    else if(now.hour()==6 || now.hour() ==18){
      TurnOffAll();
      digitalWrite(col[1],HIGH);
      digitalWrite(col[2],HIGH);
      digitalWrite(row[1],LOW);
      delayMicroseconds(DEL);
      TurnOffAll();
      digitalWrite(col[4],HIGH);
      digitalWrite(row[2],LOW);
      delayMicroseconds(DEL);
      TurnOnLightForMinute();
    }
    else if(now.hour()==7 || now.hour() ==19){
      TurnOffAll();
      digitalWrite(col[3],HIGH);
      digitalWrite(col[4],HIGH);
      digitalWrite(row[1],LOW);
      delayMicroseconds(DEL);
      TurnOffAll();
      digitalWrite(col[4],HIGH);
      digitalWrite(row[2],LOW);
      delayMicroseconds(DEL);
      TurnOnLightForMinute();
    }
    else if(now.hour()==8 || now.hour() ==20){
      TurnOffAll();
      digitalWrite(col[0],HIGH);
      digitalWrite(col[1],HIGH);
      digitalWrite(col[4],HIGH);
      digitalWrite(row[2],LOW);
      delayMicroseconds(DEL);
      TurnOnLightForMinute();
    }
    else if(now.hour()==9 || now.hour() ==21){
      TurnOffAll();
      digitalWrite(col[2],HIGH);
      digitalWrite(col[3],HIGH);
      digitalWrite(col[4],HIGH);
      digitalWrite(row[2],LOW);
      delayMicroseconds(DEL);
      TurnOnLightForMinute();
    }
    else if(now.hour()==10 || now.hour() ==22){
      TurnOffAll();
      digitalWrite(col[0],HIGH);
      digitalWrite(row[0],LOW);
      delayMicroseconds(DEL);
      TurnOffAll();
      digitalWrite(col[4],HIGH);
      digitalWrite(row[2],LOW);
      delayMicroseconds(DEL);
      TurnOnLightForMinute();
    }
    else{
      TurnOffAll();
      digitalWrite(col[0],HIGH);
      digitalWrite(col[1],HIGH);
      digitalWrite(row[0],LOW);
      delayMicroseconds(DEL);
      TurnOffAll();
      digitalWrite(col[4],HIGH);
      digitalWrite(row[2],LOW);
      delayMicroseconds(DEL);
      TurnOnLightForMinute();
    }
}
/*
void TurnOnHourRowInOrder(){
  for(i=0; i<3; i++){
    for(j=0; j<5; j++){
      digitalWrite(row[i],timeRow[i][j]);
    }
  }
}

void TurnOnMinuteRowInOrder(){
  for(i=3; i<5; i++){
    for(j=0; j<5; j++){
      digitalWrite(row[i],timeRow[i][j]);
    }
  }
}*/

void TurnOffAll(){
  for(i=0; i<5; i++){
    digitalWrite(row[i], 1);
    digitalWrite(col[i], 0);
  }
}

void TurnOffHours(){
  for(i=0; i<5; i++){
    if(i<3){
      digitalWrite(row[i],1);
    }
    digitalWrite(col[i],0);
  }
}

void TurnOffMinutes(){
  for(i=0; i<5; i++){
    digitalWrite(row[i],1);
    digitalWrite(col[i],0);
  }
}

void TurnOnLightForMinute(){
  
  DateTime now = RTC.now();

  if(now.minute()<5 && now.minute()>=0){
    TurnOffAll();
    digitalWrite(col[0],HIGH);
    digitalWrite(col[1],HIGH);
    digitalWrite(row[3],LOW);
    delayMicroseconds(DEL);
  }
  else if(now.minute()<10 && now.minute()>=5){
    TurnOffAll();
    digitalWrite(col[3],HIGH);
    digitalWrite(col[4],HIGH);
    digitalWrite(row[4],LOW);
    delayMicroseconds(DEL);
  }
  else if(now.minute()<15 && now.minute()>=10){
    TurnOffAll();
    digitalWrite(col[4],HIGH);
    digitalWrite(row[3],LOW);
    digitalWrite(row[4],LOW);
    delayMicroseconds(DEL);
  }
  else if(now.minute()<20 && now.minute()>=15){
    TurnOffAll();
    digitalWrite(col[2],HIGH);
    digitalWrite(col[3],HIGH);
    digitalWrite(col[4],HIGH);
    digitalWrite(row[4],LOW);
    delayMicroseconds(DEL);
  }
  else if(now.minute()<25 && now.minute()>=20){
    TurnOffAll();
    digitalWrite(col[2],HIGH);
    digitalWrite(row[3],LOW);
    digitalWrite(row[4],LOW);
    delayMicroseconds(DEL);
    TurnOffAll();
    digitalWrite(col[4],HIGH);
    digitalWrite(row[4],LOW);
    delayMicroseconds(DEL);
  }
  else if(now.minute()<30 && now.minute()>=25){
    TurnOffAll();
    digitalWrite(col[2],HIGH);
    digitalWrite(row[3],LOW);
    delayMicroseconds(DEL);
    TurnOffAll();
    digitalWrite(col[2],HIGH);
    digitalWrite(col[3],HIGH);
    digitalWrite(col[4],HIGH);
    digitalWrite(row[4],LOW);
    delayMicroseconds(DEL);
  }
  else if(now.minute()<35 && now.minute()>=30){
    TurnOffAll();
    digitalWrite(col[3],HIGH);
    digitalWrite(col[4],HIGH);
    digitalWrite(row[3],LOW);
    delayMicroseconds(DEL);
    TurnOffAll();
    digitalWrite(col[4],HIGH);
    digitalWrite(row[4],LOW);
    delayMicroseconds(DEL);
  }
  else if(now.minute()<40 && now.minute()>=35){
    TurnOffAll();
    digitalWrite(col[3],HIGH);
    digitalWrite(col[4],HIGH);
    digitalWrite(row[3],LOW);
    digitalWrite(row[4],LOW);
    delayMicroseconds(DEL);
  }
  else if(now.minute()<45 && now.minute()>=40){
    TurnOffAll();
    digitalWrite(col[0],HIGH);
    digitalWrite(col[2],HIGH);
    digitalWrite(col[4],HIGH);
    digitalWrite(row[4],LOW);
    delayMicroseconds(DEL);
  }
  else if(now.minute()<50 && now.minute()>=45){
    TurnOffAll();
    digitalWrite(col[0],HIGH);
    digitalWrite(col[2],HIGH);
    digitalWrite(col[3],HIGH);
    digitalWrite(col[4],HIGH);
    digitalWrite(row[4],LOW);
    delayMicroseconds(DEL);
  }
  else if(now.minute()<55 && now.minute()>=50){
    TurnOffAll();
    digitalWrite(col[1],HIGH);
    digitalWrite(col[2],HIGH);
    digitalWrite(col[4],HIGH);
    digitalWrite(row[4],LOW);
    delayMicroseconds(DEL);
  }
  else{
    TurnOffAll();
    digitalWrite(col[1],HIGH);
    digitalWrite(col[2],HIGH);
    digitalWrite(col[3],HIGH);
    digitalWrite(col[4],HIGH);
    digitalWrite(row[4],LOW);
    delayMicroseconds(DEL);
  }
}
