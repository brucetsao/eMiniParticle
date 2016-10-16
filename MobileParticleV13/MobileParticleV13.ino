
#include <Wire.h>

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

void setup() {
  Serial.begin(9600);
  Serial.println("Program Start Here");

    initEEPROM() ;
  for (int i = 0 ; i<DataCounter ; i++)
      {
          Serial.print("EEPROM(") ;
          Serial.print(i) ;
          Serial.print("):") ;
           EEPROM2Array(i) ;
           ShowArrayData(i) ;
            Serial.print("\n") ;
    }

}

void loop() { // run over and over

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

void EEPROM2Array(int pt)
{
     eeprom.readBytes(DataStart_Adr+pt*16, DataLen, SaveData);
    delay(10);
       
}

void ShowArrayData(int pt) 
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


