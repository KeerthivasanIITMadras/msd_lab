#include <LiquidCrystal.h>
const int rs = 2, en = 3, d4 = 4, d5 = 8, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
  lcd.begin(16,2);
}
void loop(){
  lcd.setCursor(0, 0);
  lcd.print("Presented by");
  lcd.setCursor(0, 1);
  lcd.print("Group 2 :)");
}
