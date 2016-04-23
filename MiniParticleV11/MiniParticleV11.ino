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
#include <String.h> 
#include <SoftwareSerial.h>
/*
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
String MacAddress ;

void setup() {
  Serial.begin(9600);
  Serial.println("Program Start Here");
  mySerial.begin(9600); // PMS 3003 UART has baud rate 9600

}

void loop() { // run over and over
  retrievePM25Value() ;

     delay(10000);
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

