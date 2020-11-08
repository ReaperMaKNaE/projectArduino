#include <SoftwareSerial.h>

SoftwareSerial BTSerial(8, 7);   //bluetooth module Tx:Digital 2 Rx:Digital 3

void setup() {
  Serial.begin(38400);
  BTSerial.begin(38400);
}

void loop() {
  if (BTSerial.available())
    Serial.write(BTSerial.read());
  if (Serial.available())
    BTSerial.write(Serial.read());
}
