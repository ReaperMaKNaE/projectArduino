#include<Wire.h>

int toDecoder1 = 6;
int toDecoder2 = 7;
int toDecoder3 = 8;

const int MPU=0x68;  //MPU 6050 의 I2C 기본 주소
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

int turnOnMotor = false;

void setup() {
  Wire.begin();      //Wire 라이브러리 초기화
  Wire.beginTransmission(MPU); //MPU로 데이터 전송 시작
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     //MPU-6050 시작 모드로
  Wire.endTransmission(true); 
  Serial.begin(9600);
  pinMode(toDecoder1, OUTPUT);
  pinMode(toDecoder2, OUTPUT);
  pinMode(toDecoder3, OUTPUT);
}

void loop() {
  Wire.beginTransmission(MPU);    //데이터 전송시작
  Wire.write(0x3B);               // register 0x3B (ACCEL_XOUT_H), 큐에 데이터 기록
  Wire.endTransmission(false);    //연결유지
  Wire.requestFrom(MPU,14,true);  //MPU에 데이터 요청
  //데이터 한 바이트 씩 읽어서 반환
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  if(AcX > 10000) {
    digitalWrite(toDecoder1, HIGH);
    digitalWrite(toDecoder2, LOW);
    digitalWrite(toDecoder3, LOW);
    analogWrite(3, 0);
    analogWrite(5, 100);
    delay(500);
  }
  else if(AcX < -10000) {
    digitalWrite(toDecoder1, LOW);
    digitalWrite(toDecoder2, HIGH);
    digitalWrite(toDecoder3, LOW);
    analogWrite(3, 0);
    analogWrite(5, 150);
    delay(500);
  }
  else if(AcY > 10000) {
    digitalWrite(toDecoder1, HIGH);
    digitalWrite(toDecoder2, HIGH);
    digitalWrite(toDecoder3, LOW);
    analogWrite(3, 0);
    analogWrite(5, 200);
    delay(500);
  }
  else if(AcY < -10000) {
    digitalWrite(toDecoder1, LOW);
    digitalWrite(toDecoder2, LOW);
    digitalWrite(toDecoder3, HIGH);
    analogWrite(3, 0);
    analogWrite(5, 250);
    delay(500);
  }
  else {
    digitalWrite(toDecoder1, LOW);
    digitalWrite(toDecoder2, LOW);
    digitalWrite(toDecoder3, LOW);
    analogWrite(3, 0);
    analogWrite(5, 0);
    delay(500);
  }
}
