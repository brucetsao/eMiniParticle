
// this is for Nokia 5110

/*********************************************************************
This is an example sketch for our Monochrome Nokia 5110 LCD Displays

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/338

These displays use SPI to communicate, 4 or 5 pins are required to
interface

Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#define PIN_SCE   7
#define PIN_RESET 6
#define PIN_DC    5
#define PIN_SDIN  4
#define PIN_SCLK  3

// Software SPI (slower updates, more flexible pin options):
//=== old version pin out======
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(PIN_SCLK, PIN_SDIN, PIN_DC, PIN_SCE, PIN_RESET);
// Adafruit_PCD8544 display = Adafruit_PCD8544(SCLK, DIN, D/C, CS/SCE, RST);


#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16


static const byte ASCII[][5] =
{
 {0x00, 0x00, 0x00, 0x00, 0x00} // 20  
,{0x00, 0x00, 0x5f, 0x00, 0x00} // 21 !
,{0x00, 0x07, 0x00, 0x07, 0x00} // 22 "
,{0x14, 0x7f, 0x14, 0x7f, 0x14} // 23 #
,{0x24, 0x2a, 0x7f, 0x2a, 0x12} // 24 $
,{0x23, 0x13, 0x08, 0x64, 0x62} // 25 %
,{0x36, 0x49, 0x55, 0x22, 0x50} // 26 &
,{0x00, 0x05, 0x03, 0x00, 0x00} // 27 '
,{0x00, 0x1c, 0x22, 0x41, 0x00} // 28 (
,{0x00, 0x41, 0x22, 0x1c, 0x00} // 29 )
,{0x14, 0x08, 0x3e, 0x08, 0x14} // 2a *
,{0x08, 0x08, 0x3e, 0x08, 0x08} // 2b +
,{0x00, 0x50, 0x30, 0x00, 0x00} // 2c ,
,{0x08, 0x08, 0x08, 0x08, 0x08} // 2d -
,{0x00, 0x60, 0x60, 0x00, 0x00} // 2e .
,{0x20, 0x10, 0x08, 0x04, 0x02} // 2f /
,{0x3e, 0x51, 0x49, 0x45, 0x3e} // 30 0
,{0x00, 0x42, 0x7f, 0x40, 0x00} // 31 1
,{0x42, 0x61, 0x51, 0x49, 0x46} // 32 2
,{0x21, 0x41, 0x45, 0x4b, 0x31} // 33 3
,{0x18, 0x14, 0x12, 0x7f, 0x10} // 34 4
,{0x27, 0x45, 0x45, 0x45, 0x39} // 35 5
,{0x3c, 0x4a, 0x49, 0x49, 0x30} // 36 6
,{0x01, 0x71, 0x09, 0x05, 0x03} // 37 7
,{0x36, 0x49, 0x49, 0x49, 0x36} // 38 8
,{0x06, 0x49, 0x49, 0x29, 0x1e} // 39 9
,{0x00, 0x36, 0x36, 0x00, 0x00} // 3a :
,{0x00, 0x56, 0x36, 0x00, 0x00} // 3b ;
,{0x08, 0x14, 0x22, 0x41, 0x00} // 3c <
,{0x14, 0x14, 0x14, 0x14, 0x14} // 3d =
,{0x00, 0x41, 0x22, 0x14, 0x08} // 3e >
,{0x02, 0x01, 0x51, 0x09, 0x06} // 3f ?
,{0x32, 0x49, 0x79, 0x41, 0x3e} // 40 @
,{0x7e, 0x11, 0x11, 0x11, 0x7e} // 41 A
,{0x7f, 0x49, 0x49, 0x49, 0x36} // 42 B
,{0x3e, 0x41, 0x41, 0x41, 0x22} // 43 C
,{0x7f, 0x41, 0x41, 0x22, 0x1c} // 44 D
,{0x7f, 0x49, 0x49, 0x49, 0x41} // 45 E
,{0x7f, 0x09, 0x09, 0x09, 0x01} // 46 F
,{0x3e, 0x41, 0x49, 0x49, 0x7a} // 47 G
,{0x7f, 0x08, 0x08, 0x08, 0x7f} // 48 H
,{0x00, 0x41, 0x7f, 0x41, 0x00} // 49 I
,{0x20, 0x40, 0x41, 0x3f, 0x01} // 4a J
,{0x7f, 0x08, 0x14, 0x22, 0x41} // 4b K
,{0x7f, 0x40, 0x40, 0x40, 0x40} // 4c L
,{0x7f, 0x02, 0x0c, 0x02, 0x7f} // 4d M
,{0x7f, 0x04, 0x08, 0x10, 0x7f} // 4e N
,{0x3e, 0x41, 0x41, 0x41, 0x3e} // 4f O
,{0x7f, 0x09, 0x09, 0x09, 0x06} // 50 P
,{0x3e, 0x41, 0x51, 0x21, 0x5e} // 51 Q
,{0x7f, 0x09, 0x19, 0x29, 0x46} // 52 R
,{0x46, 0x49, 0x49, 0x49, 0x31} // 53 S
,{0x01, 0x01, 0x7f, 0x01, 0x01} // 54 T
,{0x3f, 0x40, 0x40, 0x40, 0x3f} // 55 U
,{0x1f, 0x20, 0x40, 0x20, 0x1f} // 56 V
,{0x3f, 0x40, 0x38, 0x40, 0x3f} // 57 W
,{0x63, 0x14, 0x08, 0x14, 0x63} // 58 X
,{0x07, 0x08, 0x70, 0x08, 0x07} // 59 Y
,{0x61, 0x51, 0x49, 0x45, 0x43} // 5a Z
,{0x00, 0x7f, 0x41, 0x41, 0x00} // 5b [
,{0x02, 0x04, 0x08, 0x10, 0x20} // 5c ¥
,{0x00, 0x41, 0x41, 0x7f, 0x00} // 5d ]
,{0x04, 0x02, 0x01, 0x02, 0x04} // 5e ^
,{0x40, 0x40, 0x40, 0x40, 0x40} // 5f _
,{0x00, 0x01, 0x02, 0x04, 0x00} // 60 `
,{0x20, 0x54, 0x54, 0x54, 0x78} // 61 a
,{0x7f, 0x48, 0x44, 0x44, 0x38} // 62 b
,{0x38, 0x44, 0x44, 0x44, 0x20} // 63 c
,{0x38, 0x44, 0x44, 0x48, 0x7f} // 64 d
,{0x38, 0x54, 0x54, 0x54, 0x18} // 65 e
,{0x08, 0x7e, 0x09, 0x01, 0x02} // 66 f
,{0x0c, 0x52, 0x52, 0x52, 0x3e} // 67 g
,{0x7f, 0x08, 0x04, 0x04, 0x78} // 68 h
,{0x00, 0x44, 0x7d, 0x40, 0x00} // 69 i
,{0x20, 0x40, 0x44, 0x3d, 0x00} // 6a j 
,{0x7f, 0x10, 0x28, 0x44, 0x00} // 6b k
,{0x00, 0x41, 0x7f, 0x40, 0x00} // 6c l
,{0x7c, 0x04, 0x18, 0x04, 0x78} // 6d m
,{0x7c, 0x08, 0x04, 0x04, 0x78} // 6e n
,{0x38, 0x44, 0x44, 0x44, 0x38} // 6f o
,{0x7c, 0x14, 0x14, 0x14, 0x08} // 70 p
,{0x08, 0x14, 0x14, 0x18, 0x7c} // 71 q
,{0x7c, 0x08, 0x04, 0x04, 0x08} // 72 r
,{0x48, 0x54, 0x54, 0x54, 0x20} // 73 s
,{0x04, 0x3f, 0x44, 0x40, 0x20} // 74 t
,{0x3c, 0x40, 0x40, 0x20, 0x7c} // 75 u
,{0x1c, 0x20, 0x40, 0x20, 0x1c} // 76 v
,{0x3c, 0x40, 0x30, 0x40, 0x3c} // 77 w
,{0x44, 0x28, 0x10, 0x28, 0x44} // 78 x
,{0x0c, 0x50, 0x50, 0x50, 0x3c} // 79 y
,{0x44, 0x64, 0x54, 0x4c, 0x44} // 7a z
,{0x00, 0x08, 0x36, 0x41, 0x00} // 7b {
,{0x00, 0x00, 0x7f, 0x00, 0x00} // 7c |
,{0x00, 0x41, 0x36, 0x08, 0x00} // 7d }
,{0x10, 0x08, 0x08, 0x10, 0x08} // 7e ←
,{0x78, 0x46, 0x41, 0x46, 0x78} // 7f →
};
//------------------
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2




 
#include <String.h> 
#include <SoftwareSerial.h>
/*
SoftwareSerial mySerial(RX, TX); // RX, TX
*/    
//SoftwareSerial(rxPin, txPin, inverse_logic)
SoftwareSerial mySerial(8, 9); // RX, TX
//Adafruit_PCD8544 display = Adafruit_PCD8544(PIN_SCLK, PIN_SDIN, PIN_DC, PIN_SCE, PIN_RESET);

