// ========================================================================================
//
// Project    : NTP COBA
// Sensor     : -
// Board      : ESP8266 NodeMcu Lolin V3
//
// ========================================================================================

#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <time.h>

#define NTP_OFFSET    60*60*7             // GMT+7
#define NTP_ADDRESS   "pool.ntp.org"

const char *ssid      = "Kroniz";
const char *password  = "ade300699";

String daysOfTheWeek[7] = {
  "Minggu",
  "Senin",
  "Selasa",
  "Rabu",
  "Kamis",
  "Jum'at",
  "Sabtu",
};

String months[12]={
  "Januari", 
  "Februari", 
  "Maret", 
  "April", 
  "Mei", 
  "Juni", 
  "Juli", 
  "Agustus", 
  "September", 
  "Oktober", 
  "November", 
  "Desember"
};

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP,NTP_ADDRESS,NTP_OFFSET);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin(ssid,password);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
    Serial.println("");
  }
  timeClient.begin();
}

void loop() {
  timeClient.update();
  unsigned long epochTime = timeClient.getEpochTime();
  String formattedTime = timeClient.getFormattedTime();
  struct tm *ptm = gmtime ((time_t *)&epochTime);
  int seconds = timeClient.getSeconds();

  int monthDay = ptm->tm_mday;
  int currentMonth = ptm->tm_mon+1;
  String CurrentMonthName = months[currentMonth-1];
  int currentYear = ptm->tm_year+1900;
  String currentDate = String(monthDay)+"-"+String(CurrentMonthName)+"-"+String(currentYear);
  
//  Serial.print(daysOfTheWeek[timeClient.getDay()]);
//  Serial.print(", ");
//  Serial.println(currentDate);
//  Serial.println(formattedTime);
//  Serial.println("");
//  delay(1000);
  if(seconds==0){
    Serial.print(daysOfTheWeek[timeClient.getDay()]);
    Serial.print(", ");
    Serial.println(currentDate);
    Serial.println(formattedTime);
    Serial.println("");
    delay(1000);
  } else if(seconds==30){
    Serial.print(daysOfTheWeek[timeClient.getDay()]);
    Serial.print(", ");
    Serial.println(currentDate);
    Serial.println(formattedTime);
    Serial.println("");
    delay(1000);
  }
}
