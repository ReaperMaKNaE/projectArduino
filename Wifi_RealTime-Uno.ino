#include "WiFiEsp.h"
#include "WiFiEspUdp.h"
#include <TimeLib.h>

//Pin number
int dust_sensor = A0;

//The amount of the dust
float dust_value = 0;
float dustDensityug=0;

int sensor_led = 12;
int sampling = 280;     //For Sampling time
int waiting = 40;    
float stop_time = 9680;

#include "SoftwareSerial.h"
//For communication, digital pin will be used as Rx, Tx Pin
SoftwareSerial Serial1(2, 3); // RX, TX

char ssid[] = "ReaperMaKNaE";            // your network SSID (name)
char pass[] = "aassdd123";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

char timeServer[] = "kr.pool.ntp.org";  // NTP server
unsigned int localPort = 2390;        // local port to listen for UDP packets

const int NTP_PACKET_SIZE = 48;  // NTP timestamp is in the first 48 bytes of the message
const int UDP_TIMEOUT = 2000;    // timeout in miliseconds to wait for an UDP packet to arrive

byte packetBuffer[NTP_PACKET_SIZE]; // buffer to hold incoming and outgoing packets

// A UDP instance to let us send and receive packets over UDP
WiFiEspUDP Udp;

bool got_NTP = false;
uint8_t timeZone = 9;

void setup()
{
  // initialize serial for debugging
  Serial.begin(9600);
  // initialize serial for ESP module
  Serial1.begin(9600);
  // initialize ESP module
  WiFi.init(&Serial1);

  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }

  // you're connected now, so print out the data
  Serial.println("You're connected to the network");
  
  Udp.begin(localPort);
  
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
  NTP_send();
  getNtpTime();
}

unsigned long startMs = 0l;

void NTP_send(){
  if(got_NTP == false){
    if(millis() - startMs >= 2000){
      startMs = millis();
      sendNTPpacket(timeServer);
    }
  }
}

void getNtpTime(){
  if(got_NTP == false){
    if(Udp.available()){
      if(Udp.parsePacket()){
        Udp.read(packetBuffer, NTP_PACKET_SIZE);
        unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
        unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
        unsigned long secsSince1900 = highWord << 16 | lowWord;
        const unsigned long seventyYears = 2208988800UL;
        unsigned long epoch = secsSince1900 - seventyYears + timeZone * 3600;
        if (hour(epoch) < 10) {
          Serial.print('0'); 
        }
        Serial.print(hour(epoch)); 
        if (minute(epoch) < 10) {
          Serial.print('0'); 
        }
        Serial.println(minute(epoch)); 
        got_NTP = true;
      }
    }
  }
}

void sendNTPpacket(char *ntpSrv) {
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;
  Udp.beginPacket(ntpSrv, 123); //NTP requests are to port 123
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}