#define pmsDataLen 24
unsigned char buf[pmsDataLen];
int idx = 0;
int pm10 = 0;
int pm25 = 0;
int pm100 = 0;

bool hasPm25Value = false;

/* 
 HTU21D Humidity Sensor Example Code
 By: Nathan Seidle
 SparkFun Electronics
 Date: September 15th, 2013
 License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).
 
 Uses the HTU21D library to display the current humidity and temperature
 
 Open serial monitor at 9600 baud to see readings. Errors 998 if not sensor is detected. Error 999 if CRC is bad.
  
 Hardware Connections (Breakoutboard to Arduino):
 -VCC = 3.3V
 -GND = GND
 -SDA = A4 (use inline 330 ohm resistor if your board is 5V)
 -SCL = A5 (use inline 330 ohm resistor if your board is 5V)

 */

#include <Wire.h>
#include "SparkFunHTU21D.h"

//  create HTU21D
HTU21D myHumidity;
float humd  ;
float temp  ;
//  create RTC(DS1307 )
#include "RTClib.h"
RTC_DS1307 RTC;
DateTime nowT  ;
// use  EEPROM for DS1307 24C32 chip
#include <Eeprom24C32_64.h>
#define EEPROM_ADDRESS 0x50
#define DataCounter_Adr 10
#define DataStart_Adr 100
static Eeprom24C32_64 eeprom(EEPROM_ADDRESS);
byte SaveData[16] ;
#define DataLen 16
long DataCounter= 0 ;
#define MaxCounter 2000 

