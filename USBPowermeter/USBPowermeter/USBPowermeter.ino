#include <Adafruit_INA219.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_BusIO_Register.h>
#include <Wire.h>
#include <ForWarning_1.0.h>

//Refer
//https://github.com/adafruit/Adafruit_LSM303_Accel/issues/3
//https://luftaquila.tistory.com/8?category=726570
//https://m.blog.naver.com/kwy1052aa/221761758616

#define SerialDebugging true

int TFT_SCLK = 12;  //CLK
int TFT_MOSI = 11;   //MOSI is same as SDA/SDI
int TFT_DC = 10;     //DC is same as SS(Display collect)
int TFT_RST = 9;
int TFT_CS = 8;

int voltageInput = A7;


float voltage = 0;
float filteredCurrentVal = 0;
float current = 0;
float power = 0;
float vin = 0;
float vout = 0;
float R1 = 30000.0;
float R2 = 7500.0;

ForWarning filter;
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
Adafruit_INA219 ina219;

void setup(void) {
  ina219.begin();
  Serial.begin(9600);
  
  // Use this initializer if using a 1.8" TFT screen:
  tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab
  tft.fillScreen(ST77XX_BLACK);
  //Rotate TFT LCD Screen
  tft.setRotation(1);

  // Filter reset
  filter.resetAll();
  filter.getNumberOfData(5);
}

void loop() {

  current = ina219.getCurrent_mA();
  filter.SaveDataOfDust(current);
  filteredCurrentVal = filter.CalculateFilteredDataForDust();

  vout = (analogRead(voltageInput)*5.0)/1024.0;
  vin = vout / (R2 / (R1 + R2));
  voltage = vin - 0.2;
  if(voltage < 0){
    voltage = 0;
  }

  power = voltage * filteredCurrentVal;
  
  //TFT LCD output
  //tft.fillRect(화면의 왼쪽위부터 우측으로, 화면의 왼쪽위부터 아래로, 상자의 가로길이, 상자의 세로길이, 색깔);
  //tft.fillRoundRect(50,20,40,30,ST7735_BLACK);
  //위 방법 매우 별로. 지우는게 화면에보임
  tft.setCursor(0,0);
  //위 지우는 방법을 아래 textColor에서 해결.
  //setTextColor(쓸 글씨 색, overwrite할 글씨색)
  tft.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
  tft.setTextSize(2);
  tft.println("   Voltage");
  tft.print("    ");    // 3 spaces
  tft.print(voltage);
  tft.println("V");
  tft.setTextSize(1);
  tft.println("");
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_RED,ST77XX_BLACK);
  tft.println("   Current");
  tft.print("    ");    // 3 spaces
  tft.print(current);
  tft.println("A");
  tft.setTextSize(1);
  tft.println("");
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_CYAN,ST77XX_BLACK);
  tft.println("    Power");
  tft.print("    ");    // 3 spaces
  tft.print(power);
  tft.println("W");
}
