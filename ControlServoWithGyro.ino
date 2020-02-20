#include<Wire.h>
#include <Servo.h>

Servo servo;
int value = 0;

int ServoPin = 10;

#define THROTTLE_MAX 255
#define THROTTLE_MIN 0

//MSP프로토콜 설정//
enum{
  HEAD1,
  HEAD2,
  HEAD3,
  DATASIZE,
  CMD,
  ROLL,
  PICTH,
  YAW,
  THROTTLE,
  AUX,
  CRC,
  PACKETSIZE
};
uint8_t mspPacket[PACKETSIZE];

const int MPU_addr = 0x68; //MPU Address//
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ; //가속도 센서값, 자이로 센서값//

//세가지 형태의 Roll, Pitch, Yaw 각도를 저장하기 위한 변수//
float accel_angle_x, accel_angle_y, accel_angle_z;
//float gyro_angle_x, gyro_angle_y, gyro_angle_z;
float filtered_angle_x, filtered_angle_y, filtered_angle_z;

//메시지 출력을 위한 알려주는 변수. extern으로 선언 시 선언된 변수가 어딘가에 있다는 것을 아두이노 소프트웨어에 알릴 때 사용//
extern float roll_output, pitch_output, yaw_output;
extern float motorA_speed, motorB_speed, motorC_speed, motorD_speed;

//보정형 변수//
float baseAcX, baseAcY, baseAcZ;
float baseGyX, baseGyY, baseGyZ;

//시간관련 값//
float dt;
unsigned long t_now;
unsigned long t_prev;

//자이로 센서를 이용한 각도구하기//
float gyro_x, gyro_y, gyro_z;

//이중루프PID에서 제어할 변수들//
float roll_target_angle = 0.0;
float roll_angle_in;
float roll_rate_in;
float roll_stabilize_kp = 1;
float roll_stabilize_ki = 0;
float roll_rate_kp = 1;
float roll_rate_ki = 0;
float roll_stabilize_iterm;
float roll_rate_iterm;
float roll_output;

float pitch_target_angle = 0.0;
float pitch_angle_in;
float pitch_rate_in;
float pitch_stabilize_kp = 1;
float pitch_stabilize_ki = 0;
float pitch_rate_kp = 1;
float pitch_rate_ki = 0;
float pitch_stabilize_iterm;
float pitch_rate_iterm;
float pitch_output;

float yaw_target_angle = 0.0;
float yaw_angle_in;
float yaw_rate_in;
float yaw_stabilize_kp = 1;
float yaw_stabilize_ki = 0;
float yaw_rate_kp = 1;
float yaw_rate_ki = 0;
float yaw_stabilize_iterm;
float yaw_rate_iterm;
float yaw_output;

float base_roll_target_angle;
float base_pitch_target_angle;
float base_yaw_target_angle;

extern float roll_target_angle;
extern float pitch_target_angle;
extern float yaw_target_angle;

void setup() {
  servo.attach(ServoPin);
  initMPU6050();
  Serial.begin(9600);
  calibAccelGyro();
  initDT();
  initYPR(); //Roll, Pitch, Yaw의 초기각도 값을 설정(평균을 구해 초기 각도로 설정, 호버링을 위한 목표 각도로 사용)
}

void loop() {
  // put your main code here, to run repeatedly:
  int degree;
  int servoAngle;
  
  readAccelGyro();
  calcDT();
  
  calcAccelYPR(); //가속도 센서 Roll, Pitch, Yaw의 각도를 구하는 루틴
  calcGyroYPR(); //자이로 센서 Roll, Pitch, Yaw의 각도를 구하는 루틴
  degree = calcFilteredYPR(); //상보필터를 적용해 Roll, Pitch, Yaw의 각도를 구하는 루틴

  if(degree > -10 && degree < 10) {
    servoAngle = 100;
    servo.write(servoAngle);
  }
  else {
    servoAngle = 100 - int(degree/2);
    servo.write(servoAngle);
  }
  
}

void initMPU6050(){
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true); //I2C의 제어권을 반환
}

void calibAccelGyro(){
  float sumAcX = 0;
  float sumAcY = 0;
  float sumAcZ = 0;
  float sumGyX = 0;
  float sumGyY = 0;
  float sumGyZ = 0;

  readAccelGyro();

  //초기 보정값은 10번의 가속도 자이로 센서의 값을 받아 해당 평균값을 가진다.
  for(int i=0; i<10; i++){
    readAccelGyro();

    sumAcX += AcX, sumAcY += AcY, sumAcZ += AcZ;
    sumGyX += GyX, sumGyY += GyY, sumGyZ += GyZ;

    delay(100);
  }

  baseAcX = sumAcX / 10;
  baseAcY = sumAcY / 10;
  baseAcZ = sumAcZ / 10;

  baseGyX = sumGyX / 10;
  baseGyY = sumGyY / 10;
  baseGyZ = sumGyZ / 10;
}

void initDT(){
  t_prev = micros(); //초기 t_prev값은 근사값//
}

