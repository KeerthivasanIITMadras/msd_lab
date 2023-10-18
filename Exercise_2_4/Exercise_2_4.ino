#include <Servo.h>
Servo myservo;

int pos = 0;

void setup() {
  Serial.begin(9600);
  myservo.attach(5);
  pinMode(12, OUTPUT);  // LED
}

void loop() {
  for (; pos <= 180; pos += 1) {
    int s1 = analogRead(A2);
    Serial.println(s1);
    if (s1 > 200) {
      break;
    }
    myservo.write(pos);
    delay(15);
  }
  for (; pos >= 0; pos -= 1) {
    int s1 = analogRead(A2);
    Serial.println(s1);
    if (s1 > 200) {
      break;
    }
    myservo.write(pos);
    delay(15);
  }
}