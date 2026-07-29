#pragma once

#include <Arduino.h>

#include <Bounce2.h>

class ButtonManager {
public:
    void begin();
    void scan();
    inline bool isPressed(size_t n) { return buttons[n].isPressed(); }
    inline bool pressed(size_t n) { return buttons[n].pressed(); }
    inline bool released(size_t n) { return buttons[n].released(); }
    inline int8_t getLastPressed() { return lastPressed; }
private:
    Bounce2::Button buttons[10];
    int8_t lastPressed{-1};
};