#include <Servo.h>

Servo myservo;
int servoPosition = 90; 
int switch7State = 0;  
int switch8State = 0;  
int lastSwitch7State = 0;  
int lastSwitch8State = 0;  

void setup() {
  myservo.attach(6);  
  pinMode(7, INPUT_PULLUP); 
  pinMode(8, INPUT_PULLUP); 
}

void loop() {
  
  switch7State = digitalRead(7);

  
  if (switch7State != lastSwitch7State) {
    if (switch7State == LOW) { 
      servoPosition++; 
      if (servoPosition > 180) {
        servoPosition = 180; 
      }
      myservo.write(servoPosition); 
    }
  }
  lastSwitch7State = switch7State;

  
  switch8State = digitalRead(8);

  
  if (switch8State != lastSwitch8State) {
    if (switch8State == LOW) { 
      servoPosition--; 
      if (servoPosition < 0) {
        servoPosition = 0; 
      }
      myservo.write(servoPosition); 
    }
  }
  lastSwitch8State = switch8State;
}






