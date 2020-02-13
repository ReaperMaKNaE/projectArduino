#include <Servo.h>
#include <SoftwareSerial.h>

Servo servo;

int servoPin = 10;
int blueTx = 3;     //TXD Pin
int blueRx = 2;     //RXD Pin

int firstDCinput1 = 8;
int firstDCinput2 = 9;

int angleForServo = 0;

SoftwareSerial mySerial(blueTx, blueRx);
char value;

unsigned long previousTime = 0;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  servo.attach(servoPin, 500, 1500);
  pinMode(firstDCinput1, OUTPUT);
  pinMode(firstDCinput2, OUTPUT);
}

void loop() {
  unsigned long currentTime = millis();

  if(mySerial.available()){
    value = mySerial.read();
    Serial.print(value);
    
    if(value == '1') {
      digitalWrite(firstDCinput1,HIGH);
      digitalWrite(firstDCinput2,LOW);
      angleForServo = 0;
      Serial.println("Go Straight");
      servo.write(0);
    }
    else if(value == '2') {
      if(currentTime > previousTime + 100) {
        angleForServo += 20;
        previousTime = currentTime;
      }
      digitalWrite(firstDCinput1,LOW);
      digitalWrite(firstDCinput2,LOW);
      Serial.print("angleFor servo :");
      Serial.println(angleForServo);
      servo.write(angleForServo);
      delay(100);
    }
    else if(value == '3') {
      if(currentTime > previousTime + 100) {
        angleForServo -= 20;
        previousTime = currentTime;
      }
      digitalWrite(firstDCinput1,LOW);
      digitalWrite(firstDCinput2,LOW);
      Serial.print("angleFor servo :");
      Serial.println(angleForServo);
      servo.write(angleForServo);
      delay(100);
    }
    else if(value == '4') {
      digitalWrite(firstDCinput1,LOW);
      digitalWrite(firstDCinput2,HIGH);
      Serial.println("Go Back");
      servo.write(0);
      angleForServo = 0;
    }
  }
}
