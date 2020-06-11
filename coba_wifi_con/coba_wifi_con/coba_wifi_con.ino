#include <ESP8266WiFi.h>

char ssid[]           = "Kroniz";
char password[]       = "ade300699";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println();

  WiFi.begin(ssid,password);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Disconected");
  } else {
    Serial.println("Connected");
  }
  delay(1000);
}
