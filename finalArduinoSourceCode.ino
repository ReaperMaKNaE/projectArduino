/*
 * Copyright 2019 Lee, Kang, Jeong, ALl rights reserved.
 * 
 * ArduinoFianlProject_ver_1.0.ino
 * 
 * SKKU
 * School of Mechanical Engineering
 * School of Electromagnetic Engineering
 * Undergraduated student
 * 
 * 2019.11.04
 * 2019.11.06
 * 2019.11.12
 * 
 * Modified history :
 * 
 *            2019.11.04, TFT LCD module is added
 *            2019.11.06, Library for prediction is added
 *            2019.11.12, Add Dust sensor with communication
 *            
 *   NOTE : To make Air cleaner for the weak and the elderly,
 *          Smart functions are used in air cleaner. 
 *          
 *          I) Clock
 *          II) Auto Alarm for Gas
 *          III) Wireless communication by using bluetooth or WIFI
 *          IV) Check temperature, humidity
 *          V) Auto-Operating System
 */

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>
#include "LedControlMS.h"
#include "SoftwareSerial.h"
#define NBR_MTX 1
#include "RTClib.h"
#include <Wire.h>
#include "DHT11.h"
#include <ForWarning_1.0.h>
#include <MsTimer2.h>

#define SerialDebugging true

int dustAnalogPin = A0;
int gasSensorPin = A1;
int dustDigitalPin = 13;
int dht11Pin = 3;
int bluetoothRXDPin = 4;
int bluetoothTXDPin = 5;
int UnoRXDPin = 34;
int UnoTXDPin = 36;
//# of TFT LCD  = 2
//5 pines are needed more
int TFT_SCLK = 8;  //CLK
int TFT_MOSI = 9;   //MOSI is same as SDA/SDI
int TFT_DC = 10;     //DC is same as SS(Display collect)
int TFT_RST = 11;
int TFT_CS = 12;
int buzzerPin = 6;
int ledMatrixDIN = 22;
int ledMatrixCLK = 23;
int ledMatrixCS = 24;

int TFT2_SCLK = 30;  //CLK
int TFT2_MOSI = 32;   //MOSI is same as SDA/SDI
int TFT2_DC = 34;     //DC is same as SS(Display collect)
int TFT2_RST = 36;
int TFT2_CS = 38;

//For Dust sensor
//sampling time 280ms
//waiting time 40ms
int sampling = 280;
int waiting = 40;
float stopTimeForDust = 9680;
int checkSampling = 0;
int checkWaiting = 0;
int checkStoptime = 0;
int dustDensityug;

//15+5+SDA,SDL(2)= 20(analog 2/ digital 18);
//Wifi is not decided yet
//int wifiPin = 4;

SoftwareSerial bluetoothModule(bluetoothTXDPin, bluetoothRXDPin);
ForWarning dataPrediction;
SoftwareSerial CommuWithUno(UnoTXDPin, UnoRXDPin);
DHT11 dht11(dht11Pin);
RTC_DS1307 RTC;

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
Adafruit_ST7735 tft2 = Adafruit_ST7735(TFT2_CS, TFT2_DC, TFT2_MOSI, TFT2_SCLK, TFT2_RST);

LedControl lc = LedControl(ledMatrixDIN,ledMatrixCLK,ledMatrixCS,NBR_MTX);

unsigned long previousTime = 0;
//unsigned long previousCheckDustTime = 0;

//Define hours and minutes for HanguelTime
byte hours[12][3]={
  {B10000000,B10000000,B00001000},
  {B01000000,B00000000,B00001000},
  {B00000000,B10000000,B00001000},
  {B00010000,B00000000,B00001000},
  {B00001000,B00000000,B00001000},
  {B00100000,B00100000,B00001000},
  {B00000000,B01100000,B00001000},
  {B00000000,B00011000,B00001000},
  {B00000000,B00000000,B11001000},
  {B00000000,B00000000,B00111000},
  {B10000000,B00000000,B00001000},
  {B11000000,B00000000,B00001000}
};

byte minutes[12][2]={
  {B11000000,B00000000},
  {B00000000,B00011000},
  {B00001000,B00001000},
  {B00000000,B00111000},
  {B00100000,B00101000},
  {B00100000,B00111000},
  {B00011000,B00001000},
  {B00011000,B0001000},
  {B00000000,B10101000},
  {B00000000,B10111000},
  {B00000000,B01101000},
  {B00000000,B01111000}
};

