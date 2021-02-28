#include <SoftwareSerial.h>
#include <Servo.h>

int servoPin = 12;
int blueTx = 3;         //TXD Pin
int blueRx = 2;         //RXD Pin
int tact_input1 = 5;
int tact_input2 = 6;
int T_STATE1 = HIGH;
int T_STATE2 = HIGH;
int turn = 0;

char value;

Servo servo;
SoftwareSerial mySerial(blueTx, blueRx);

unsigned long previousTime = 0;

void setup() {
    Serial.begin(38400);
    mySerial.begin(38400);
    servo.attach(servoPin, 500, 1500);
    pinMode(tact_input1, INPUT_PULLUP);
    pinMode(tact_input2, INPUT_PULLUP);
}

void loop() {
    // value 1 means turn the light off
    // value 2 means turn the light on
    if(mySerial.available()){
        value = mySerial.read();
        Serial.print("read value: ");
        Serial.println(value);
        if(value == '2'){
            servo.write(30);
            turn = 0;
            delay(300);
        }
        else if(value == '1'){
            servo.write(90);
            turn = 1;
            delay(300);
        }
    }

    // read switch state and rotate servo
    if(digitalRead(tact_input1)==LOW){
      Serial.println("STATE1");
      T_STATE1 = LOW;
      servo.write(60);
    }
    else{
      T_STATE1 = HIGH;
      servo.write(60);
    }

    if(digitalRead(tact_input2)==LOW){
      T_STATE2 = LOW;
      servo.write(60);
    }
    else{
      T_STATE2 = HIGH;
      servo.write(60);
    }
    /*
    if(T_STATE1 == LOW && T_STATE2 == HIGH){ 
        Serial.println("STATE1, servo");
        turn = 0;
        servo.write(30);
        delay(300);
    }
    else if(T_STATE1 == HIGH && T_STATE2 == LOW){
        Serial.println("STATE2");
        turn = 1;
        servo.write(90);
        delay(300);
    }*/
}