#include "String.h"

void setup() {
  Serial.begin(9600);
  Serial.println("Program Start Here");
  mySerial.begin(9600); // PMS 3003 UART has baud rate 9600
//------------for Nokia 5110
  display.begin();      //init Nokia 5110 display
  // init done

  // you can change the contrast around to adapt the display
  // for the best viewing!
  display.setContrast(50);      //set Contrast
  display.clearDisplay();       //清除螢幕
  display.display(); // show splashscreen  //

  myHumidity.begin(); 
  initRTC();

    // Initiliaze EEPROM library.
    initEEPROM() ;
    
 ShowScreen() ;
}

void loop() { // run over and over
  retrievePM25Value() ;
  ShowAllData() ;
      if (hasPm25Value)
      {
          Data2Array() ;
          ShowArrayData() ;
          Array2EEPROM() ;
          
      }
     delay(10000);
}

void retrievePM25Value()
{
  hasPm25Value = false;
  int  count = 0;
  int ckecksum = 0 ;
  int exptsum = 0 ;
  memset(buf, 0, pmsDataLen);

  while (( mySerial.available()>0) && (count < pmsDataLen) )
  {
    //    mySerial.readBytes(buf,pmsDataLen);
    buf[count] = mySerial.read();
    /*
      Serial.print("NO(") ;
      Serial.print(count) ;
      Serial.print(") , ") ;
      Serial.print( buf[count],DEC) ;
      Serial.print("\n") ;
    */
    if (buf[0] == 0x42 && count == 0 )
    {
      count = 1 ;
      continue ;

    }
    if (buf[1] == 0x4d && count == 1 )
    {
      count = 2 ;
      continue ;

    }
    if (count >= 2 )
    {
      count++ ;
      if (count >= (pmsDataLen) )
      {
        hasPm25Value = true ;
        break ;
      }
      continue ;
    }

  }


  if (hasPm25Value )
  {
    for (int i = 0 ; i < (pmsDataLen - 2) ; i++)
      ckecksum = ckecksum + buf[i] ;
    exptsum = ((unsigned int)buf[22] << 8 ) + ((unsigned int)buf[23]) ;
    if (ckecksum == exptsum)
    {
      hasPm25Value = true ;
    }
    else
    {
      hasPm25Value = false ;
      Serial.print("\n \n ERROR Check sum");
      Serial.print("\n Sensor Check sum is : ");
      Serial.print(exptsum);
      Serial.print(", \n And Data Check sum is :");
      Serial.print(ckecksum);
      Serial.println("");
      return ;
    }
    pm25 = ( buf[12] << 8 ) | buf[13];
    pm10 = ( buf[10] << 8 ) | buf[11];
    pm100 = ( buf[14] << 8 ) | buf[15];

    Serial.print("\n pm2.5: ");
    Serial.print(pm25);
    Serial.print(" ug/m3\t");
    Serial.print("pm1.0: ");
    Serial.print(pm10);
    Serial.print(" ug/m3\t");
    Serial.print("pm100: ");
    Serial.print(pm100);
    Serial.print(" ug/m3");
    Serial.println("");
  }


}



