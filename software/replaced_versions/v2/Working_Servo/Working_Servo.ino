#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX

int EN=4;

byte array1[] = {255, 255, 1, 4, 2, 3, 1, 244};
byte array2[] = {255, 255, 1, 4, 2, 5, 1, 242};
byte array3[] = {255, 255, 1, 5, 3, 32, 75, 0, 139};
byte array4[] = {255, 255, 1, 5, 3, 30, 17, 0, 199};

byte array11[] = {255, 255, 1, 4, 2, 3, 1, 244};
byte array12[] = {255, 255, 1, 4, 2, 5, 1, 242};
byte array13[] = {255, 255, 1, 5, 3, 32, 75, 0, 139};
byte array14[] = {255, 255, 1, 5, 3, 30, 239, 3, 230};

void setup()  
{
  Serial.begin(9600);
  mySerial.begin(57600);     // set the data rate for the SoftwareSerial port
  pinMode(EN,OUTPUT);
}

void loop() // run over and over
{
  int numBytesAvail;
  
  digitalWrite(EN,HIGH);
  mySerial.write(array1, sizeof(array1));
  digitalWrite(EN,LOW);
  delay(100);
  numBytesAvail = mySerial.available();   // get number of bytes in response message 
  for (int i=0; i<numBytesAvail; i++)
    Serial.print(mySerial.read(), HEX);      // print each one as hex number on console
    
  digitalWrite(EN,HIGH);
  mySerial.write(array2, sizeof(array2));
  
  digitalWrite(EN,LOW);
  delay(100);
  numBytesAvail = mySerial.available();   // get number of bytes in response message 
  for (int i=0; i<numBytesAvail; i++)
    Serial.print(mySerial.read(), HEX);      // print each one as hex number on console
    
  digitalWrite(EN,HIGH);
  mySerial.write(array3, sizeof(array3));
  
  digitalWrite(EN,LOW);
  delay(100);
  numBytesAvail = mySerial.available();   // get number of bytes in response message 
  for (int i=0; i<numBytesAvail; i++)
    Serial.print(mySerial.read(), HEX);      // print each one as hex number on console
    
  digitalWrite(EN,HIGH);
  mySerial.write(array4, sizeof(array4));
  
  digitalWrite(EN,LOW);
  delay(100);
  numBytesAvail = mySerial.available();   // get number of bytes in response message 
  for (int i=0; i<numBytesAvail; i++)
    Serial.print(mySerial.read(), HEX);      // print each one as hex number on console
    
    
  delay(1000);
  
  digitalWrite(EN,HIGH);
  mySerial.write(array11, sizeof(array11));
  
  digitalWrite(EN,LOW);
  delay(100);
  numBytesAvail = mySerial.available();   // get number of bytes in response message 
  for (int i=0; i<numBytesAvail; i++)
    Serial.print(mySerial.read(), HEX);      // print each one as hex number on console
    
  digitalWrite(EN,HIGH);
  mySerial.write(array12, sizeof(array12));
  
  digitalWrite(EN,LOW);
  delay(100);
  numBytesAvail = mySerial.available();   // get number of bytes in response message 
  for (int i=0; i<numBytesAvail; i++)
    Serial.print(mySerial.read(), HEX);      // print each one as hex number on console
    
  digitalWrite(EN,HIGH);
  mySerial.write(array13, sizeof(array13));
  
  digitalWrite(EN,LOW);
  delay(100);
  numBytesAvail = mySerial.available();   // get number of bytes in response message 
  for (int i=0; i<numBytesAvail; i++)
    Serial.print(mySerial.read(), HEX);      // print each one as hex number on console
    
  digitalWrite(EN,HIGH);
  mySerial.write(array14, sizeof(array14));
  
  digitalWrite(EN,LOW);
  delay(100);
  numBytesAvail = mySerial.available();   // get number of bytes in response message 
  for (int i=0; i<numBytesAvail; i++)
    Serial.print(mySerial.read(), HEX);      // print each one as hex number on console
  
  delay(1000);

}
