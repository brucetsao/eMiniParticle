 /*
 This example demonstrate how to read pm2.5 value on PMS 3003 air condition sensor

 PMS 3003 pin map is as follow:
    PIN1  :VCC, connect to 5V
    PIN2  :GND
    PIN3  :SET, 0:Standby mode, 1:operating mode
    PIN4  :RXD :Serial RX
    PIN5  :TXD :Serial TX
    PIN6  :RESET
    PIN7  :NC
    PIN8  :NC

 In this example, we only use Serial to get PM 2.5 value.

 The circuit:
 * RX is digital pin 0 (connect to TX of PMS 3003)
 * TX is digital pin 1 (connect to RX of PMS 3003)

 */
// OLED_I2C_Graph_Demo
// Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
// web: http://www.RinkyDinkElectronics.com/
//
// A quick demo of how to use my OLED_I2C library.
//
// To use the hardware I2C (TWI) interface of the Arduino you must connect
// the pins as follows:
//
// Arduino Uno/2009:
// ----------------------
// Display:  SDA pin   -> Arduino Analog 4 or the dedicated SDA pin
//           SCL pin   -> Arduino Analog 5 or the dedicated SCL pin
//
// Arduino Leonardo:
// ----------------------
// Display:  SDA pin   -> Arduino Digital 2 or the dedicated SDA pin
//           SCL pin   -> Arduino Digital 3 or the dedicated SCL pin
//
// Arduino Mega:
// ----------------------
// Display:  SDA pin   -> Arduino Digital 20 (SDA) or the dedicated SDA pin
//           SCL pin   -> Arduino Digital 21 (SCL) or the dedicated SCL pin
//
// Arduino Due:
// ----------------------
// Display:  SDA pin   -> Arduino Digital 20 (SDA) or the dedicated SDA1 (Digital 70) pin
//           SCL pin   -> Arduino Digital 21 (SCL) or the dedicated SCL1 (Digital 71) pin
//
// The internal pull-up resistors will be activated when using the 
// hardware I2C interfaces.
//
// You can connect the OLED display to any available pin but if you use 
// any other than what is described above the library will fall back to
// a software-based, TWI-like protocol which will require exclusive access 
// to the pins used, and you will also have to use appropriate, external
// pull-up resistors on the data and clock signals.
//
#include <Arduino.h>
#include <Wire.h>  // Arduino IDE 內建
#include <String.h> 
#include <OLED_I2C.h>




// LCD I2C Library，從這裡可以下載：
// https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
#include <Math.h>
#include <SoftwareSerial.h>
/*
 The circuit:
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)
SoftwareSerial mySerial(RX, TX); // RX, TX
*/    
//SoftwareSerial(rxPin, txPin, inverse_logic)
SoftwareSerial mySerial(2, 3); // RX, TX
//char ssid[] = "TSAO";      // your network SSID (name)
//char pass[] = "TSAO1234";     // your network password
int keyIndex = 0;               // your network key Index number (needed only for WEP)


#define pmsDataLen 24

unsigned char buf[pmsDataLen];
int idx = 0;
int pm10 = 0;
int pm25 = 0;
int pm100 = 0;
//uint16_t PM01Value=0;          //define PM1.0 value of the air detector module
//uint16_t PM2_5Value=0;         //define PM2.5 value of the air detector module
//uint16_t PM10Value=0;         //define PM10 value of the air detector module
String MacAddress ;
OLED  myOLED(SDA, SCL, 8);
extern uint8_t SmallFont[];

#include "Adafruit_SHT31.h"

Adafruit_SHT31 sht31 = Adafruit_SHT31();

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif

bool hasPm25Value = false;

void setup() {
  initSensor() ;
  DisplayClear() ;
  //  delay(5000);
  ShowScreen() ;
  myOLED.update();

}

void loop() 
{ // run over and over
         
        retrievePM25Value() ;
    if (hasPm25Value )
                ShowPM()  ;
       ShowHumidity() ;
        myOLED.update();  
        delay(10000);
}




void retrievePM25Value() 
{
     hasPm25Value = false;
     int  count = 0;
     int ckecksum = 0 ;
     int exptsum = 0 ;
     memset(buf, 0, pmsDataLen);

   while ( mySerial.available() && count < pmsDataLen )
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
                  count =1 ;
                  continue ;
                  
               }
          if (buf[1] == 0x4d && count == 1 )
               {
                  count =2 ;
                  continue ;
                 
               }
          if (count >= 2 )
               {
                     count++ ;
             if (count >=(pmsDataLen) )
                   {
                      hasPm25Value = true ;
                      break ;
                   }
                  continue ;
             }

        }                                        
 

    if (hasPm25Value )
      {
        for (int i = 0 ; i < (pmsDataLen-2) ; i++)
           ckecksum = ckecksum + buf[i] ;
        exptsum = ((unsigned int)buf[22] << 8 )+ ((unsigned int)buf[23]) ;
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

void ShowHumidity()
{
   float t = sht31.readTemperature();
  float h = sht31.readHumidity();
  ShowNumber(String((int)round(t)),90,10,20) ;
  ShowNumber(String((int)round(h)),90,30,20) ;
 //    myOLED.update();
   Serial.print("Temperature :(");
   Serial.print(t);
  Serial.print("),");
   Serial.print("Humidity :(");
    Serial.print(h); 
  Serial.print(") \n");
  
  
 
}


void ShowPM()
{

  ShowNumber(String(pm25),40,2,38) ;
  ShowNumber(String(pm10),40,20,38) ;
  ShowNumber(String(pm100),40,40,38) ;
  
//  myOLED.update();
}



void DisplayClear()
{

  myOLED.clrScr();
   myOLED.update();

}

void ShowNumber(String p, int x, int y,int sizeN)
{
    myOLED.drawRect(x, y, x+sizeN, y+14);
    myOLED.clrRect(x+1, y+1, x+sizeN-2, y+12);
    myOLED.print(p, x+3, y+4);
   //  myOLED.update();

}


void ShowChar(String p, int x, int y)
{
       myOLED.print(p, x, y);
   //  myOLED.update();
 
}

void initSensor()
{

  Serial.begin(9600);
  Serial.println("Program Start") ;
  mySerial.begin(9600); // PMS 3003 UART has baud rate 9600
     myOLED.begin();
  myOLED.setFont(SmallFont); 
  DisplayClear() ;
    if (! sht31.begin(0x44)) 
  {   // Set to 0x45 for alternate i2c addr
    Serial.println("Couldn't find SHT31");
  }

  
}

void ShowScreen()
{
     ShowChar("PM2.5",4,6) ;
   ShowChar("PM1.0",4,28) ;
   ShowChar("PM10",4,48) ;
   myOLED.update();
}


