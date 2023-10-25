
void setup() {
  Serial.begin(9600);
  pinMode(12, OUTPUT);  // LED
  pinMode(7, OUTPUT);
  // pinMode(A2,INPUT); // Electromagnet
}

void loop() 
{
    int s1 = analogRead(A2);
    if (s1 > 200) 
    {
      digitalWrite(7, HIGH);
    } 
    else 
    {
      digitalWrite(7, LOW);
    }
    delay(15);
}