#include <LiquidCrystal.h>

// Initialize LCD
LiquidCrystal lcd(2,3,4,8,12,13);

// Define LDR pins
int LDRPin = A2;


// Define LED pins
int redLEDPin = 9;
int greenLEDPin = 10;
int blueLEDPin = 11;

void setup() {
  // Initialize LCD
  lcd.begin(16, 2);

  // Set LED pins as OUTPUT
  pinMode(redLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);

  // Start the serial communication
  Serial.begin(9600);
}

// Function to manually calibrate
void manualCalibrate() {
  // Initialize variables to store reflected intensities
  int redIntensity = 0;
  int greenIntensity = 0;
  int blueIntensity = 0;

  // Shine red color
  analogWrite(redLEDPin, 255);
  delay(100);
  redIntensity = analogRead(LDRPin);
  analogWrite(redLEDPin, 0);

  // Shine green color
  analogWrite(greenLEDPin, 255);
  delay(100);
  greenIntensity = analogRead(LDRPin);
  analogWrite(greenLEDPin, 0);

  // Shine blue color
  analogWrite(blueLEDPin, 255);
  delay(100);
  blueIntensity = analogRead(LDRPin);
  analogWrite(blueLEDPin, 0);

  // Print the read values on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("R:");
  lcd.print(redIntensity);
  lcd.setCursor(0, 1);
  lcd.print("G:");
  lcd.print(greenIntensity);
  lcd.setCursor(8, 0);
  lcd.print("B:");
  lcd.print(blueIntensity);

  // Find the maximum intensity
  int maxIntensity = max(redIntensity, max(greenIntensity, blueIntensity));

  // Adjust the potentiometers to equalize the intensities (implement this part)

  // Give a small delay
  delay(500);  // Adjust the delay duration as needed
}

void loop() {
  // Check if the user wants to stop and calibrate
  // if (Serial.available() > 0) {
  //   int userInput = Serial.parseInt();
  //   if (userInput == 1) {
  //     // Exit the loop after calibration
      analogWrite(redLEDPin, 0);
      analogWrite(greenLEDPin, 0);
      analogWrite(blueLEDPin, 0);

      // Perform the manual calibration
      manualCalibrate();
      
    
    }
  // }
// }