void initYPR(){
  //초기 호버링의 각도를 잡아주기 위해서 Roll, Pitch, Yaw 상보필터 구하는 과정을 10번 반복한다.//
  for(int i=0; i<10; i++){
    readAccelGyro();
    calcDT();
    calcAccelYPR();
    calcGyroYPR();
    calcFilteredYPR();

    base_roll_target_angle += filtered_angle_y;
    base_pitch_target_angle += filtered_angle_x;
    base_yaw_target_angle += filtered_angle_z;

    delay(100);
  }

  //평균값을 구한다.//
  base_roll_target_angle /= 10;
  base_pitch_target_angle /= 10;
  base_yaw_target_angle /= 10;

  //초기 타겟 각도를 잡아준다.//
  roll_target_angle = base_roll_target_angle;
  pitch_target_angle = base_pitch_target_angle;
  yaw_target_angle = base_yaw_target_angle;
}

void calcDT(){
  t_now = micros();
  dt = (t_now - t_prev) / 1000000.0;
  t_prev = t_now;
}

void calcAccelYPR(){
  float accel_x, accel_y, accel_z;
  float accel_xz, accel_yz;
  const float RADIANS_TO_DEGREES = 180 / 3.14159;

  accel_x = AcX - baseAcX;
  accel_y = AcY - baseAcY;
  accel_z = AcZ + (16384 - baseAcZ);

  //accel_angle_y는 Roll각을 의미//
  accel_yz = sqrt(pow(accel_y, 2) + pow(accel_z, 2));
  accel_angle_y = atan(-accel_x / accel_yz) * RADIANS_TO_DEGREES;

  //accel_angle_x는 Pitch값을 의미//
  accel_xz = sqrt(pow(accel_x, 2) + pow(accel_z, 2));
  accel_angle_x = atan(accel_y / accel_xz) * RADIANS_TO_DEGREES;

  accel_angle_z = 0; //중력 가속도(g)의 방향과 정반대의 방향을 가리키므로 가속도 센서를 이용해서는 회전각을 계산할 수 없다.//
}

void calcGyroYPR(){
  const float GYROXYZ_TO_DEGREES_PER_SEC = 131;

  gyro_x = (GyX - baseGyX) / GYROXYZ_TO_DEGREES_PER_SEC;
  gyro_y = (GyY - baseGyY) / GYROXYZ_TO_DEGREES_PER_SEC;
  gyro_z = (GyZ - baseGyZ) / GYROXYZ_TO_DEGREES_PER_SEC;

}

int calcFilteredYPR(){
  const float ALPHA = 0.96;
  float tmp_angle_x, tmp_angle_y, tmp_angle_z;

  tmp_angle_x = filtered_angle_x + gyro_x * dt;
  tmp_angle_y = filtered_angle_y + gyro_y * dt;
  tmp_angle_z = filtered_angle_z + gyro_z * dt;

  //상보필터 값 구하기(가속도, 자이로 센서의 절충)//
  filtered_angle_x = ALPHA * tmp_angle_x + (1.0-ALPHA) * accel_angle_x;
  filtered_angle_y = ALPHA * tmp_angle_y + (1.0-ALPHA) * accel_angle_y;
  filtered_angle_z = tmp_angle_z;
  Serial.print("Filter X value : ");
  Serial.print(filtered_angle_x);
  Serial.print(" || Filter Y value : ");
  Serial.print(filtered_angle_y);
  Serial.print(" || Filter z value : ");
  Serial.println(filtered_angle_z);

  return filtered_angle_y;
}

void dualPID(float target_angle,
             float angle_in,
             float rate_in,
             float stabilize_kp,
             float stabilize_ki,
             float rate_kp,
             float rate_ki,
             float &stabilize_iterm,
             float &rate_iterm,
             float &output
){
  float angle_error;
  float desired_rate;
  float rate_error;
  float stabilize_pterm, rate_pterm;

  //이중루프PID알고리즘//
  angle_error = target_angle - angle_in;

  stabilize_pterm = stabilize_kp * angle_error;
  stabilize_iterm = stabilize_ki * angle_error * dt; //안정화 적분항//

  desired_rate = stabilize_pterm;

  rate_error = desired_rate - rate_in;

  rate_pterm = rate_kp * rate_error; //각속도 비례항//
  rate_iterm = rate_ki * rate_error * dt; //각속도 적분항//

  output = rate_pterm + rate_iterm + stabilize_iterm; //최종 출력 : 각속도 비례항 + 각속도 적분항 + 안정화 적분항//
}

void readAccelGyro(){
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);  //I2C의 제어권을 이어간다//
  Wire.requestFrom(MPU_addr, 14, true);

  //가속도, 자이로 센서의 값을 읽어온다.//
  AcX = Wire.read() << 8|Wire.read();
  AcY = Wire.read() << 8|Wire.read();
  AcZ = Wire.read() << 8|Wire.read();
  Tmp = Wire.read() << 8|Wire.read();
  GyX = Wire.read() << 8|Wire.read();
  GyY = Wire.read() << 8|Wire.read();
  GyZ = Wire.read() << 8|Wire.read();
}
