//******************************
 //*Copyright (c) 2015, DFRobot
 //*All rights reserved
 //*Abstract: Read value of PM1, PM2.5 and PM10 of air quality
 //*
 //*Version：V2.0
 //*Author：Jason, jason.ling@dfrobot.com
 //*Date：Feb.2016
 //******************************
 #include <SoftwareSerial.h>
#include <Arduino.h>
#define LENG 32
char buf[LENG];
 
int PM01Value=0;          //define PM1.0 value of the air detector module
int PM2_5Value=0;         //define PM2.5 value of the air detector module
int PM10Value=0;         //define PM10 value of the air detector module
 SoftwareSerial mySerial(6, 7); // RX, TX
 
void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600); // PMS 3003 UART has baud rate 9600
}
 
void loop()
{
  if(mySerial.available()) 
  {
    mySerial.readBytes(buf,LENG);
    if(buf[0] == 0x42 && buf[1] == 0x4d){
      if(checkValue(buf,LENG)){
        PM01Value=transmitPM01(buf); //count PM1.0 value of the air detector module
        PM2_5Value=transmitPM2_5(buf);//count PM2.5 value of the air detector module
        PM10Value=transmitPM10(buf); //count PM10 value of the air detector module 
      }           
    } 
  }
  static unsigned long OledTimer=millis();  
    if (millis() - OledTimer >=1000) 
    {
      OledTimer=millis(); 
       
      Serial.print("PM1.0: ");  //send PM1.0 data to bluetooth
      Serial.print(PM01Value);
      Serial.println("  ug/m3");            
     
      Serial.print("PM2.5: ");  //send PM1.0 data to bluetooth
      Serial.print(PM2_5Value);
      Serial.println("  ug/m3");     
       
      Serial.print("PM10:  ");  //send PM1.0 data to bluetooth
      Serial.print(PM10Value);
      Serial.println("  ug/m3");   
    }
   
}
char checkValue(char *thebuf, char leng)
{  
  char receiveflag=0;
  int receiveSum=0;
  char i=0;
 
  for(i=0;i<leng;i++)
  {
  receiveSum=receiveSum+thebuf[i];
  }
    
  if(receiveSum==((thebuf[leng-2]<<8)+thebuf[leng-1]+thebuf[leng-2]+thebuf[leng-1]))  //check the serial data 
  {
    receiveSum=0;
    receiveflag=1;
  }
  return receiveflag;
}
 
int transmitPM01(char *thebuf)
{
  int PM01Val;
  PM01Val=((thebuf[4]<<8) + thebuf[5]); //count PM1.0 value of the air detector module
  return PM01Val;
}
 
//transmit PM Value to PC
int transmitPM2_5(char *thebuf)
{
  int PM2_5Val;
  PM2_5Val=((thebuf[6]<<8) + thebuf[7]);//count PM2.5 value of the air detector module
  return PM2_5Val;
  }
 
//transmit PM Value to PC
int transmitPM10(char *thebuf)
{
  int PM10Val;
  PM10Val=((thebuf[8]<<8) + thebuf[9]); //count PM10 value of the air detector module  
  return PM10Val;
}
