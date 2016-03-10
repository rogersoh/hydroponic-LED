//this is the working hydroponic system lighting

/*
   TimeAlarmExample.pde

   This example calls alarm functions at 8:30 am and at 5:45 pm (17:45)
   and simulates turning lights on at night and off in the morning
   A weekly timer is set for Saturdays at 8:30:30

   A timer is called every 15 seconds
   Another timer is called once only after 10 seconds

   At startup the time is set to Jan 1 2011  8:29 am
*/

#include <Time.h>
#include <TimeAlarms.h>
#include <DS1307RTC.h>
#include <rgb_lcd.h>
#include "Ultrasonic.h"

rgb_lcd lcd;
Ultrasonic ultrasonic(8);  //ultrasonic pin

const int colorR = 0;
const int colorG = 160;
const int colorB = 0;

//Pin setting

//LED lighting output pin control thru mosfet
const int ledPin =  7;      // the number of the LED pin
const int fanPin = 5; // the number of the fan pin
const int tempPin = A3; //Temperature sensor
const int buttonPin = 2;     // the number of the pushbutton pin
const int batteryVoltPin = A2; //voltage measurement pin
const int batteryLowLEDPin = 6; //low battery voltage LED pin
const long displayOnDuration = 300000; // lcd on for 5 minutes (300 000 ms)

// Variables will change :
long lastDisplayOnTime = 0; // the last time display was ON
long nearbyOnTime = 0 ; // time the LED is on when obstacle are in front
int temperatureValue;
double temperatureC;

//state
int ledState = LOW;             // ledState used to set the LED
int fanState = LOW;
int buttonState = LOW;         // variable for reading the pushbutton status
bool morningAlarmState = false; // morning alarm off

void setup()
{
  Serial.begin(9600);

  // set the digital pin
  pinMode(ledPin, OUTPUT);
  pinMode(fanPin, OUTPUT);
  pinMode(batteryLowLEDPin, OUTPUT);
  pinMode(buttonPin, INPUT);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.setRGB(0, 0, 0);
  lcd.noDisplay();

  //  setTime(8,29,0,1,1,11); // set time to Saturday 8:29:00am Jan 1 2011
  //  setTime(8,29,0,1,1,11); // set time to Saturday 8:29:00am Jan 1 2011
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if (timeStatus() != timeSet)
    Serial.println("Unable to sync with the RTC");
  else
    Serial.println("RTC has set the system time");

  // create the alarms
  Alarm.alarmRepeat(05, 30, 0, MorningAlarm); // 5:30am every day
  Alarm.alarmRepeat(11, 30, 0, MorningAlarm);
  Alarm.alarmRepeat(19, 00, 0, EveningAlarm); // 19:00pm every day
  Alarm.alarmRepeat(dowSaturday, 8, 30, 30, WeeklyAlarm); // 8:30:30 every Saturday
  Alarm.timerRepeat(15, Repeats);            // timer for every 15 seconds
  Alarm.timerOnce(10, OnceOnly);             // called once after 10 seconds
}

void  loop() {
  digitalClockDisplay();
  fanControl();
  distance();
  Alarm.delay(500); // wait 0.5 second between clock display
}


