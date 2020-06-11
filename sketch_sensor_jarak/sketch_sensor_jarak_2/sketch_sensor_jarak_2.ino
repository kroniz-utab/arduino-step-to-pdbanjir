#define echoPin 14            
#define initPin 12  

unsigned long pulseTime = 0;  // variabel untuk membaca pulsa
int touchPin = 2; //relay
int val = 0;
int relayPin = 5; //relay
int ultrasonik;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);                                              // Setup Debug uart port if you want ?
  Serial.println(" cm" );

  // setting output pada pin initPin
   pinMode(initPin, OUTPUT);
   //setting input untuk pin Echo
   pinMode(echoPin, INPUT);
   //setup komunikasi serial
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);

      digitalWrite(initPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(initPin, LOW);

     pulseTime = pulseIn(echoPin, HIGH);
     ultrasonik = 30 - pulseTime / 53, DEC;
    

           
//      Cayenne.virtualWrite(V7, ultrasonik);              // Post Distance value in cayenne mqtt server
      Serial.print(ultrasonik); 
      Serial.println(" cm" );
//      Cayenne.loop();

      if(ultrasonik <10){  //  rules relay
      do {
      delay(50);          // wait for sensors to stabilize
      digitalWrite(relayPin, HIGH);
      Serial.print(ultrasonik); 
      Serial.println(" cm" );
//      Serial.println(" nyala" );  // check the sensors
      delay(100);
      digitalWrite(initPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(initPin, LOW);
      pulseTime = pulseIn(echoPin, HIGH);
     ultrasonik = 30 - pulseTime / 53, DEC;
     delay(100);
//      Cayenne.virtualWrite(V7, ultrasonik); // mengirim ke cayene
      Serial.print(ultrasonik); 
      Serial.println(" cm" );
//      Cayenne.loop(); //mengirim ke cayene
      } while (ultrasonik < 70);
       }
      if(ultrasonik > 20){  //  rules relay
      do {
      delay(50);          // wait for sensors to stabilize
      digitalWrite(relayPin, LOW);
      Serial.print(ultrasonik); 
      Serial.println(" cm" );
//      Serial.println(" mati" );  // check the sensors
      delay(100);
      digitalWrite(initPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(initPin, LOW);
      pulseTime = pulseIn(echoPin, HIGH);
     ultrasonik = 30 - pulseTime / 5, DEC;
     delay(100);
//      Cayenne.virtualWrite(V7, ultrasonik); //mengirim ke cayene
      Serial.print(ultrasonik); 
      Serial.println(" cm" );
//      Cayenne.loop();
      } while (ultrasonik > 20);
       }

}
