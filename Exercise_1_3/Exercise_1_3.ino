const int button = 7;
const int LED_PIN = 13;

void setup(){
    pinMode(button, INPUT_PULLUP );
    pinMode( LED_PIN, OUTPUT );
    Serial.begin( 9600 );
}

void loop(){
    int value;
    
    value = digitalRead(button);

    if ( value == HIGH ){
        digitalWrite( LED_PIN, LOW );
    }else{
        digitalWrite( LED_PIN, HIGH );
    }
    Serial.println( value );

    delay( 1000 );
}