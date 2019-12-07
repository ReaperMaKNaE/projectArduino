int dust_sensor = A0;   // 미세먼지 핀 번호
 
float dust_value = 0;  // 센서에서 입력 받은 미세먼지 값
float dustDensityug=0;  // ug/m^3 값을 계산
 
int sensor_led = 3;      // 미세먼지 센서 안에 있는 적외선 led 핀 번호
int sampling = 280;    // 적외선 led를 키고, 센서 값을 읽어 들여 미세먼지를 측정하는 샘플링 시간
int waiting = 40;    
float stop_time = 9680;   // 센서를 구동하지 않는 시간
 
void setup(){
  Serial.begin(9600);   // 시리얼 모니터 시작, 속도는 9600
  pinMode(sensor_led,OUTPUT); // 미세먼지 적외선 led를 출력으로 설정
}
 
void loop(){
  digitalWrite(sensor_led, LOW);    // LED 켜기
  delayMicroseconds(sampling);   // 샘플링해주는 시간. 
 
  dust_value = analogRead(dust_sensor); // 센서 값 읽어오기
  
  delayMicroseconds(waiting);  // 너무 많은 데이터 입력을 피해주기 위해 잠시 멈춰주는 시간. 
 
  digitalWrite(sensor_led, HIGH); // LED 끄기
  delayMicroseconds(stop_time);   // LED 끄고 대기  
 
  dustDensityug = (0.172 * (dust_value * (5.0 / 1024)) - 0.099) * 1000;    // 미세먼지 값 계산
  Serial.println(dustDensityug);
  
  delay(2000);
}
