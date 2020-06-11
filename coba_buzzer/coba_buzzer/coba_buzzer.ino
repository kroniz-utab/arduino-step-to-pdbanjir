#define buzzPin 5

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buzzPin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int jarak_acak;
  jarak_acak = random(20,70);

  if(jarak_acak>59){
    delay(10);
    buzzer_siaga();
    Serial.print("Ketinggian : ");
    Serial.print(jarak_acak);
    Serial.println(" cm");
    Serial.println("SIAGA!!");
  } else if(jarak_acak>49&&jarak_acak<60){
    delay(10);
    buzzer_was();
    Serial.print("Ketinggian : ");
    Serial.print(jarak_acak);
    Serial.println(" cm");
    Serial.println("Waspada!!");
  };
}

void buzzer_was(){
  tone(buzzPin,261);
  delay(200);
  tone(buzzPin,0);
  delay(200);
}

void buzzer_siaga(){
  tone(buzzPin,500);
  delay(400);
}
