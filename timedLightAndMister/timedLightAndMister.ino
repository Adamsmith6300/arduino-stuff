
#include <Wire.h>
#include <RTClib.h>
#include <Time.h>
#include <TimeAlarms.h>

RTC_DS1307 RTC;

int lightRelay = 2;
int misterState = LOW;
const int misterPin = 5; 
unsigned long previousMillis = 0;
const long OnTime = 3000;
const long OffTime = 3000;

// Start Time
int sHour = 17;
int sMinute = 12;
int sSecond = 0;
 
// End Time
int eHour = 17;
int eMinute = 22;
int eSecond = 0;

void setup()
{
// Set the light to off immediately
digitalWrite(lightRelay, HIGH);

Serial.begin(9600);
Wire.begin();
RTC.begin();
  
pinMode(misterPin, OUTPUT);           // set pinModes
pinMode(lightRelay, OUTPUT);          //set pinModes

Alarm.alarmRepeat(17,12,0, LightOn);           //  Turn on the light
Alarm.alarmRepeat(17,22,0, LightOff);              //  Turn off the light

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


void loop()
{
RTC.now();
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
  Alarm.delay(1000);
}


//Turn on the light 
void LightOn()
{
  digitalWrite(lightRelay, LOW); 
}

void LightOff()
{
  digitalWrite(lightRelay, HIGH); 
}