//  for Nokia use Start


void ShowAllData()
{
    if (hasPm25Value)
      {
        display.fillRoundRect(33, 0, 50, 32,1,WHITE) ;
    //  int16_t radius, uint16_t color),(33,0,15,9) ;
     //   display.drawRoundRect(33,10,15,9);
   //     display.drawRoundRect(33,20,15,9);
          display.setTextSize(1);
           display.setTextColor(BLACK);
            display.setCursor(36,0);
            display.println(pm25);
          display.setCursor(36,10);
          display.println(pm10);
          display.setCursor(36,20);
          display.println(pm100);
            display.display();    //顯示所有上面內容，必要在所有秀字命令後，一定要的
      }
        display.fillRoundRect(0, 30, 84, 20,1,WHITE) ;
      ShowHumidity() ;
  ShowDateTime() ;
}
void ShowScreen()
{
    display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  display.println("PM1.0");
  display.setCursor(0,10);
  display.println("PM2.5");
  display.setCursor(0,20);
  display.println("PM10");
display.display();    //顯示所有上面內容，必要在所有秀字命令後，一定要的

}

//--------- for Nokia 5110 use End

// for HTU21D use

void ShowHumidity()
{
       humd = myHumidity.readHumidity();
       temp = myHumidity.readTemperature();
           Serial.print("Humidity is:(");
          Serial.print(humd);
          Serial.print(") and Temperature is :(");
          Serial.print(temp);
          Serial.print(")\n");
  
        display.setTextSize(1);
      display.setTextColor(BLACK);
      display.setCursor(0,30);
      display.print((int)temp);
      display.print(".C " );
      display.print((int)humd);    
      display.print(" %" );        
    display.display();    //顯示所有上面內容，必要在所有秀字命令後，一定要的

 
}
// use RTC DS1307
void initRTC()
{
  Wire.begin();
  RTC.begin();
 
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
        RTC.adjust(DateTime(__DATE__, __TIME__));

  }
}
void ShowDateTime()
{
      Serial.print(StrDate()) ;
      Serial.print("-") ;
      Serial.print(StrTime()) ;
      Serial.print("\n") ;
     display.setTextSize(1);
      display.setTextColor(BLACK);
      display.setCursor(0,40);
      display.print(StrDate2());
      display.print("~");
      display.print(StrTime2());    
   
    display.display();    //顯示所有上面內容，必要在所有秀字命令後，一定要的

}

