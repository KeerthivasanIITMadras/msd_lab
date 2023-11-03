#include <Servo.h>

Servo myServo;
int servoAngle = 0;
bool isSweeping = false;

void setup() {
  Serial.begin(9600); 
  myServo.attach(5);  
  myServo.write(servoAngle); 
  Serial.println("Enter '1' to start sweeping, '2' to stop.");
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == '1') {
      if (!isSweeping) {
        Serial.println("Sweeping ON");
        isSweeping = true;
        servoSweep();
      }
    } else if (command == '2') {
      if (isSweeping) {
        Serial.println("Sweeping OFF");
        isSweeping = false;
      }
    } else {
      Serial.println("Invalid command. Enter '1' to start sweeping, '2' to stop.");
    }
  }
}

void servoSweep() {
  while (isSweeping) {
    for (servoAngle = 0; servoAngle <= 180; servoAngle++) {
      myServo.write(servoAngle);
      delay(15); 
    }
    for (servoAngle = 180; servoAngle >= 0; servoAngle--) {
      myServo.write(servoAngle);
      delay(15); 
    }
  }
}
