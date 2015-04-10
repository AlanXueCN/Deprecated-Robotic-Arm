#include "EasyTransfer.h"
#include <Wire.h>

#define DELAY 5

const int FORWARD_CHARACTER = 0;
const int REVERSE_CHARACTER = 1;
int last = 0;
int count = 0;

volatile int state = LOW;

EasyTransfer ETreceive;

struct RECEIVE_DATA_STRUCTURE{
  uint8_t reset;
  uint8_t wristUp;
  uint8_t wristDown;
  uint8_t wristClockWise;
  uint8_t wristCounterClockWise;
  uint8_t elbowUp;
  uint8_t elbowDown;
  uint8_t elbowClockWise;
  uint8_t elbowCounterClockWise;
  uint8_t actuatorForward;
  uint8_t actuatorReverse;
  uint8_t baseClockWise;
  uint8_t baseCounterClockWise;
};

RECEIVE_DATA_STRUCTURE receiveData;

boolean DEBUG_MODE = false;
const int DEBUG_MODE_SELECT=A3;

void setup(){
  //attachInterrupt(0, backup, RISING);
    Serial.begin(115200);
    resetStruct();
    ETreceive.begin(details(receiveData), &Serial);
    Wire.begin(); // join i2c bus (address optional for master)  
  }

void loop(){
  if(ETreceive.receiveData()){ 
    if(receiveData.reset)
      reset();
    if(receiveData.wristUp)
      wristUp();
    if(receiveData.wristDown)
      wristDown();
    if(receiveData.wristClockWise)
      wristClockWise();
    if(receiveData.wristCounterClockWise)
      wristCounterClockWise();
    if(receiveData.elbowUp)
      elbowUp();
    if(receiveData.elbowDown)
      elbowDown();
    if(receiveData.elbowClockWise)
      elbowClockWise();
    if(receiveData.elbowCounterClockWise)
      elbowCounterClockWise();
    if(receiveData.actuatorForward)
      actuatorForward();
    if(receiveData.actuatorReverse)
      actuatorReverse();
    if(receiveData.baseClockWise)
      baseClockWise();
    if(receiveData.baseCounterClockWise)
      baseCounterClockWise();
    resetStruct();
  }
}

void reset(){
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  delay(2000);
  digitalWrite(4, HIGH);
  pinMode(4, INPUT);
}

void wristClockWise(){
  Wire.beginTransmission(1);
  Wire.write(FORWARD_CHARACTER);
  Wire.endTransmission();
  delay(DELAY);
  Wire.beginTransmission(2);
  Wire.write(FORWARD_CHARACTER);
  Wire.endTransmission();
  delay(DELAY);
  last=1;
}

void wristCounterClockWise(){
  Wire.beginTransmission(1);
  Wire.write(REVERSE_CHARACTER);
  Wire.endTransmission();
  delay(DELAY);
  Wire.beginTransmission(2);
  Wire.write(REVERSE_CHARACTER);
  Wire.endTransmission();
  delay(DELAY);
  last=2;
}

void wristUp(){
  Wire.beginTransmission(1);
  Wire.write(FORWARD_CHARACTER);
  Wire.endTransmission();
  delay(DELAY);
  Wire.beginTransmission(2);
  Wire.write(REVERSE_CHARACTER);
  Wire.endTransmission();
  delay(DELAY);
  last=3;
}

void wristDown(){
  Wire.beginTransmission(1);
  Wire.write(REVERSE_CHARACTER);
  Wire.endTransmission();
  delay(DELAY);
  Wire.beginTransmission(2);
  Wire.write(FORWARD_CHARACTER);
  Wire.endTransmission();
  delay(DELAY);
  last=4;
}

void elbowCounterClockWise(){
  Wire.beginTransmission(3);
  Wire.write(FORWARD_CHARACTER);
  Wire.endTransmission();
  delay(DELAY);
  Wire.beginTransmission(4);
  Wire.write(FORWARD_CHARACTER);
  Wire.endTransmission();
  delay(DELAY);
  last=5;
}

void elbowClockWise(){
  Wire.beginTransmission(3);
  Wire.write(REVERSE_CHARACTER);
  Wire.endTransmission();
  delay(DELAY);
  Wire.beginTransmission(4);
  Wire.write(REVERSE_CHARACTER);
  Wire.endTransmission();
  delay(DELAY);
  last=6;
}

void elbowDown(){
  Wire.beginTransmission(3);
  Wire.write(FORWARD_CHARACTER);
  Wire.endTransmission();
  delay(DELAY);
  Wire.beginTransmission(4);
  Wire.write(REVERSE_CHARACTER);
  Wire.endTransmission();
  delay(DELAY);
  last=7;
}

void elbowUp(){
  Wire.beginTransmission(3);
  Wire.write(REVERSE_CHARACTER);
  Wire.endTransmission();
  delay(DELAY);
  Wire.beginTransmission(4);
  Wire.write(FORWARD_CHARACTER);
  Wire.endTransmission();
  delay(DELAY);
  last=8;
}

void actuatorForward(){
  Wire.beginTransmission(5);
  Wire.write(FORWARD_CHARACTER);
  Wire.endTransmission();
  delay(DELAY);
  last=9;
}

void actuatorReverse(){
  Wire.beginTransmission(5);
  Wire.write(REVERSE_CHARACTER);
  Wire.endTransmission();
  delay(DELAY);
  last=10;
}

void baseClockWise(){
  Wire.beginTransmission(6);
  Wire.write(FORWARD_CHARACTER);
  Wire.endTransmission();
  delay(DELAY);
  last=11;
}

void baseCounterClockWise(){
  Wire.beginTransmission(6);
  Wire.write(REVERSE_CHARACTER);
  Wire.endTransmission();
  delay(DELAY);
  last=12;
}

void resetStruct(){
  receiveData.reset = 0;
  receiveData.wristUp = 0;
  receiveData.wristDown = 0;
  receiveData.wristClockWise = 0;
  receiveData.wristCounterClockWise = 0;
  receiveData.elbowUp = 0;
  receiveData.elbowDown = 0;
  receiveData.elbowClockWise = 0;
  receiveData.elbowCounterClockWise = 0;
  receiveData.actuatorForward = 0;
  receiveData.actuatorReverse = 0;
  receiveData.baseClockWise = 0;
  receiveData.baseCounterClockWise = 0; 
}

/*
void backup(){
  if(last==2)
    wristUp();
  if(last==1)
    wristDown();
  if(last==4)
    wristClockWise();
  if(last==3)
    wristCounterClockWise();
  if(last==6)
    elbowUp();
  if(last==5)
    elbowDown();
  if(last==8)
    elbowClockWise();
  if(last==7)
    elbowCounterClockWise();
  if(last==10)
    actuatorForward();
  if(last==9)
    actuatorReverse();
  if(last==12)
    baseClockWise();
  if(last==11)
    baseCounterClockWise();
  delay(1000);
}
*/