String  StrDate2() {
  String ttt ;
  //nowT  = now;
  nowT = RTC.now();
  // ttt = print4digits(nowT.year()) + "-" + print2digits(nowT.month()) + "-" + print2digits(nowT.day()) ;
  ttt = StringDate2(nowT.year(), nowT.month(), nowT.day()) ;
  //ttt = print4digits(NDPyear) + "/" + print2digits(NDPmonth) + "/" + print2digits(NDPday) ;
  return ttt ;
}
String  StrDate() {
  String ttt ;
  //nowT  = now;
  nowT = RTC.now();
  // ttt = print4digits(nowT.year()) + "-" + print2digits(nowT.month()) + "-" + print2digits(nowT.day()) ;
  ttt = StringDate(nowT.year(), nowT.month(), nowT.day()) ;
  //ttt = print4digits(NDPyear) + "/" + print2digits(NDPmonth) + "/" + print2digits(NDPday) ;
  return ttt ;
}

String  StringDate2(int yyy, int mmm, int ddd) {
  String ttt ;
  //nowT  = now;
  ttt = print2digits(mmm) + "" + print2digits(ddd) + "" + print2digits(ddd) ;
  return ttt ;
}


String  StringDate(int yyy, int mmm, int ddd) {
  String ttt ;
  //nowT  = now;
  ttt = print4digits(yyy) + "-" + print2digits(mmm) + "-" + print2digits(ddd) ;
  return ttt ;
}


String  StrTime2() {
  String ttt ;
  // nowT  = RTC.now();
  nowT = RTC.now();
  //  ttt = print2digits(nowT.hour()) + ":" + print2digits(nowT.minute()) + ":" + print2digits(nowT.second()) ;
  ttt = StringTime2(nowT.hour(), nowT.minute(), nowT.second()) ;
  //  ttt = print2digits(NDPhour) + ":" + print2digits(NDPminute) + ":" + print2digits(NDPsecond) ;
  return ttt ;
}
String  StrTime() {
  String ttt ;
  // nowT  = RTC.now();
  nowT = RTC.now();
  //  ttt = print2digits(nowT.hour()) + ":" + print2digits(nowT.minute()) + ":" + print2digits(nowT.second()) ;
  ttt = StringTime(nowT.hour(), nowT.minute(), nowT.second()) ;
  //  ttt = print2digits(NDPhour) + ":" + print2digits(NDPminute) + ":" + print2digits(NDPsecond) ;
  return ttt ;
}
String  StringTime2(int hhh, int mmm, int sss) {
  String ttt ;
  ttt = print2digits(hhh) + "" + print2digits(mmm) + "" + print2digits(sss) ;
  return ttt ;
}


String  StringTime(int hhh, int mmm, int sss) {
  String ttt ;
  ttt = print2digits(hhh) + ":" + print2digits(mmm) + ":" + print2digits(sss) ;
  return ttt ;
}



