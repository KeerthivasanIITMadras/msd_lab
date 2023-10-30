#include <Servo.h>
Servo myservo;

int pos = 0;

void setup() {
  Serial.begin(9600);
  myservo.attach(6);
  pinMode(12, OUTPUT);  // LED
  pinMode(7,OUTPUT);
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) {
    int s1 = analogRead(A2);
    Serial.println(s1);
    if (s1 <200) {
      digitalWrite(7,HIGH);
      break;
    }
    myservo.write(pos);
    digitalWrite(7,LOW);
    delay(15);

}
}