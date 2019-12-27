/*
 *  Copyright 2019 Joung Byeong In, All rights reserved
 * 
 *  DigitalClock.ino
 * 
 *  SKKU, School of Mechanical Engineering
 * 
 *  2019.12.24
 * 
 *  Modified History :
 * 
 *        2019.12.24 for ver 1.0
 * 
 * 
 *  NOTE :
 *    
 *        Make Clock by using TM1637 Module.
 *        This code support 3 modes.
 *        First Mode ==> TIME mode
 *        Second Mode ==> DATE mode
 *        Third Mode ==> TIMER mode
 */

#include <TM1637Display.h>
#include <MsTimer2.h>
#include "U8glib.h"

int TM1637_CLK = 6;
int TM1637_DIO = 7;
int switchForBigMode = 8;
int switchForSmallMode = 9;
int switchForSet = 10;

int bigMode = 0;
int smallMode = 0;
int increaseValue = 0;

int timeHour = 0;
int timeMinute = 0;
int timeSecond = 0;

int dateMonth = 1;
int dateDay = 1;

int timerMinute = 0;
int timerSecond = 0;

int cond_switchForBigMode = 0;
int cond_switchForSmallMode = 0;
int cond_switchForSet = 0;
int timeElapse = 0;

TM1637Display TM1637_1(TM1637_CLK,TM1637_DIO);
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);

void setup() {
  Serial.begin(9600);
  TM1637_1.setBrightness(7);
  pinMode(switchForBigMode, INPUT_PULLUP);
  pinMode(switchForSmallMode, INPUT_PULLUP);
  pinMode(switchForSet, INPUT_PULLUP);

  MsTimer2::set(997,increaseSecond);
  MsTimer2::start();

  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }
}