String  print2HEX(int number) {
  String ttt ;
  if (number >= 0 && number < 16)
  {
    ttt = String("0") + String(number, HEX);
  }
  else
  {
    ttt = String(number, HEX);
  }
  return ttt ;
}
String  print2digits(int number) {
  String ttt ;
  if (number >= 0 && number < 10)
  {
    ttt = String("0") + String(number);
  }
  else
  {
    ttt = String(number);
  }
  return ttt ;
}

String  print4digits(int number) {
  String ttt ;
  ttt = String(number);
  return ttt ;
}

// ------------init EEPROM 

void initEEPROM()
{
           eeprom.initialize();
            DataCounter  = eeprom.readByte(DataCounter_Adr)*256+eeprom.readByte(DataCounter_Adr+1) ;
         Serial.print("Read Counter is :(") ;
           Serial.print(DataCounter) ;
           Serial.print(") \n") ; 
}

void Data2Array()
{
   // nowT = RTC.now();
    SaveData[0] = (byte)(nowT.year() /256) ;
    SaveData[1] = (byte)(nowT.year() % 256) ;
    SaveData[2] = (byte)(nowT.month()) ;
    SaveData[3] = (byte)(nowT.day()) ;
    SaveData[4] = (byte)(nowT.hour()) ;
    SaveData[5] = (byte)(nowT.minute()) ;
    SaveData[6] = (byte)(nowT.second()) ;
    SaveData[7] = (byte)(pm10 / 256) ;
    SaveData[8] = (byte)(pm10 % 256) ;
    SaveData[9] = (byte)(pm25 / 256) ;
    SaveData[10] = (byte)(pm25 % 256) ;
    SaveData[11] = (byte)(pm100 / 256) ;
    SaveData[12] = (byte)(pm100 % 256) ;
    SaveData[13] = (byte)(humd) ;
      if (temp >= 0) 
        {
            SaveData[14] = 43 ;
        }
        else
        {
            SaveData[14] = 45 ;
        }
        
         SaveData[15] = (byte)(abs(temp)) ;
}

void Array2EEPROM()
{
     eeprom.writeBytes(DataStart_Adr+DataCounter*16, DataLen, SaveData);
    DataCounter ++ ;
     eeprom.writeByte(DataCounter_Adr,(int)(DataCounter/256));
    delay(10);
   eeprom.writeByte(DataCounter_Adr+1,(int)(DataCounter % 256));
    delay(10);
     Serial.print("New Counter is :(") ;
           Serial.print(DataCounter) ;
           Serial.print(") \n") ; 
     if (DataCounter >MaxCounter)
          {
            DataCounter = 0 ;
             eeprom.writeByte(DataCounter_Adr,(int)(DataCounter/256));
              delay(10);
               eeprom.writeByte(DataCounter_Adr+1,(int)(DataCounter % 256));
              delay(10);
           Serial.print("Reset Counter to  :(") ;
           Serial.print(DataCounter) ;
           Serial.print(") \n") ; 
            
          }
}


void ShowArrayData() 
{
   
   Serial.print("Data is :") ;
   Serial.print(StringDate((int)SaveData[0]*256+(int)SaveData[1],(int)SaveData[2],SaveData[3])) ;
   Serial.print(" and Time  is :") ;
   Serial.print(StringTime((int)SaveData[4],(int)SaveData[5],(int)SaveData[6])) ;
   Serial.print(" and PM1.0 is :") ;
   Serial.print((int)SaveData[7]*256+(int)SaveData[8]) ;
   Serial.print(" and PM2.5 is :") ;
   Serial.print(SaveData[9]*256+SaveData[10]) ;
   Serial.print(" and PM10 is :") ;
   Serial.print((int)SaveData[11]*256+(int)SaveData[12]) ;
   Serial.print(" and Humidity is :") ;
   Serial.print((int)SaveData[13],DEC) ;
   Serial.print(" and Temperature is :") ;
   Serial.print((int)SaveData[14]) ;
   Serial.print((int)SaveData[14],DEC) ;
   Serial.print("\n") ;
}



