#include <Arduino.h>

#include <Bounce2.h>

#include "buttonmanager.h"
#include "constants.h"


void ButtonManager::begin() {
    for(int i = 0; i < 8; i++) {
        buttons[i].attach(pinmap::buttons::in1+(i%4), INPUT_PULLUP);
        buttons[i].interval(10);
        buttons[i].setPressedState(LOW); 
    }

    buttons[8].attach(pinmap::buttons::shift, INPUT_PULLUP);
    buttons[9].attach(pinmap::buttons::alt, INPUT_PULLUP);
    buttons[8].interval(10);
    buttons[8].setPressedState(LOW); 
    buttons[9].interval(10);
    buttons[9].setPressedState(LOW); 

    pinMode(pinmap::buttons::outA, OUTPUT);
    pinMode(pinmap::buttons::outB, OUTPUT);
}

void ButtonManager::scan() {
    pinMode(pinmap::buttons::outA, OUTPUT);
    digitalWrite(pinmap::buttons::outA, LOW);
    for (int i = 0; i < 4; i++) {
        buttons[i].update();
    }
    digitalWrite(pinmap::buttons::outA, HIGH);
    pinMode(pinmap::buttons::outA, INPUT);
    pinMode(pinmap::buttons::outB, OUTPUT);
    digitalWrite(pinmap::buttons::outB, LOW);
    for (int i = 4; i < 8; i++) {
        buttons[i].update();
    }
    digitalWrite(pinmap::buttons::outB, HIGH);
    pinMode(pinmap::buttons::outB, INPUT);

    for (uint8_t i = 0; i < 8; i++) {
        if (buttons[i].pressed()) {
            lastPressed = i;
            if (buttons[8].isPressed()) lastPressed &= 8;
            if (buttons[9].isPressed()) lastPressed &= 16;
            break;
        }
        lastPressed = -1;
    }

/*
    for (int i = 0; i < 8; i++) {
        Serial.print(buttons[i].isPressed());
    }
    Serial.println();*/
}