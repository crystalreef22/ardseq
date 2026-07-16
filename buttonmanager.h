#pragma once

#include <Arduino.h>

#include <Bounce2.h>

constexpr uint8_t BM_IN1   = A0;
constexpr uint8_t BM_OUTA  = 5 ;
constexpr uint8_t BM_OUTB  = 6 ;
constexpr uint8_t BM_SHIFT = 7 ;
constexpr uint8_t BM_ALT   = 8 ;

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