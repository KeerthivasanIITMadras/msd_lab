#include <LiquidCrystal.h>

LiquidCrystal lcd(2,3,4,8,12,13); 

const int ldrPin = A2; 
const int threshold = 500; 
const unsigned long measurementTime = 5000; 

unsigned long startTime; 
int crossingCount = 0; 
bool aboveThreshold = false;

void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud rate
  lcd.begin(16, 2); // Initialize the LCD (16 characters x 2 rows)
  lcd.print("Crossings: 0");
}

void loop() {
  unsigned long currentTime = millis();

  

  int ldrValue = analogRead(ldrPin);

  if (ldrValue > threshold && !aboveThreshold) {
    aboveThreshold = true;
    crossingCount++;
  }
   if (currentTime - startTime <= measurementTime) {
    lcd.setCursor(0, 1);
    lcd.print("Crossings:   "); 
    lcd.setCursor(10, 1);
    lcd.print(crossingCount);
    Serial.print("Crossings: ");
    Serial.println(crossingCount);
  }
  if (currentTime - startTime >= measurementTime) {
    lcd.setCursor(0, 1);
    lcd.print("Crossings:   "); 
    lcd.setCursor(10, 1);
    lcd.print(crossingCount);
    Serial.print("Crossings: ");
    Serial.println(crossingCount);

    crossingCount = 0;
    aboveThreshold = false;
    startTime = currentTime;
  }
}


