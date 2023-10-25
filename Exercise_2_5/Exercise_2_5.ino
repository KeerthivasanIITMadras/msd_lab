#include <LiquidCrystal.h>
#include <string.h>
//#include <iostream>
using namespace std;
#include <Servo.h>
Servo myservo;

int pos = 0;


LiquidCrystal lcd(2,3,4,8,12,13); // Initialize the LCD with your pin configuration

String receivedData = ""; // Store received data

void setup() {
  Serial.begin(9600); // Set the baud rate to match your serial communication
  lcd.begin(16, 2);   // Initialize the LCD dimensions (16x2)
  lcd.clear();        // Clear the LCD screen
  Serial.println("Enter a string of format “a**b*c” ( represents numbers):");
  myservo.attach(5);
  pinMode(12, OUTPUT);  // LED
}

void loop() {
  if (Serial.available() > 0) {
  receivedData = Serial.readString();
  parseReceivedData();
  if (receivedData == "ON") {
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
  }
}

void parseReceivedData() {
  String cmnd = receivedData.substring;
  // Display the numbers on the LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Cmnd: ");
    lcd.print(cmnd);
}
