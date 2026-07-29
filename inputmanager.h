#pragma once

#include <Arduino.h>

#include <Bounce2.h>

#include <Encoder.h>

#include "constants.h"

class InputManager {
public:
    void begin();
    void scan();
    int turnsEncoder();
    inline bool isPressed(size_t n) { return buttons[n].isPressed(); }
    inline bool pressed(size_t n) { return buttons[n].pressed(); }
    inline bool released(size_t n) { return buttons[n].released(); }
    inline int8_t getLastPressed() { return lastPressed; }

    // could be enum but oh well
    static constexpr uint8_t shiftId    = 9;
    static constexpr uint8_t altId    = 10;
    static constexpr uint8_t selId    = 11;
private:
    Bounce2::Button buttons[11];
    Encoder knob{pinmap::enc_1,pinmap::enc_2};
    int8_t lastPressed{-1};
};