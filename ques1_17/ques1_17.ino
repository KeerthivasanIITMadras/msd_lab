#include <LiquidCrystal.h>

LiquidCrystal lcd(2,3,4,8,12,13); 

const int switchPin = 7; 
int switchState = HIGH; 
int prevSwitchState = HIGH; 
int pressCount = 0; 

void setup() {
  Serial.begin(9600); 
  lcd.begin(16, 2); 
  lcd.print("Presses: 0");
  pinMode(switchPin, INPUT_PULLUP); 

void loop() {
  switchState = digitalRead(switchPin);

  if (switchState == LOW && prevSwitchState == HIGH) {
    // Switch has been pressed
    pressCount++;
    updateLCD();
  }

  prevSwitchState = switchState;
}

void updateLCD() {
  lcd.setCursor(0, 1);
  lcd.print("Presses:   "); 
  lcd.setCursor(9, 1);
  lcd.print(pressCount);
  Serial.print("Switch pressed. Presses: ");
  Serial.println(pressCount);
}
