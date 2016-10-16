#include <Wire.h>
#include <Eeprom24C32_64.h>
#define EEPROM_ADDRESS 0x50
#define DataCounter_Adr 10
#define DataStart_Adr 100
static Eeprom24C32_64 eeprom(EEPROM_ADDRESS);
byte SaveData[16] ;
long DataCounter= 0 ;

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    Serial.println("Program Start Here");
         eeprom.initialize();
         eeprom.writeByte(DataCounter_Adr,(int)(DataCounter/256));
            delay(10);
         eeprom.writeByte(DataCounter_Adr+1,(int)(DataCounter % 256));
            delay(10);
         Serial.print("Read Counter is :(") ;
           Serial.print(eeprom.readByte(DataCounter_Adr)*256+eeprom.readByte(DataCounter_Adr+1)) ;
           Serial.print(") \n") ;      
}

void loop() {
  // put your main code here, to run repeatedly:

}
