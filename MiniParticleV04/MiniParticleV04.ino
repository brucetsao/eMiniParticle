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
//char ssid[] = "TSAO";      // your network SSID (name)
//char pass[] = "TSAO1234";     // your network password
int keyIndex = 0;               // your network key Index number (needed only for WEP)


#define pmsDataLen 30
uint8_t bufHead[2];
uint8_t buf[pmsDataLen];
int idx = 0;
int pm25 = 0;
uint16_t PM01Value=0;          //define PM1.0 value of the air detector module
uint16_t PM2_5Value=0;         //define PM2.5 value of the air detector module
uint16_t PM10Value=0;         //define PM10 value of the air detector module
String MacAddress ;
void setup() {
  Serial.begin(9600);

  mySerial.begin(9600); // PMS 3003 UART has baud rate 9600
    
}

void loop() { // run over and over
   boolean readdataOK = false ;
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
                                readdataOK = true ;
                                 break ;
                            }
                    }
                mySerial.readBytes(bufHead,1);
 //     Serial.print( buf[idx] ,HEX) ;
  //    idx++ ;
    }
  //    Serial.print(")\n") ;
  // check if data header is correct
  if (readdataOK) 
      mySerial.readBytes(buf,pmsDataLen);
      /*
      for (idx = 0 ; idx <pmsDataLen ; idx ++)
          {
             buf[idx] = mySerial.read();   
          }
          */
          
  // if (buf[0] == 0x42 && buf[1] == 0x4d) 
  if (readdataOK) 
      {
        pm25 = ( buf[10] << 8 ) | buf[11]; 
        Serial.print("pm2.5: ");
        Serial.print(pm25);
        Serial.println(" ug/m3");
       
      }
     delay(500);
}




