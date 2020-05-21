#include <Servo.h>
#include <SoftwareSerial.h>

Servo servo;

int servoPin = 7;
int blueTx = 3;     //TXD Pin
int blueRx = 2;     //RXD Pin

int firstDCinput1 = 8;
int firstDCinput2 = 9;
int secondDCinput1 = 10;
int secondDCinput2 = 11;

int angleForServo = 90;

int cruiseMode = 0;

SoftwareSerial mySerial(blueTx, blueRx);
int value;

unsigned long previousTime = 0;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  servo.attach(servoPin, 500, 1500);
  pinMode(firstDCinput1, OUTPUT);
  pinMode(firstDCinput2, OUTPUT);
  pinMode(secondDCinput1, OUTPUT);
  pinMode(secondDCinput2, OUTPUT);
}

void loop() {
  unsigned long currentTime = millis();

  if(mySerial.available()){
    value = mySerial.read();
    Serial.print(value);

    if(value <= 190) {
      servo.write(value);
    }
    else {
      if(value == 250) {
        digitalWrite(firstDCinput1, LOW);
        digitalWrite(firstDCinput2, LOW);
        digitalWrite(secondDCinput1, LOW);
        digitalWrite(secondDCinput2, LOW);
        Serial.println("Stop");
      }
      else if(value == 200) {
        digitalWrite(firstDCinput1,HIGH);
        digitalWrite(firstDCinput2,LOW);
        digitalWrite(secondDCinput1,HIGH);
        digitalWrite(secondDCinput2,LOW);
        Serial.println("Go Straight");
      }
      else if(value == 203) {
        digitalWrite(firstDCinput1,LOW);
        digitalWrite(firstDCinput2,HIGH);
        digitalWrite(secondDCinput1,LOW);
        digitalWrite(secondDCinput2,HIGH);
        Serial.println("Go Back");
      }
    }
  }
}
