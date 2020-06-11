// ========================================================================================
//
// Project  : PDBanjir
// Sensor   : HC-SR 04
// Board    : NodeMcu ESP8266 Lolin V3
//
// ========================================================================================

// ======================================== LIBRARY =======================================

#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <time.h>
#include <AntaresESP8266HTTP.h>

//===================================== DEFINE VARIABLE ==================================

#define NTP_OFFSET    60*60*7         //GMT+7
#define NTP_ADDRESS   "pool.ntp.org"  //Server of NTP

#define ACCKEY        "1e2d478edeb4f485:8a609ec56865b1dd" // Antares Access Key
#define WIFI          "Kroniz"        //SSID
#define PASS          "ade300699"     //Password of Wifi

#define projName      "PDBanjir"      //Project Name in Antares
#define devcName      "pd0001"        //DeviceName

#define trigPin       14
#define echoPin       12
#define buzzPin       5

// =============================== DECLARE OTHER VARIABLE ================================

String dow[7] = {
  "Minggu",
  "Senin",
  "Selasa",
  "Rabu",
  "Kamis",
  "Jum'at",
  "Sabtu",
};

String moy[12]={
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

int ts    = 30;     // Tinggi Sensor dari permukaan air (cm)
int ka    = 5000;   // kedalaman air pada sungai / danau (cm)
int aws   = 4000;   // trigger awas (cm)
int was   = 3500;   // trigger waspada (cm)
long dnm  = 29.1;   // Faktor Pembagi hasil sensor
int cal   = 0;      // hasil kalibrasi

// ================================== INSTALL LIBRARY =================================

AntaresESP8266HTTP antares(ACCKEY);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP,NTP_ADDRESS,NTP_OFFSET);

// =================================== SETUP PROGRAM ===================================

void setup() {
  Serial.begin(9600);
  WiFi.begin(WIFI,PASS);
  antares.setDebug(false);
  antares.wifiConnection(WIFI,PASS);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
    Serial.println("");
  }

  timeClient.begin();

  pinMode(buzzPin,OUTPUT);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
}

// ==================================== MAIN PROGRAM ===================================

void loop() {
  timeClient.update();
  int seconds       = timeClient.getSeconds();
  String timeStamp  = dateCather();
  String waktu      = timeClient.getFormattedTime();
  String hari       = dow[timeClient.getDay()];

  if(seconds == 0){
    long jarak,jakir;
    long jatol = 0;
    int tinggi;
    for(int i=0;i<40;i++){
      jarak = count();
      jatol = jatol + jarak;
      delay(800);
    }
    jakir   = jatol / 40;
    tinggi  = ka + ts - jakir;

    if(tinggi>ka){
      int stat = 1;             //id banjir
      dataSender(timeStamp,tinggi,stat,waktu);
      printall(hari,timeStamp,waktu,tinggi);
      buzzer();
    } else if(tinggi<=ka&&tinggi>=aws){
      int stat = 2;             // id siaga
      dataSender(timeStamp,tinggi,stat,waktu);
      printall(hari,timeStamp,waktu,tinggi);
      buzzer();                 
    } else if(tinggi<aws&&tinggi>was){
      int stat = 3;             // id waspada
      dataSender(timeStamp,tinggi,stat,waktu);
      printall(hari,timeStamp,waktu,tinggi);
    } else{
      int stat = 4;             // id aman
      dataSender(timeStamp,tinggi,stat,waktu);
      printall(hari,timeStamp,waktu,tinggi);
    }
  }
}

// ==================================== SIDE PROGRAM ===================================

void buzzer(){
  tone(buzzPin,500,1000);
  tone(buzzPin,300,1000);
}

long count(){
  long dur,jarak;
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);

  dur = pulseIn(echoPin,HIGH);
  jarak = (dur/2)/dnm;  

  return jarak;
}

void dataSender(
  String tgl,
  int tinggi,
  int stat,
  String jam){
  antares.add("tanggal",tgl);
  antares.add("ketinggian",tinggi);
  antares.add("status",stat);
  antares.add("jam",jam);

  antares.send(projName,devcName);
}

String dateCather(){
  unsigned long epochTime = timeClient.getEpochTime();
  struct tm *ptm = gmtime ((time_t *)&epochTime);

  int monthDay = ptm->tm_mday;
  int currentMonth = ptm->tm_mon+1;
  String CurrentMonthName = moy[currentMonth-1];
  int currentYear = ptm->tm_year+1900;
  String currentDate  = String(monthDay)+"-"+String(CurrentMonthName)+"-"+String(currentYear);

  return currentDate;
}

void printall(String hari, String tanggal, String jam, int tinggi){
  Serial.print(hari);
  Serial.print(",");
  Serial.println(tanggal);
  Serial.println(jam);
  Serial.print("Ketinggian : ");
  Serial.println(tinggi);
  Serial.println("");
}
