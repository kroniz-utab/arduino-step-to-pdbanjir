void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Mulai");

}

void loop() {
  // put your main code here, to run repeatedly:
  int temp = random(25,31);
  int hum = random(75,90);

  Serial.println("Temperature : ");
  Serial.println(temp);
  Serial.println("Kelembaban : ");
  Serial.println(hum);

  delay(1000);
}
