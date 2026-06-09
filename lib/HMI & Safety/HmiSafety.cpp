#include "HmiSafety.h"

// pin definitions
const int deadmanPin = 0;
const int ledPins[] = {1, 2, 3, 4, 5, 6, 7};
const int numLeds = 7;

// function 1: starting
void initHmiSafety(){
    pinMode(deadmanPin, INPUT_PULLUP);
    
    for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

// function 2: steering LED's
void update7Leds(int deviation, bool lineVisible, bool lifted){
    // reset all LED's
    for (int i = 0; i < numLeds; i++) {
        digitalWrite(ledPins[i], LOW);
    }
    
    // button not pressed -> all LED's off
    if (!buttonPressed()){
        return;
    }
    
    // device lifted -> all LED's on
    if (lifted){
        for (int i = 0; i < numLeds; i++){
            digitalWrite(ledPins[i], HIGH);
        }
        return;
    }

    // line lost -> outer LED's on
    if (!lineVisible){
        digitalWrite(ledPins[0], HIGH);
        digitalWrite(ledPins[6], HIGH);
        return; 
    }

    // direct LED indication
    int activeLedIndex = deviation;

    // safety boundaries
    if (activeLedIndex < 0) activeLedIndex = 0;
    if (activeLedIndex > 6) activeLedIndex = 6;
    
    // turn on specific LED
    digitalWrite(ledPins[activeLedIndex], HIGH);
}

// function 3: button status
// LOW = button is pressed.
bool buttonPressed(){
    return (digitalRead(deadmanPin) == LOW);
}
