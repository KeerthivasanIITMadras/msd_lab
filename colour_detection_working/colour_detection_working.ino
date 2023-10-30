#include <LiquidCrystal.h>
const int rs = 2, en = 3, d4 = 4, d5 = 8, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#include <Servo.h>

Servo myservo_1;
Servo myservo_2;

int ldr1 = 0;
int ldr2 = 0;
int ldr3 = 0;
int d_ldr1 = 0;
int d_ldr2 = 0;
int d_ldr3 = 0;

int r_I = 255;
int g_I = 255;
int b_I = 255;
int maximum = 0;
int inside = 1;

int red = 9;
int green = 10;
int blue = 11;
int i = 1;
int color = 4;
int stop = 0;
int pos;
int cal = 0;
//int color = 0;
int detected_color = -1;

int em = 7;



void setup() {
  Serial.begin(9600);
  myservo_1.attach(5);
  // myservo_1.write(40);
  // myservo_2.attach(6);
  // myservo_2.write(160);
  delay(100);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  // pinMode(em, OUTPUT); //EM

  pinMode(A2, INPUT);
  lcd.begin(16, 2);
}
void ManualCalibrate() {
  while (inside == 1) {
    pos = 90;
    myservo_1.write(pos);
    read_ldr();
    if (inside == 1) {
      if (ldr1 > ldr2 && ldr1 > ldr3) {
        maximum = ldr1;
      } else if (ldr2 > ldr3) {
        maximum = ldr2;
      } else {
        maximum = ldr3;
      }
      Serial.println(r_I);
      Serial.println(g_I);
      Serial.println(b_I);
      if (maximum - ldr1 < 60 && maximum - ldr2 < 60 && maximum - ldr3 < 60) {
        inside = 0;
        Serial.println("DONE");
      }
    }
  }
  //value at white
  d_ldr1 = ldr1;
  d_ldr2 = ldr2;
  d_ldr3 = ldr3;
}


void read_ldr() {
  digitalWrite(red, HIGH);
  delay(150);
  ldr1 = analogRead(A2);
  digitalWrite(red, 0);

  digitalWrite(green, HIGH);
  delay(150);
  ldr2 = analogRead(A2);
  digitalWrite(green, 0);

  digitalWrite(blue, HIGH);
  delay(150);
  ldr3 = analogRead(A2);
  digitalWrite(blue, 0);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("R:");
  lcd.print(ldr1);

  lcd.print(" G:");
  lcd.print(ldr2);

  lcd.setCursor(0, 1);
  lcd.print("B:");
  lcd.print(ldr3);
  lcd.display();
  delay(100);
}

void reach_color(int h) {
  Serial.println("--------------------------------");
  // int pos = 40;
  int in = 0;
  inside = 1;
  int max_dist = 970;

  for (pos = 20; pos <= 180; pos += 5) {  // goes from 0 degrees to 180 degrees
    myservo_1.write(pos);                 // tell servo to go to position in variable 'pos'
    delay(15);                            // waits 15ms for the servo to reach the position
    read_ldr();
    // Serial.println("--------------------------------");
    // // Serial.println(color);
    // // Serial.println(pos);
    // // Serial.println(ldr1); // red
    // // Serial.println(ldr2); // green
    // // Serial.println(ldr3); // blue
    // Serial.print(ldr1);
    // Serial.print(" ");
    // Serial.print(ldr2);
    // Serial.print(" ");
    // Serial.print(ldr3);
    // Serial.print(" ");
    // Serial.println();
    int c = max(max(ldr1, ldr2), ldr3);
    int a = min(min(ldr1, ldr2), ldr3);
    int b = ldr1 + ldr2 + ldr3 - a - b;  //ascending [a,b,c]
    int threshold = 30;
    if (h == 2 && a == ldr3 && abs(ldr1 - d_ldr1) > threshold && abs(ldr2 - d_ldr2) > threshold && c < 950 && b > 800 && c>800) {
      Serial.println("The colour is reached Blue");
      break;
    } 
    if (h == 0 && a == ldr1 && abs(ldr2 - d_ldr2) > threshold && abs(ldr3 - d_ldr3) > threshold && c < 950 && b > 800 && c>800 ) {
      Serial.println("The colour is reached Red");
      break;
    } if (h == 1 && a == ldr2 && abs(ldr1 - d_ldr1) > threshold && abs(ldr3 - d_ldr3) > threshold && c < 950 && b > 800 && c>800 ) {
      Serial.println("The colour is reached Green");
      break;
    }
  }
}
void loop() {
  ManualCalibrate();
  // Serial.println("Pick Up: Please enter 0, 1, 2 for R, G, B respectively");
  int h;
  while (Serial.available() > 0) {  //this while is running twice and in the second run it takes color = 0
    h = Serial.parseInt();
    Serial.println(h);
    reach_color(h);
  }
}