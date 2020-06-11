// ====================================================
//
//
// Author   = Ade Hermawan Fajri
// Project  = Sanyo Otomatis
//
//
// ====================================================

#define echoPin 12
#define initPin 14

unsigned long pulseTime = 0; // variabel untuk membaca pulsa
int touchPin = 2; //relay
int relayPin = 5; //relay
int val = 0;
int ultrasonik;
int tMax = 100;
int lowTg = 20;
int highTg = 80;
int denumFactor = 58;

// ================== BASIC SETUP ====================

void setup(){
  Serial.begin(9600);
  Serial.println(" cm");

  // setting output pada pin initPin
  pinMode(initPin, OUTPUT);
  // setting inpt untuk pin echo
  pinMode(echoPin, INPUT);
}

void loop(){
  delay(100);

  digitalWrite(initPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(initPin, LOW);

  pulseTime = pulseIn(echoPin,HIGH);
  ultrasonik = tMax - pulseTime / denumFactor, DEC;

  Serial.print(ultrasonik);
  Serial.println(" cm");

  if(ultrasonik < lowTg){
    do{
      delay(50);
      digitalWrite(relayPin,HIGH);
      Serial.print(ultrasonik);
      Serial.println(" cm NYALA");

      delay(100);
      digitalWrite(initPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(initPin, LOW);
      pulseTime = pulseIn(echoPin, HIGH);
      ultrasonik = tMax - pulseTime / denumFactor, DEC;
      delay(100);
      Serial.print(ultrasonik);
      Serial.println(" cm");
    } 
    while (ultrasonik < highTg);
  }

  if(ultrasonik > highTg){
    do{
      delay(50);
      digitalWrite(relayPin,LOW);
      Serial.print(ultrasonik);
      Serial.println(" cm MATI");
      delay(100);
      digitalWrite(initPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(initPin, LOW);
      pulseTime = pulseIn(echoPin, HIGH);
      ultrasonik = tMax - pulseTime / denumFactor, DEC;
      delay(100);
      Serial.print(ultrasonik);
      Serial.println(" cm");
    }
    while (ultrasonik > lowTg);
  }
}
