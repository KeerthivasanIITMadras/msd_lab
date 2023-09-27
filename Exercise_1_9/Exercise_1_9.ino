/*
  Fade

  This example shows how to fade an LED on pin 9 using the analogWrite()
  function.

  The analogWrite() function uses PWM, so if you want to change the pin you're
  using, be sure to use another PWM capable pin. On most Arduino, the PWM pins
  are identified with a "~" sign, like ~3, ~5, ~6, ~9, ~10 and ~11.

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Fade
*/

int led = 3;         // the PWM pin the LED is attached to // how many points to fade the LED by
const int pin = A2;

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  pinMode(led, OUTPUT);
  pinMode(pin,INPUT);
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // set the brightness of pin 9:'
  int potvalue = analogRead(pin);
  //Serial.println(potvalue);
  potvalue = map(potvalue,0,1023,0,255);
  Serial.println(potvalue);
  analogWrite(led, potvalue);

  // change the brightness for next time through the loop:
  
  // wait for 30 milliseconds to see the dimming effect
  delay(100);
}