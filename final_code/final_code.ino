#include <LiquidCrystal.h>
const int rs = 2, en = 3, d4 = 4, d5 = 8, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#include <Servo.h>

Servo myservo_1;// sweep motor
Servo myservo_2;// arm motor

bool inputRecievedPick = false;
int ldr1 = 0;// ldr check for red
int ldr2 = 0;// ldr check for green
int ldr3 = 0;// ldr check for blue
int d_ldr1 = 300;// default values for ldrs
int d_ldr2 = 300;
int d_ldr3 = 300;

int r_I = 255;// high values for all three lights
int g_I = 255;
int b_I = 255;
int maximum = 0;
int inside = 1;

int red = 9; // pin for R,G,B
int green = 10;
int blue = 11;
int i = 1; 
int color = 4;
int stop = 0;
int pos;
int cal = 0;
int detected_color = -1;
int em = 7;



void setup() {
  Serial.begin(9600);
  myservo_1.attach(5);
  myservo_1.write(40);
  myservo_2.attach(6);
  myservo_2.write(160);
  delay(100);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(em, OUTPUT); 

  pinMode(A2, INPUT);
  lcd.begin(16, 2);
}
void attach() {  // attaching the object to electromagnet
  myservo_2.write(180);
  int j=0;
  for (; pos >= 0; pos -= 1) {
    delay(150);
    if (pos == 0){
       delay(4000);
    }
    int s1 = analogRead(A1);
    Serial.println(s1);
    if (s1 > 200) {
      j=1;
      break;
    }
    myservo_2.write(pos);
    // digitalWrite(7,j);
  }
  Serial.println(j);
  if (j == 1){
    digitalWrite(em,HIGH);
    delay(1000);
  }
  else {
    Serial.println("No object detected.");
  }
  myservo_2.write(180);
}

void detach(){
  int j=0;
  myservo_2.write(0);
  delay(3000);
  digitalWrite(7,j);
  delay(3000);
  for(int i=0;i<=180;i+=10)
  {
      myservo_2.write(i);
  }
}

void read_ldr(){  // reading values from ldr
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

void ManualCalibrate() {
  while (inside == 1) {
    pos = 90;
    Serial.println("Manual start");
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
        Serial.println("Manual Calibration is Done");
      }
    }
  }
  //value at white
  d_ldr1 = ldr1;
  d_ldr2 = ldr2;
  d_ldr3 = ldr3;
}

void AutoCalibrate() {
  Serial.println("Autocal start");
  pos=90;
  myservo_1.write(pos);
  Serial.println(pos);
  delay(1000);
  myservo_1.detach();
  myservo_2.detach();
  int i =1;

  while (inside == 1) {
    i+=1;
    analogWrite(red, r_I);
    delay(150);
    ldr1 = analogRead(A2);
    analogWrite(red, 0);
  

    analogWrite(green, g_I);
    delay(150);
    ldr2 = analogRead(A2);
    analogWrite(green, 0);

    analogWrite(blue, b_I);
    delay(150);
    ldr3 = analogRead(A2);
    analogWrite(blue, 0);
    Serial.println(i);
    Serial.println(ldr1);
    Serial.println(ldr2);


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

    if (inside == 1) {
      if (ldr1 > ldr2 && ldr1 > ldr3) {
        maximum = ldr1;
      }
      else if (ldr2 > ldr3) {
        maximum = ldr2;
      }
      else {
        maximum = ldr3;
      }

      if (maximum - ldr1 > 60) {
        r_I = r_I - 5;
      }
      if (maximum - ldr2 > 60) {
        g_I = g_I - 5;
      }
      if (maximum - ldr3 > 60) {
        b_I = b_I - 5;
      }

      Serial.println(r_I);
      Serial.println(g_I);
      Serial.println(b_I);
      if (maximum - ldr1 < 60 && maximum - ldr2 < 60 && maximum - ldr3 < 60) {
        inside = 0;
        d_ldr1 = ldr1;
        d_ldr2 = ldr2;
        d_ldr3 = ldr3;
        Serial.println("Auto Callibration is Done");
      }
    }
  }
  myservo_1.attach(5);
  myservo_2.attach(6);
}

void reach_color(int h) {
  Serial.println("--------------------------------");
  //int pos = 40;
  int in = 0;
  int max_dist = 970;

  for (pos = 60; pos <= 180; pos += 5) {  // goes from 0 degrees to 180 degrees
    myservo_1.write(pos);                 // tell servo to go to position in variable 'pos'
    read_ldr();
    delay(500); 
    int c = max(max(ldr1, ldr2), ldr3);
    int a = min(min(ldr1, ldr2), ldr3);
    int b = ldr1 + ldr2 + ldr3 - a - c;  //ascending [a,b,c]
    int threshold = 150;
    
    if ( a == ldr1 && abs(ldr2 - d_ldr2) > threshold && abs(ldr3 - d_ldr3) > threshold && c < 990 && b > 800 && c > 800) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Red");
      if (h==0){
       Serial.println("The colour is reached Red");
       in += 1;
       if (in == 2) {
          inside = 1;
          break;
      } 
     }
    }
    if (a == ldr2 && abs(ldr1 - d_ldr1) > threshold && abs(ldr3 - d_ldr3) > threshold && c < 990 && b > 800 && c > 800) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Green");
      if (h==1){
        Serial.println("The colour is reached Green");
        in += 1;
        if (in == 2) {
          inside = 1;
          break;
      }
     }
    }
    if (a == ldr3 && abs(ldr1 - d_ldr1) > threshold && abs(ldr2 - d_ldr2) > threshold && c < 990 && b > 800 && c > 800) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Blue");
      if (h==2){
        Serial.println("The colour is reached Blue");
        in += 1;
        if (in == 2) {
          inside = 1;
          break;
       }
      }
    }
  }
}
void loop() {
  Serial.println("Please enter 0 for Manual Calibration and 1 for Auto Calibration");
  while (Serial.available() == 0) {}
  if (Serial.available() > 0) {
    cal = Serial.parseInt();
    Serial.println(cal);
    if (cal == 0) {
      Serial.println("Starting Manual Calibration ");
      ManualCalibrate();
    }
    else if (cal == 1) {
      Serial.println("Start Auto Calibration");
      AutoCalibrate();
    }
  }
  Serial.println("Pick Up: Please enter 0, 1, 2 for R, G, B respectively");
  int flow = 0;
  int choice = 5;
  delay(10000);
  if (!inputRecievedPick){
  
    if (Serial.available() > 0) {
      choice = Serial.parseInt();
      Serial.print("Received input: ");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Received input: ");
      lcd.print(choice);
      Serial.println(choice);
      reach_color(choice);
      attach();
      

      Serial.println("Drop location: Please enter 0, 1, 2 for R, G, B respectively");
      // delay(100000);
      int choice_2 = 5;

      if (Serial.available()==0){}
      delay(10000);
      if (Serial.available() > 0) {
        choice_2 = Serial.parseInt();
        Serial.print("Received input: ");
        Serial.println(choice_2);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Received input: ");
        lcd.print(choice_2);
        reach_color(choice_2);
        detach();
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Thank you");

        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Presented by Group2");
        
      }
    }
  }
}