#include <AntaresESP8266HTTP.h>

#define ACCKEY    "1e2d478edeb4f485:8a609ec56865b1dd"
#define WIFI      "Kroniz"
#define PASS      "ade300699"

#define projName  "PDBanjir"
#define devcName  "sensor01"

AntaresESP8266HTTP antares(ACCKEY);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  antares.setDebug(true);
  antares.wifiConnection(WIFI,PASS);

}

void loop() {
  // put your main code here, to run repeatedly:
  int temp  = random(25,30);
  int hum   = random(75,90);

  antares.add("suhu",temp);
  antares.add("kelembaban",hum);

  antares.send(projName,devcName);
  delay(10000);

}
