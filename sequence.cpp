#include "sequence.h"

#include <Arduino.h>    

Sequence::Sequence()
    : sequenceSteps {
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
    }
{}