void setup(void) {
  Serial.begin(9600);

  //Start bluetooth Module
  bluetoothModule.begin(9600);
  //CommuWithUno.begin(9600);
  
  //Clear LED matrix
  for(int i=0;i<NBR_MTX;i++){
    lc.shutdown(i,false);
    lc.setIntensity(i,7);
    lc.clearDisplay(i);
  }
  Wire.begin();
  RTC.begin();
  RTC.adjust(DateTime("Nov 5 2019", "19:10:00"));
  dataPrediction.resetAll();
  dataPrediction.getNumberOfData(10);

  //digitalOUT(buzzer & dust)
  pinMode(buzzerPin,OUTPUT);
  pinMode(dustDigitalPin,OUTPUT);
  
  // Use this initializer if using a 1.8" TFT screen:
  tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab
  tft.fillScreen(ST77XX_BLACK);
  //Rotate TFT LCD Screen
  tft.setRotation(3);
  tft2.initR(INITR_BLACKTAB);
  tft2.fillScreen(ST77XX_BLACK);
  tft2.setRotation(3);
}
  //dustSensor

void loop() {

  //To use millis, use unsigned long
  unsigned long currentTime = millis();
  //unsigned long dustSensorTime = micros();
  DateTime now = RTC.now();

  //Declare variables
  float temp, humi;
  int dustValue = 0;
  //float dustDensityug = 0;
  int checkDust = 0;
  /*
  if(checkSampling == 0){
    digitalWrite(dustDigitalPin, LOW);
    if(dustSensorTime > previousCheckDustTime + sampling){
      dustValue = analogRead(dustAnalogPin);
      checkSampling = 1;
      previousCheckDustTime = dustSensorTime;
      Serial.print("checkSampling check!");
      Serial.println(dustSensorTime);
    }
  } else if(checkSampling == 1){
    if(checkWaiting == 0){
      if(dustSensorTime>previousCheckDustTime+waiting){
        digitalWrite(dustDigitalPin, HIGH);
        checkWaiting = 1;
        previousCheckDustTime = dustSensorTime;
        Serial.print("  checkWaiting check!");
        Serial.println(dustSensorTime);
      }
    } 
    else {
      if(dustSensorTime>previousCheckDustTime+stopTimeForDust){
        dustDensityug = (float)(0.172*(dustValue*(5.0/1024))-0.099)*1000;
        //Serial.print("Dust density [ug/m^3]: ");
        //Serial.println(dustDensityug);
        previousCheckDustTime = dustSensorTime;
        checkSampling=0;
        checkWaiting =0;
        Serial.print("  ALL check!");
        Serial.println(dustSensorTime);
      }
    }
  }*/
  float dustData;
  int filteredDustData;
  
  if(Serial.available()){
    dustDensityug = Serial.parseFloat();
  }
  /*
  dataPrediction.SaveDataOfDust(dustData);
  filteredDustData = dataPrediction.CalculateFilteredDataForDust();
  */
  dataPrediction.SaveDataOfDust(dustDensityug);
  Serial.println(dustDensityug);
  filteredDustData = dataPrediction.CalculateFilteredDataForDust();
  /*
  Serial.print("Dust density : ");
  Serial.print(dustDensityug);
  Serial.print(" Filtered Dust Density : ");
  Serial.println(filteredDustData);*/
  //Use millis, check humi, temp, time
  //Additionally, send to bluetooth
  //At RTC, only print hours.
  //Minute will use the other one

  if(currentTime>previousTime+2000){
    if(now.hour()==0 || now.hour()==12){
      clearTimeDisplayHour();
      lc.setColumn(0,7,hours[0][0]);
      lc.setColumn(0,6,hours[0][1]);
      lc.setColumn(0,5,hours[0][2]);
      TurnOnLightForMinute();
    }
    else if(now.hour()==1 || now.hour()== 13){
      clearTimeDisplayHour();
      lc.setColumn(0,7,hours[1][0]);
      lc.setColumn(0,6,hours[1][1]);
      lc.setColumn(0,5,hours[1][2]);
      TurnOnLightForMinute();
    }
    else if(now.hour()==2 || now.hour() ==14){
      clearTimeDisplayHour();
      lc.setColumn(0,7,hours[2][0]);
      lc.setColumn(0,6,hours[2][1]);
      lc.setColumn(0,5,hours[2][2]);
      TurnOnLightForMinute();
    }
    else if(now.hour()==3 || now.hour() ==15){
      clearTimeDisplayHour();
      lc.setColumn(0,7,hours[3][0]);
      lc.setColumn(0,6,hours[3][1]);
      lc.setColumn(0,5,hours[3][2]);
      TurnOnLightForMinute();
    }
    else if(now.hour()==4 || now.hour() ==16){
      clearTimeDisplayHour();
      lc.setColumn(0,7,hours[4][0]);
      lc.setColumn(0,6,hours[4][1]);
      lc.setColumn(0,5,hours[4][2]);
      TurnOnLightForMinute();
    }
    else if(now.hour()==5 || now.hour() ==17){
      clearTimeDisplayHour();
      lc.setColumn(0,7,hours[5][0]);
      lc.setColumn(0,6,hours[5][1]);
      lc.setColumn(0,5,hours[5][2]);
      TurnOnLightForMinute();
    }
    else if(now.hour()==6 || now.hour() ==18){
      clearTimeDisplayHour();
      lc.setColumn(0,7,hours[6][0]);
      lc.setColumn(0,6,hours[6][1]);
      lc.setColumn(0,5,hours[6][2]);
      TurnOnLightForMinute();
    }
    else if(now.hour()==7 || now.hour() ==19){
      clearTimeDisplayHour();
      lc.setColumn(0,7,hours[7][0]);
      lc.setColumn(0,6,hours[7][1]);
      lc.setColumn(0,5,hours[7][2]);
      TurnOnLightForMinute();
    }
    else if(now.hour()==8 || now.hour() ==20){
      clearTimeDisplayHour();
      lc.setColumn(0,7,hours[8][0]);
      lc.setColumn(0,6,hours[8][1]);
      lc.setColumn(0,5,hours[8][2]);
      TurnOnLightForMinute();
    }
    else if(now.hour()==9 || now.hour() ==21){
      clearTimeDisplayHour();
      lc.setColumn(0,7,hours[9][0]);
      lc.setColumn(0,6,hours[9][1]);
      lc.setColumn(0,5,hours[9][2]);
      TurnOnLightForMinute();
    }
    else if(now.hour()==10 || now.hour() ==22){
      clearTimeDisplayHour();
      lc.setColumn(0,7,hours[10][0]);
      lc.setColumn(0,6,hours[10][1]);
      lc.setColumn(0,5,hours[10][2]);
      TurnOnLightForMinute();
    }
    else{
      clearTimeDisplayHour();
      lc.setColumn(0,7,hours[11][0]);
      lc.setColumn(0,6,hours[11][1]);
      lc.setColumn(0,5,hours[11][2]);
      TurnOnLightForMinute();
    }
    dht11.read(humi,temp);
    bluetoothModule.print("습도 : ");
    bluetoothModule.print(humi);
    bluetoothModule.print(" 온도 : ");
    bluetoothModule.println(temp);
    bluetoothModule.print("가스 :");
    bluetoothModule.print(analogRead(gasSensorPin));
    bluetoothModule.print(" 먼지 :");
    bluetoothModule.print(filteredDustData);
    previousTime=currentTime;
  }
/*
  //Check output values by comparing Serial monitor values
  Serial.print("Humidity : ");
  Serial.print(humi);
  Serial.print("  Temperature : ");
  Serial.print(temp);
  Serial.print("  Time  ");
  Serial.print(now.hour());
  Serial.print(":");
  Serial.print(now.minute());
  Serial.print("        Amount of Gas: ");
  Serial.println(analogRead(gasSensorPin));

  if(Serial.available()){
    float dust = (float)Serial.read();
  }*/
  //When concentration of gas is too high(here, 500)
  //HIGH to buzzer
  /*
  if(analogRead(gasSensorPin)>=500){
    digitalWrite(buzzerPin,HIGH);
  }
  else{
    digitalWrite(buzzerPin,LOW);
  }
*/
  //TFT LCD output
  
  //tft.fillRect(화면의 왼쪽위부터 우측으로, 화면의 왼쪽위부터 아래로, 상자의 가로길이, 상자의 세로길이, 색깔);
  //tft.fillRoundRect(50,20,40,30,ST7735_BLACK);
  //위 방법 매우 별로. 지우는게 화면에보임
  tft.setCursor(0,0);
  //위 지우는 방법을 아래 textColor에서 해결.
  //setTextColor(쓸 글씨 색, overwrite할 글씨색)
  tft.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
  tft.setTextSize(3);
  tft.println("  GAS : ");
  tft.print("  ");
  tft.print(analogRead(gasSensorPin));
  tft.println(" ");
  tft.println("");
  tft.println(" DUST :");
  tft.print("  ");
  tft.print(filteredDustData);
  tft.print("         ");
  

  
  tft2.setCursor(0,0);
  //위 지우는 방법을 아래 textColor에서 해결.
  //setTextColor(쓸 글씨 색, overwrite할 글씨색)
  tft2.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
  tft2.setTextSize(3);
  tft2.println("  TEMP :");
  tft2.print(" ");
  tft2.print(temp);
  tft2.println("");
  tft2.println("");
  tft2.println(" HUMI :");
  tft2.print(" ");
  tft2.println(humi);
}

