#include <Arduino.h>

#include <Bounce2.h>

#include "buttonmanager.h"


void ButtonManager::begin() {
    for(int i = 0; i < 8; i++) {
        buttons[i].attach(BM_IN1+(i%4), INPUT_PULLUP);
        buttons[i].interval(10);
        buttons[i].setPressedState(LOW); 
    }

    buttons[8].attach(BM_SHIFT, INPUT_PULLUP);
    buttons[9].attach(BM_ALT, INPUT_PULLUP);
    buttons[8].interval(10);
    buttons[8].setPressedState(LOW); 
    buttons[9].interval(10);
    buttons[9].setPressedState(LOW); 

    pinMode(BM_OUTA, OUTPUT);
    pinMode(BM_OUTB, OUTPUT);
}

void ButtonManager::scan() {
    pinMode(BM_OUTA, OUTPUT);
    digitalWrite(BM_OUTA, LOW);
    for (int i = 0; i < 4; i++) {
        buttons[i].update();
    }
    digitalWrite(BM_OUTA, HIGH);
    pinMode(BM_OUTA, INPUT);
    pinMode(BM_OUTB, OUTPUT);
    digitalWrite(BM_OUTB, LOW);
    for (int i = 4; i < 8; i++) {
        buttons[i].update();
    }
    digitalWrite(BM_OUTB, HIGH);
    pinMode(BM_OUTB, INPUT);

    for (uint8_t i = 0; i < 8; i++) {
        if (buttons[i].pressed()) {
            lastPressed = i;
            if (buttons[8].pressed()) lastPressed &= 8;
            if (buttons[9].pressed()) lastPressed &= 16;
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