#ifndef HMI_SAFETY_H
#define HMI_SAFETY_H

#include <Arduino.h>
// functie 1: setup
void initHmiSafety();

// functie 2: steering LED's
void update7Leds(int deviation, bool lineVisible, bool lifted);

// functie 3: check if button is pressed
bool buttonPressed();

#endif
