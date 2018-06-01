// Date and time functions using a DS3231 RTC connected via I2C and Wire Lib
 
#include <Wire.h>
#include <RTClib.h>
#include <Time.h>
#include <TimeAlarms.h>
 
RTC_DS1307 RTC;
 
// Start Time
int sHour = 7;
int sMinute = 00;
int sSecond = 0;
 
// End Time
int eHour = 19;
int eMinute = 00;
int eSecond = 0;
 
int lightRelay = 2;

int misterState = LOW;
const int misterPin = 5; 
unsigned long previousMillis = 0;
const long OnTime = 2000;
const long OffTime = 1200000;
 
void setup() {
  // Set the relay to off immediately
  digitalWrite(lightRelay, HIGH);
  pinMode(misterPin, OUTPUT);
   
  Serial.begin(9600);
  Wire.begin();
  RTC.begin();
   
  // Set the pinmode
  pinMode(lightRelay, OUTPUT);
  pinMode(misterPin, OUTPUT);
   
  // Notify if the RTC isn't running
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running");
  }
 
  // Get time from RTC
  DateTime current = RTC.now();
  DateTime compiled = DateTime(__DATE__, __TIME__);
  if (current.unixtime() < compiled.unixtime()) {
    Serial.println("RTC is older than compile time! Updating");
    RTC.adjust(DateTime(__DATE__, __TIME__));    
  }
 
 // Use RTC time to set the start time
  setTime(sHour, sMinute, sSecond, current.day(), current.month(), current.year());
  time_t s = now();
 
  // Use RTC time to set the end time 
  setTime(eHour, eMinute, eSecond, current.day(), current.month(), current.year());   
  time_t e = now();
   
  // Use RTC time to set the current time
  setTime(current.hour(), current.minute(), current.second(), current.day(), current.month(), current.year());  
  time_t n = now();    

 // Test if grow light should be on
 if (s <= n && n <= e) {
    digitalWrite(lightRelay, LOW);  // Sets the grow light "on"
  } 
    
}
 

void loop() {
  // put your main code here, to run repeatedly:
  
DateTime now = RTC.now();

   if (sHour <= RTC.now && RTC.now <= eHour) {
    digitalWrite(lightRelay, LOW);
    
unsigned long currentMillis = millis();
if ((misterState == HIGH) && (currentMillis - previousMillis >= OnTime)) 
{
  misterState = LOW;
  previousMillis = currentMillis;
  digitalWrite(misterPin, misterState);
}
 else if ((misterState == LOW) && (currentMillis - previousMillis >= OffTime))
 {
  misterState = HIGH;
  previousMillis = currentMillis;
  digitalWrite(misterPin, misterState);
  }
}

