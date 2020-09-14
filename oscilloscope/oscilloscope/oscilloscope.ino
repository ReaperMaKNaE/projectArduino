#include "SPI.h"
#include "Wire.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

#define CHARWIDTH           5
#define CHARHEIGHT          8
#define AXISWIDTH           (2 + 1)
#define VISIBLEVALUEPIXELS  (128 - AXISWIDTH)
#define NUMVALUES           (2 * VISIBLEVALUEPIXELS)

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

#define TRIGGER_ENABLE_PIN       2
#define SCREEN_UPDATE_ENABLE_PIN 3

byte values[NUMVALUES];
int pos = 0;
int count = 0;
unsigned long readStartTime = 0;
int sampleRate = 1;


/*
 * 기본 세팅
 * 
 * GPIO 2,3을 GND(330옴 연결해서)
 * OLED 128x64 i2C
 * SCL -> A5
 * SDA -> A4
 * VCC -> +5V
 * GND -> GND
 * 
 * A0를 가져다대면 voltage 파형 관찰 가능
 * 
 */
/********************************************/

//OLED에 글씨 출력하는 함수
void displayln(const char* format, ...)
{
  char buffer[32];

  va_list args;
  va_start(args, format);
  vsprintf(buffer, format, args);
  va_end(args);

  display.setTextSize(1);
  display.setTextColor(WHITE);

  int len = strlen(buffer);
  Serial.println(len);
  for (uint8_t i = 0; i < len; i++) {
    display.setCursor(9 * CHARWIDTH + (i * 7), 7 * CHARHEIGHT - 2);
    display.println(buffer[i]);
    Serial.print(buffer[i]);
  }
}

//그래프의 Y축에 기준점 표시
void drawAxis()
{
  for (int x = 0; x < 2; x++) {
    display.drawPixel(x,  0, WHITE);
    display.drawPixel(x, 13, WHITE);
    display.drawPixel(x, 26, WHITE);
    display.drawPixel(x, 38, WHITE);
    display.drawPixel(x, 50, WHITE);
    display.drawPixel(x, 63, WHITE);
  }
}

//들어온 데이터를 바탕으로 파형을 OLED에 그린다
void drawValues()
{
  int start = 0;

  if ( digitalRead(TRIGGER_ENABLE_PIN) ) {
    for (int i = 0; i < NUMVALUES; i++) {
      if ( values[i] == 0 ) {
        for (; i < NUMVALUES; i++) {
          if ( values[i] != 0 ) {
            start = i;
            break;
          }
        }
        break;
      }
    }

    if ( start >= VISIBLEVALUEPIXELS )
      return;
  }

  for (int i = 0; i < VISIBLEVALUEPIXELS; i++) {
    display.drawPixel(i + AXISWIDTH, 63 - (values[i + start]), WHITE);
  }
}

//화면 프레임시간 출력
void drawFrameTime(unsigned long us)
{
  displayln("%ld us", us);
}

/********************************************/

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC,0x3C);

  //버튼 모드 설정
  pinMode(TRIGGER_ENABLE_PIN, INPUT_PULLUP);
  pinMode(SCREEN_UPDATE_ENABLE_PIN, INPUT_PULLUP);

  display.display();
  delay(2000);
  display.clearDisplay();
}

/********************************************/

void loop() {
  //1프레임 출력의 시간을 체크하기 위한 시간 측정 시작
  if ( pos == 0 )
    readStartTime = micros();

  //BIT SHIFT 연산
  if ( (++count) % sampleRate == 0 ) {
    values[pos++] = analogRead(0) >> 4;
  }

  if ( pos >= NUMVALUES ) {
    unsigned long totalSampleTime = (micros() - readStartTime) / 2;

    //화면 업데이트 핀이 눌려졌다면 OLED에 파형을 출력한다.
    if ( !digitalRead(SCREEN_UPDATE_ENABLE_PIN) ) {
      display.clearDisplay();
      drawAxis();
      drawValues();
      drawFrameTime(totalSampleTime);
      display.display();
    }

    pos = 0;
    count = 0;
  }
}
