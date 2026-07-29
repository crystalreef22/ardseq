#pragma once

#include <Arduino.h>

class Sequence {
public:
    Sequence();
    struct SequenceStep {
        uint8_t note;
        enum GateMode : uint8_t { GATE_OFF, GATE_NORMAL, GATE_TIE };
        GateMode gateMode;
    };
private: public:
    SequenceStep sequenceSteps[16] = {
        {0, SequenceStep::GATE_NORMAL},
        {2, SequenceStep::GATE_NORMAL},
        {4, SequenceStep::GATE_NORMAL},
        {5, SequenceStep::GATE_NORMAL},
        {7, SequenceStep::GATE_NORMAL},
        {9, SequenceStep::GATE_NORMAL},
        {11, SequenceStep::GATE_NORMAL},
        {12, SequenceStep::GATE_NORMAL},
        {11, SequenceStep::GATE_NORMAL},
        {9, SequenceStep::GATE_NORMAL},
        {7, SequenceStep::GATE_NORMAL},
        {5, SequenceStep::GATE_NORMAL},
        {4, SequenceStep::GATE_NORMAL},
        {2, SequenceStep::GATE_TIE},
        {0, SequenceStep::GATE_TIE},
        {0, SequenceStep::GATE_OFF}
    };

};