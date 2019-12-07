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
#include "LedControlMS.h"
#include <SPI.h>
#include "SoftwareSerial.h"
#include <Wire.h>
#include "DHT11.h"
#include <ForWarning_1.0.h>
#include <MsTimer2.h>

#define SerialDebugging true

int gasSensorPin = A0;
int dht11Pin = 3;
int bluetoothRXDPin = 5;
int bluetoothTXDPin = 4;
/*
int TFT_SCLK = 8;  //CLK
int TFT_MOSI = 9;   //MOSI is same as SDA/SDI
int TFT_DC = 10;     //DC is same as SS(Display collect)
int TFT_RST = 11;
int TFT_CS = 12;
*/
int TFT_SCLK = 48;  //CLK
int TFT_MOSI = 43;   //MOSI is same as SDA/SDI
int TFT_DC = 21;     //DC is same as SS(Display collect)
int TFT_RST = 45;
int TFT_CS = 38;
int buzzerPin = 6;
/*
int TFT2_SCLK = 2;  //CLK
int TFT2_MOSI = 3;   //MOSI is same as SDA/SDI
int TFT2_DC = 4;     //DC is same as SS(Display collect)
int TFT2_RST = 5;
int TFT2_CS = 6;
*/
int TFT2_SCLK = 29;  //CLK
int TFT2_MOSI = 37;   //MOSI is same as SDA/SDI
int TFT2_DC = 31;     //DC is same as SS(Display collect)
int TFT2_RST = 33;
int TFT2_CS = 35;

int fanEnable = 41;

//For Dust sensor
//sampling time 280ms
//waiting time 40ms
int dustDensityug;

//15+5+SDA,SDL(2)= 20(analog 2/ digital 18);
//Wifi is not decided yet
//int wifiPin = 4;

SoftwareSerial bluetoothModule(bluetoothTXDPin, bluetoothRXDPin);
ForWarning dataPrediction;
DHT11 dht11(dht11Pin);

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
Adafruit_ST7735 tft2 = Adafruit_ST7735(TFT2_CS, TFT2_DC, TFT2_MOSI, TFT2_SCLK, TFT2_RST);


unsigned long previousTime = 0;

void setup(void) {
  Serial.begin(9600);
  //Start bluetooth Module
  bluetoothModule.begin(9600);
  Wire.begin();
  
  dataPrediction.resetAll();
  dataPrediction.getNumberOfData(10);

  //digitalOUT(buzzer & dust)
  pinMode(buzzerPin,OUTPUT);
  
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
  
  unsigned long currentTime=0;
  currentTime = millis();
  
  //Declare variables
  float temp, humi;
  int dustValue = 0;
  int checkDust = 0;
  
  float dustData;
  int filteredDustData;
  /*
  if(Serial.available()){
    dustDensityug = Serial.parseFloat();
    dataPrediction.SaveDataOfDust(dustDensityug);
    Serial.println(dustDensityug);
    filteredDustData = dataPrediction.CalculateFilteredDataForDust();
  }*/

  filteredDustData = 30;
  
  dht11.read(humi,temp);
  bluetoothModule.print("습도 : ");
  bluetoothModule.print(humi);
  bluetoothModule.print(" 온도 : ");
  bluetoothModule.println(temp);
  bluetoothModule.print("가스 :");
  bluetoothModule.print(analogRead(gasSensorPin));
  bluetoothModule.print(" 먼지 :");
  bluetoothModule.print(filteredDustData);
  
  if(analogRead(gasSensorPin)>=500){
    digitalWrite(buzzerPin,HIGH);
  }
  else{
    digitalWrite(buzzerPin,LOW);
  }

  if(filteredDustData >= 50) {
    digitalWrite(41, HIGH);
    previousTime = currentTime;
  } else {
    if(currentTime < previousTime + 1000){
      digitalWrite(41, HIGH);
    } else {
      digitalWrite(41, LOW);
    }
  }

  //TFT LCD output
  
  //tft.fillRect(화면의 왼쪽위부터 우측으로, 화면의 왼쪽위부터 아래로, 상자의 가로길이, 상자의 세로길이, 색깔);
  //tft.fillRoundRect(50,20,40,30,ST7735_BLACK);
  //위 방법 매우 별로. 지우는게 화면에보임
  tft.setCursor(0,0);
  //위 지우는 방법을 아래 textColor에서 해결.
  //setTextColor(쓸 글씨 색, overwrite할 글씨색)
  tft.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
  tft.setTextSize(3);
  tft.print("  ");
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