void loop() {
  if(digitalRead(switchForBigMode) == LOW) {
    if(cond_switchForBigMode == 0) {
      if(bigMode == 2) {
        bigMode = 0;
        smallMode = 0;
        cond_switchForBigMode = 1;
      } else {
        bigMode++;
        smallMode = 0;
        cond_switchForBigMode = 1;
      }
    }
  } else {
    if(cond_switchForBigMode == 1) {
      cond_switchForBigMode = 0;
    }
  }

  if(digitalRead(switchForSmallMode) == LOW) {
    if(cond_switchForSmallMode == 0) {
      if(smallMode == 2) {
        smallMode = 0;
        cond_switchForSmallMode = 1;
      } else {
        smallMode++;
        cond_switchForSmallMode = 1;
      }
    }
  } else {
    if(cond_switchForSmallMode == 1) {
      cond_switchForSmallMode = 0;
    }
  }

  if(digitalRead(switchForSet) == LOW) {
    if(cond_switchForSet == 0) {
      increaseValue = 1;
      cond_switchForSet = 1;
    }
  } else {
    if(cond_switchForSet == 1) {
      cond_switchForSet = 0;
    }
  }

  if(timeElapse = 1);

  if(bigMode == 0) {
    if(smallMode == 0) {
      printTM1637(timeHour,timeMinute);
      u8g.firstPage();  
      do {
        u8g.setFont(u8g_font_unifont);
        u8g.drawStr( 0, 22, "TIME");
      } while( u8g.nextPage() );
    } else if (smallMode == 1) {
      if(increaseValue == 1 ) {
        if(timeHour == 23 ){
          timeHour = 0;
        } else {
          timeHour++;
        }
      }
      printTM1637(timeHour,timeMinute);
      u8g.firstPage();  
      do {
        u8g.setFont(u8g_font_unifont);
        u8g.drawStr( 0, 22, "TIME");
        u8g.drawStr( 0, 50, "Hour Modify Mode");
      } while( u8g.nextPage() );
    } else if (smallMode == 2) {
      if(increaseValue == 1 ) {
        if(timeMinute == 59) {
          timeMinute = 0;
        } else {
          timeMinute++;
        }
      }
      printTM1637(timeHour,timeMinute);
      u8g.firstPage();  
      do {
        u8g.setFont(u8g_font_unifont);
        u8g.drawStr( 0, 22, "TIME");
        u8g.drawStr( 0, 50, "Min Modify Mode");
      } while( u8g.nextPage() );
    }
  } else if(bigMode == 1 ) {
    if(smallMode == 0) {
      printTM1637(dateMonth,dateDay);
      u8g.firstPage();  
      do {
        u8g.setFont(u8g_font_unifont);
        u8g.drawStr( 0, 22, "DATE");
      } while( u8g.nextPage() );
    } else if(smallMode == 1) {
      if(increaseValue == 1 ) {
        if(dateMonth == 12 ) {
          dateMonth = 0;
        } else {
          dateMonth++;
        }
      }
      printTM1637(dateMonth,dateDay);
      u8g.firstPage();  
      do {
        u8g.setFont(u8g_font_unifont);
        u8g.drawStr( 0, 22, "DATE");
        u8g.drawStr( 0, 50, "Mon Modify Mode");
      } while( u8g.nextPage() );
    } else {
      if(increaseValue == 1) {
        if(dateDay == 31) {
          dateDay = 0;
        } else {
          dateDay++;
        }
      }
      printTM1637(dateMonth,dateDay);
      u8g.firstPage();  
      do {
        u8g.setFont(u8g_font_unifont);
        u8g.drawStr( 0, 22, "DATE");
        u8g.drawStr( 0, 50, "Day Modify Mode");
      } while( u8g.nextPage() );
    }
  } 

  else if(bigMode == 2) {
    if(smallMode == 0) {
      timerMinute = 0;
      timerSecond = 0;
      printTM1637(timerMinute,timerSecond);
      u8g.firstPage();  
      do {
        u8g.setFont(u8g_font_unifont);
        u8g.drawStr( 0, 22, "TIMER");
      } while( u8g.nextPage() );
    } else if(smallMode == 1 ){
      if(timerMinute == 59 && timerSecond == 59) {
        timerMinute = 0;
        timerSecond = 0;
      } else if (timerSecond == 59) {
        timerMinute++;
        timerSecond = 0;
      } else {
        timerSecond++;
      }
      delay(860);
      printTM1637(timerMinute,timerSecond);
      u8g.firstPage();  
      do {
        u8g.setFont(u8g_font_unifont);
        u8g.drawStr( 0, 22, "TIMER");
        u8g.drawStr( 0, 50, "START");
      } while( u8g.nextPage() );
    } else if (smallMode == 2 ) {
      printTM1637(timerMinute,timerSecond);
      u8g.firstPage();  
      do {
        u8g.setFont(u8g_font_unifont);
        u8g.drawStr( 0, 22, "TIMER");
        u8g.drawStr( 0, 50, "STOP");
      } while( u8g.nextPage() );
    }
  } 

  increaseValue = 0;
}

void increaseSecond() {
  if(timeHour == 23 && timeMinute == 59 && timeSecond == 59) {
    timeElapse = 1;
    timeHour = 0;
    timeMinute = 0;
    timeSecond = 0;
  } else if(timeMinute == 59 && timeSecond == 59) {
    timeHour++;
    timeMinute = 0;
    timeSecond = 0;
    timeElapse = 0;
  } else if(timeSecond == 59) {
    timeMinute++;
    timeSecond = 0;
    timeElapse = 0;
  } else {
    timeSecond++;
    timeElapse = 0;
  }

  if(timeElapse == 1) {
    if(dateMonth == 12 && dateDay == 31) {
      dateMonth = 1;
      dateDay = 1;
    } else if(dateDay == 31) {
      dateMonth++;
      dateDay = 0;
    } else {
      dateDay++;
    }
  }

}

int printTM1637(int Upper, int Lower) {
  int printedNumber;
  printedNumber = Upper * 100 + Lower;
  TM1637_1.showNumberDecEx(printedNumber, 0x40, true);
}
