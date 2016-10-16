#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>

const char *monthName[12] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

tmElements_t tm;

void setup() {
    Serial.begin(9600);
  Serial.println("Program Start ") ;
}

void loop() {

ShowDateTime() ;
delay(800);
}



void ShowDateTime()
{
 if ( RTC.read(tm) ) 
    {
          Serial.println("---Date TIme-----") ;
          Serial.println(StrDate()) ;
          Serial.println(StrTime()) ;

    }
}
String  StrDate() {
  String ttt ;
  ttt = StringDate(tm.Year-30, tm.Month, tm.Day) ;
  Serial.print("Date:") ;
  Serial.print(ttt) ;
  Serial.print("\n") ;
  
  return ttt ;
}

String  StringDate(int yyy, int mmm, int ddd) {
  String ttt ;
  //nowT  = now;
  ttt = print2digits(yyy) + "-" + print2digits(mmm) + "-" + print2digits(ddd) ;
  return ttt ;
}


String  StrTime() {
  String ttt ;
  ttt = StringTime(tm.Hour, tm.Minute, tm.Second) ;
    Serial.print("Time:") ;
  Serial.print(ttt) ;
  Serial.print("\n") ;
  return ttt ;
}

String  StringTime(int hhh, int mmm, int sss) {
  String ttt ;
  ttt = print2digits(hhh) + ":" + print2digits(mmm) + ":" + print2digits(sss) ;
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
