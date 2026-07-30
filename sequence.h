#pragma once

#include <Arduino.h>

class LCDBuffer;

class Sequence {
public:
    Sequence();
    struct Step {
        uint8_t note;
        enum GateMode : uint8_t { GATE_OFF, GATE_NORMAL, GATE_TIE };
        GateMode gateMode;
        void disp3Char(LCDBuffer lcd, uint8_t startCol) const;
    };
    void redrawSteps(LCDBuffer lcd) const;
private: public: // temporarily public for testing
    Step steps[16];

};