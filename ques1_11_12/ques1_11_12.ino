#include <LiquidCrystal.h>
const int rs = 2, en = 3, d4 = 4, d5 = 8, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
  pinMode(A3, INPUT);
  Serial.begin(9600);
  lcd.begin(16,2);
}

void loop() {
  int ldr;
  ldr = analogRead(A3);
  Serial.println("LDR value:");
  Serial.println(ldr);
  lcd.setCursor(0, 0);
  lcd.print("LDR Value");
  lcd.setCursor(0, 1);
  lcd.print(ldr);
}
