int redPin = 3;
int greenPin = 5;
int bluePin = 6;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  
  for (int brightness = 0; brightness <= 255; brightness++) {
    analogWrite(redPin, brightness);
    delay(10); 
  }

  
  for (int brightness = 0; brightness <= 255; brightness++) {
    analogWrite(greenPin, brightness);
    delay(10);
  }

  
  for (int brightness = 0; brightness <= 255; brightness++) {
    analogWrite(bluePin, brightness);
    delay(10);
  }

  
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);

  delay(1000); 
}
