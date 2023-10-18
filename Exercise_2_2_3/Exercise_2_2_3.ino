 // IR Sensor with Arduino
// Techatronic.com  
 void setup()  
 {  
 Serial.begin(9600); // sensor baud rate  
 pinMode(12,OUTPUT);  // LED  
 }  
 void loop()  
 {  
 int s1=analogRead(A2); //ANALOG PIN FOR SENSOR  
 Serial.println(s1);   // see the value in serial monitor in Arduino IDE  
 delay(100);  
 if(s1>700 )  
 {  
 digitalWrite(12,HIGH);  // LED ON  
 }  
 else  
 {  
 digitalWrite(12,LOW);  // LED OFF  
 }  
 }  