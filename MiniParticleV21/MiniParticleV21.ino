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
 * RX is digital pin 3 (connect to TX of PMS 3003)
 * TX is digital pin 2 (connect to RX of PMS 3003)

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
#include <String.h> 
#include <OLED_I2C.h>



#include <Wire.h>  // Arduino IDE 內建
// LCD I2C Library，從這裡可以下載：
// https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
#include <SoftwareSerial.h>
/*
 The circuit:
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)
SoftwareSerial mySerial(RX, TX); // RX, TX
*/    
//SoftwareSerial(rxPin, txPin, inverse_logic)
SoftwareSerial mySerial(2, 3); // RX, TX

#define pmsDataLen 22
uint8_t bufHead[2];
uint8_t buf[pmsDataLen];
int idx = 0;
int pm10 = 0;
int pm25 = 0;
int pm100 = 0;
 
OLED  myOLED(SDA, SCL, 8);
extern uint8_t SmallFont[];

void setup() {
  Serial.begin(9600);
    Serial.println("Program Start Here");
  mySerial.begin(9600); // PMS 3003 UART has baud rate 9600
     myOLED.begin();
  myOLED.setFont(SmallFont); 
  DisplayClear() ;
}

void loop() { // run over and over
  retrievePM25Value() ;
    ShowPM(pm25,pm10,pm100) ;

    myOLED.update();
     delay(200);
}



void retrievePM25Value() {
   boolean readdataOK = false ;
   bool hasPm25Value = false;
  idx = 0;
  //memset(buf, 0, pmsDataLen);

   while ( mySerial.available() >0)
    {
       //    mySerial.readBytes(buf,pmsDataLen);
       mySerial.readBytes(bufHead,1);
        Serial.print(bufHead[0],HEX) ;
        
                if (bufHead[0] == 0x42 )
                    {
                     
                      mySerial.readBytes(bufHead,1);
                      //bufHead[1] ==mySerial.read();
                          if (bufHead[0] ==  0x4d )
                            {
                                hasPm25Value = true ;
                                 break ;
                            }
                    }
                mySerial.readBytes(bufHead,1);
 //     Serial.print( buf[idx] ,HEX) ;
  //    idx++ ;
    }
  //    Serial.print(")\n") ;
  // check if data header is correct
  if (hasPm25Value) 
      mySerial.readBytes(buf,pmsDataLen);
      /*
      for (idx = 0 ; idx <pmsDataLen ; idx ++)
          {
             buf[idx] = mySerial.read();   
          }
          */
          
  // if (buf[0] == 0x42 && buf[1] == 0x4d) 
  if (hasPm25Value) 
      {
          pm25 = ( buf[10] << 8 ) | buf[11]; 
          pm10 = ( buf[8] << 8 ) | buf[9]; 
          pm100 = ( buf[12] << 8 ) | buf[13]; 
          Serial.print("pm2.5: ");
          Serial.print(pm25);
          Serial.print(" ug/m3");
          Serial.print("pm1.5: ");
          Serial.print(pm10);
          Serial.print(" ug/m3");
          Serial.print("pm100: ");
          Serial.print(pm100);
          Serial.print(" ug/m3");
          Serial.println("");
          hasPm25Value = true;
       
      }

        

}

void ShowPM(int pp25, int pp10, int pp100)
{
   ShowChar("PM2.5",4,6) ;
   ShowChar("PM1.0",4,28) ;
   ShowChar("PM10",4,48) ;
  ShowNumber(String(pp25),40,2) ;
  ShowNumber(String(pp10),40,20) ;
  ShowNumber(String(pp100),40,40) ;
  
 
}

void DisplayClear()
{

  myOLED.clrScr();
   myOLED.update();

}

void ShowNumber(String p, int x, int y)
{
    myOLED.drawRect(x, y, x+24, y+14);
    myOLED.print(p, x+3, y+4);
   //  myOLED.update();

}

void ShowChar(String p, int x, int y)
{
       myOLED.print(p, x, y);
   //  myOLED.update();
 
}




