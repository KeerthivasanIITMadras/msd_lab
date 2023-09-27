const int button_7 = 7;
const int LED_PIN_11 = 11;

const int button_8 = 8;
const int LED_PIN_12 = 12;

const int button_9 = 9;
const int LED_PIN_13 = 13;

void setup(){
    pinMode(button_7, INPUT_PULLUP );
    pinMode( LED_PIN_11, OUTPUT );

    pinMode(button_8, INPUT_PULLUP );
    pinMode( LED_PIN_12, OUTPUT );

    pinMode(button_9, INPUT_PULLUP );
    pinMode( LED_PIN_13, OUTPUT );
    Serial.begin( 9600 );
}

void loop(){
    int value_7;
    int value_8;
    int value_9;
    
    value_7 = digitalRead(button_7);
    value_8 = digitalRead(button_8);
    value_9 = digitalRead(button_9);

    if ( value_7 == HIGH ){
        digitalWrite( LED_PIN_11, LOW );
    }else{
        digitalWrite( LED_PIN_11, HIGH );
    }

    if ( value_8 == HIGH ){
        digitalWrite( LED_PIN_12, LOW );
    }else{
        digitalWrite( LED_PIN_12, HIGH );
    }
    if ( value_9 == HIGH ){
        digitalWrite( LED_PIN_13, LOW );
    }else{
        digitalWrite( LED_PIN_13, HIGH );
    }

    delay( 1000 );
}