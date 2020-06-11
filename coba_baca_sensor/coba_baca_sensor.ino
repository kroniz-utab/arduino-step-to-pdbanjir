#define trigPin 14
#define echoPin 12

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  long duration, jarak,jakir;
  long jatol = 0;
  for(int i=0;i<55;i++){
    digitalWrite(trigPin,LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin,HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin,LOW);

    duration  = pulseIn(echoPin,HIGH);
    jarak     = (duration/2) / 29.1;
    jatol     = jatol + jarak;
    
    delay(100);
  }

  jakir = jatol/55;
  
  Serial.print("jarak : ");
  Serial.print(jakir);
  Serial.println(" cm");
  Serial.println("");

  delay(5000);
}
