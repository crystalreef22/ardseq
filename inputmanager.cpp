#include <Arduino.h>

#include <Bounce2.h>

#include "inputmanager.h"
#include "constants.h"


void InputManager::begin() {
    for(int i = 0; i < 8; i++) {
        buttons[i].attach(pinmap::buttons::in1+(i%4), INPUT_PULLUP);
        // buttons[i].interval(10);
        buttons[i].setPressedState(LOW); 
    }

    buttons[8].attach(pinmap::buttons::shift, INPUT_PULLUP);
    buttons[9].attach(pinmap::buttons::alt, INPUT_PULLUP);
    buttons[10].attach(pinmap::buttons::enc_bt, INPUT_PULLUP);
    // buttons[8].interval(10);
    buttons[8].setPressedState(LOW); 
    // buttons[9].interval(10);
    buttons[9].setPressedState(LOW);
    // buttons[10].interval(10);
    buttons[10].setPressedState(LOW);

    pinMode(pinmap::buttons::outA, OUTPUT);
    pinMode(pinmap::buttons::outB, OUTPUT);
}

void InputManager::scan() {
    pinMode(pinmap::buttons::outA, OUTPUT);
    digitalWrite(pinmap::buttons::outA, LOW);
    for (int i = 0; i < 4; i++) {
        buttons[i].update();
    }
    digitalWrite(pinmap::buttons::outA, HIGH);
    pinMode(pinmap::buttons::outA, INPUT);
    pinMode(pinmap::buttons::outB, OUTPUT);
    digitalWrite(pinmap::buttons::outB, LOW);
    for (int i = 4; i < 11; i++) { // scan other buttons too
        buttons[i].update();
    }
    digitalWrite(pinmap::buttons::outB, HIGH);
    pinMode(pinmap::buttons::outB, INPUT);

    lastPressed = -1;
    for (uint8_t i = 0; i < 8; i++) {
        if (buttons[i].pressed()) {
            if (lastPressed != -1) {
                lastPressed = -1; // ghost!!
                break;
            }
            lastPressed = i;
            if (buttons[8].isPressed()) lastPressed |= 8;
            if (buttons[9].isPressed()) lastPressed |= 16;
        }
    }

/*
    for (int i = 0; i < 8; i++) {
        Serial.print(buttons[i].isPressed());
    }
    Serial.println();*/
}


int InputManager::turnsEncoder() {
    int enc = knob.read();
    if (enc > 3 || enc < -3) {
        int steps = enc / 4;
        knob.write(enc - steps * 4);
        return steps;
    }
    return 0;
}