void setup() {
  Serial.begin(9600);
  pinMode(A2,INPUT);
}

void loop() {
  int potValue = analogRead(A2); 
  Serial.print("Potentiometer Value: ");
  Serial.println(potValue); 
  delay(1000);
}