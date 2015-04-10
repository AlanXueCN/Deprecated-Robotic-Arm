#include <SoftwareSerial.h>

#define HOME_ENCODER : 0x200
#define MAX_ENCODER : 0x3FF
#define RAD_PER_ENC : math.radians(300.0)
#define MAX_AND : math.radians(148)
#define MIN_ANG : math.radians(-148)
#define MAX_SPEED : math.radians(100)

byte instruction[10];
byte inst5[5];
byte inst6[6];
byte inst7[7];
byte inst8[8];
byte inst9[9];
byte inst10[10];
bool FLIPPED = false;

SoftwareSerial mySerial(2, 3); // RX, TX
int EN=4;

void startBits()
{
  instruction[0] = 0xFF;
  instruction[1] = 0xFF;
  instruction[2] = 0x01;
}

void init_cont_turn()
{
  Serial.println("init");
  startBits();
  instruction[3] = 0x04;
  instruction[4] = 0x04;
  instruction[5] = 0x08;
  instruction[6] = 0x00;
  formMsg();
}

void kill_cont_turn()
{
  Serial.println("kill");
  startBits();
  instruction[3] = 0x04;
  instruction[4] = 0x04;
  instruction[5] = 0x08;
  instruction[6] = 0x03;
  formMsg();
}

/*
bool is_moving()
{
  data = read_address(0x2E, 1);
  return(data[0] != 0)
}

float read_voltage()
{
  data = read_address(0x2A, 1);
  return(data[0]/10);
} 
*/
void read_temperature()
{
  int numBytesAvail;
  byte array1[] = {255, 255, 1, 4, 2, 43, 1, 204};
  
  digitalWrite(EN,HIGH);
  mySerial.write(array1, sizeof(array1));
  digitalWrite(EN,LOW);
  delay(100);
  numBytesAvail = mySerial.available();   // get number of bytes in response message 
  for (int i=0; i<numBytesAvail; i++)
    Serial.print(mySerial.read(), HEX);      // print each one as hex number on console
  //data = read_address(0x2B, 1);
}
/*
float read_load()
{
  data = read_address(0x28, 2)
  load = (data[0] + ((data[1] >> 6) * 256));
}

float read_encoder()
{
  data = read_address(0x24, 2);
  load = data[0] + data[1]*256;
  if(data[1] >> 2 & 1 == 0)
    return (-1*load);
  else
    return load;
}

float read_angle()
{
  ang = (read_encoder() - (HOME_ENCODER*RAD_PER_ENC))
  if(FLIPPED)
    ang = ang*-1;
  return ang;
}

void move_angle(ang, angvel = None, blocking = true)
{
  if(angvel == None)
    angvel = MAX_SPEED;
   
  set_angvel(angvel);
 
  if(FLIPPED)
    ang = ang*-1;
   
  enc_tics = int(round(ang/RAD_PER_NENC));
  enc_tics += HOME_ENCODER;
 
  move_to_encoder(enc_tics);
 
  if(blocking == true)
  {
    while(is_moving())
      continue;
  }
}

void move_to_encoder(n)
{
  n = min(max(n,0), MAX_ENCODER);
  hi = n/256;
  lo = n%256;
  write_address(0x1E, [lo,hi]);
}

void enable_torque()
{
  write_address(0x18, [1]);
}

void disable_torque()
{
  write_address(0x18, [0]);
}

void set_angvel(float angvel)
{
  float rpm= angvel / (2 * 3.1415926535897) * 60; 
  int angvel_enc = rpm/0.11;
  if (angvel_enc<0)
  {
    byte hi = abs(angvel_enc) / 256 + 4;
    byte lo = abs(angvel_enc) % 256;
  }
  else
  {
    byte hi = angvel_enc/256;
    byte lo = angvel_enc % 256;
  }
  
  startBits();
  instruction[4] = 0x05;
  instruction[5] = 0x03;
  instruction[6] = 0x08;
  instruction[7] = 0x00;
  formMsg();
}
*/

void send_serial(byte msg[])
{
  int numBytesAvail;
  digitalWrite(EN,HIGH);
  mySerial.write(msg, sizeof(msg));
  digitalWrite(EN,LOW);
  delay(100);  
  numBytesAvail = mySerial.available();   // get number of bytes in response message 
  for (int i=0; i<numBytesAvail; i++)
    Serial.print(mySerial.read(), HEX);      // print each one as hex number on console
}

int formMsg()
{

}

void setup()  
{
  Serial.begin(9600);
  mySerial.begin(57600);     // set the data rate for the SoftwareSerial port
  pinMode(EN,OUTPUT);
}

void loop()
{
  read_temperature();
}