//Turn on LED as following minute value of RTC
void TurnOnLightForMinute(){
  
  DateTime now = RTC.now();
  
  if(now.minute()<5 && now.minute()>=0){
    clearTimeDisplayMinutes();
    lc.setColumn(0,4,minutes[0][0]);
    lc.setColumn(0,3,minutes[0][1]);
  }
  else if(now.minute()<10 && now.minute()>=5){
    clearTimeDisplayMinutes();
    lc.setColumn(0,4,minutes[1][0]);
    lc.setColumn(0,3,minutes[1][1]);
  }
  else if(now.minute()<15 && now.minute()>=10){
    clearTimeDisplayMinutes();
    lc.setColumn(0,4,minutes[2][0]);
    lc.setColumn(0,3,minutes[2][1]);
  }
  else if(now.minute()<20 && now.minute()>=15){
    clearTimeDisplayMinutes();
    lc.setColumn(0,4,minutes[3][0]);
    lc.setColumn(0,3,minutes[3][1]);
  }
  else if(now.minute()<25 && now.minute()>=20){
    clearTimeDisplayMinutes();
    lc.setColumn(0,4,minutes[4][0]);
    lc.setColumn(0,3,minutes[4][1]);
  }
  else if(now.minute()<30 && now.minute()>=25){
    clearTimeDisplayMinutes();
    lc.setColumn(0,4,minutes[5][0]);
    lc.setColumn(0,3,minutes[5][1]);
  }
  else if(now.minute()<35 && now.minute()>=30){
    clearTimeDisplayMinutes();
    lc.setColumn(0,4,minutes[6][0]);
    lc.setColumn(0,3,minutes[6][1]);
  }
  else if(now.minute()<40 && now.minute()>=35){
    clearTimeDisplayMinutes();
    lc.setColumn(0,4,minutes[7][0]);
    lc.setColumn(0,3,minutes[7][1]);
  }
  else if(now.minute()<45 && now.minute()>=40){
    clearTimeDisplayMinutes();
    lc.setColumn(0,4,minutes[8][0]);
    lc.setColumn(0,3,minutes[8][1]);
  }
  else if(now.minute()<50 && now.minute()>=45){
    clearTimeDisplayMinutes();
    lc.setColumn(0,4,minutes[9][0]);
    lc.setColumn(0,3,minutes[9][1]);
  }
  else if(now.minute()<55 && now.minute()>=50){
    clearTimeDisplayMinutes();
    lc.setColumn(0,4,minutes[10][0]);
    lc.setColumn(0,3,minutes[10][1]);
  }
  else{
    clearTimeDisplayMinutes();
    lc.setColumn(0,4,minutes[11][0]);
    lc.setColumn(0,3,minutes[11][1]);
  }
}

void clearTimeDisplayHour(){
  lc.setColumn(0,7,B00000000);
  lc.setColumn(0,6,B00000000);
  lc.setColumn(0,5,B00000000);
}

void clearTimeDisplayMinutes(){
  lc.setColumn(0,4,B00000000);
  lc.setColumn(0,3,B00000000);
}
/*
void dustSampling(){
  if(checkSampling == 0){
    digitalWrite(dustDigitalPin, LOW);
    dustValue = analogRead(dustAnalogPin);
    checkSampling = 1;
    Serial.print("checkSampling check!");
    Serial.println(dustSensorTime);
  }
}

void dustWaiting(){
  if(checkSampling == 1 && checkWaiting == 0){
    digitalWrite(dustDigitalPin, HIGH);
    checkWaiting = 1;
    Serial.print("  checkWaiting check!");
    Serial.println(dustSensorTime);
  }
}

void dustHold(){
  if(checkSampling == 1 && checkWaiting == 1){
    dustDensityug = (float)(0.172*(dustValue*(5.0/1024))-0.099)*1000;
    checkSampling=0;
    checkWaiting =0;
    Serial.print("  ALL check!");
    Serial.println(dustSensorTime);
  }
}
*/
