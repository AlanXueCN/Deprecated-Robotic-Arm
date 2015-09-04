/*******************
MRDT 2015 Drill
Mike Miles
*******************/

#include <SoftwareSerial.h>
#define PRINT true

//#define DRILL_BYTE_ID 
//#define LINACT_BYTE_ID
#define DATA_ID 210

const int pin_M1EN = 6;
const int pin_M1INA = 2;
const int pin_M1INB = 4;
const int pin_M1PWM = 9;
const int pin_M1CS = A0;
const int pin_M2EN = 12;
const int pin_M2INA = 7;
const int pin_M2INB = 8;
const int pin_M2PWM = 10;
const int pin_M2CS = A1;

SoftwareSerial moboSerial(0, 1); // (Rx, Tx)

const char STOP = 0x00;
const char FORW = 0x01;
const char REV = 0x02;

char cmd = 0;
char drillCmd = STOP;
bool drillCmd_EN = 0;
bool drillCmd_INA = 0;
bool drillCmd_INB = 0;
bool drillCmd_PWM = 0;
char linactCmd = STOP;
bool linactCmd_EN = 0;
bool linactCmd_INA = 0;
bool linactCmd_INB = 0;
bool linactCmd_PWM = 0;

void setup() {
  // Serial with xbee
  Serial.begin(57600);
  
  // config motor driver select pins
  pinMode(pin_M1EN, OUTPUT);
  pinMode(pin_M1INA, OUTPUT);
  pinMode(pin_M1INB, OUTPUT);
  pinMode(pin_M1PWM, OUTPUT);
  pinMode(pin_M1CS, INPUT);
  pinMode(pin_M2EN, OUTPUT);
  pinMode(pin_M2INA, OUTPUT);
  pinMode(pin_M2INB, OUTPUT);
  pinMode(pin_M2PWM, OUTPUT);
  pinMode(pin_M2CS, INPUT);
}

void loop() {
  
  //Wait for command ID
  while(Serial.read() != DATA_ID);  
  Serial.println("Got data ID");
  
  //wait for data
  while(!Serial.available());
  cmd = Serial.read();

  linactCmd = cmd >> 4;
  drillCmd = 0x0F & cmd;
  
  // command drill
  if(drillCmd == FORW){ // drill forward
    drillCmd_EN = 1;
    drillCmd_INA = 1;
    drillCmd_INB = 0;
    drillCmd_PWM = 1;
    
  }
  else if(drillCmd == REV){ // drill reverse
    drillCmd_EN = 1;
    drillCmd_INA = 0;
    drillCmd_INB = 1;
    drillCmd_PWM = 1;
  }
  else{ // drill stop or bad transmission
    drillCmd = STOP;
    drillCmd_EN = 1;
    drillCmd_INA = 0;
    drillCmd_INB = 0; 
    drillCmd_PWM = 0;
  }
  
  // command linear actuator
  if(linactCmd == FORW){ // drill forward
    linactCmd_EN = 1;
    linactCmd_INA = 1;
    linactCmd_INB = 0;
    linactCmd_PWM = 1;
    
  }
  else if(linactCmd == REV){ // drill reverse
    linactCmd_EN = 1;
    linactCmd_INA = 0;
    linactCmd_INB = 1;
    linactCmd_PWM = 1;
  }
  else{ // drill stop or bad transmission
    linactCmd = STOP;
    linactCmd_EN = 1;
    linactCmd_INA = 0;
    linactCmd_INB = 0; 
    linactCmd_PWM = 0;
  }
  
  digitalWrite(pin_M1EN, drillCmd_EN);
  digitalWrite(pin_M1INA, drillCmd_INA);
  digitalWrite(pin_M1INB, drillCmd_INB);
  digitalWrite(pin_M1PWM, drillCmd_PWM);
  digitalWrite(pin_M2EN, linactCmd_EN);
  digitalWrite(pin_M2INA, linactCmd_INA);
  digitalWrite(pin_M2INB, linactCmd_INB);
  digitalWrite(pin_M2PWM, linactCmd_PWM);
  
  if(PRINT )
  {
    Serial.print("Rx'ed: "); 
    Serial.print(cmd, HEX);
    Serial.print("  ");
    Serial.print("drill: ");
    print_cmd(drillCmd);
    Serial.print("  ");
    Serial.print("linact: ");
    print_cmd(linactCmd);
    Serial.println();
  }

}

void print_cmd(char bite){
  switch(bite){
    case STOP:
      Serial.print("STOP");
      break;
    case FORW:
      Serial.print("FORW");
      break;
    case REV:
      Serial.print("REV");
      break;
  }
  return;
}


