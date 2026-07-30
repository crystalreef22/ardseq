#include "sequence.h"

#include <Arduino.h>
#include "lcdbuffer.h"

Sequence::Sequence()
    : steps {
        {0, Step::GATE_NORMAL},
        {2, Step::GATE_NORMAL},
        {4, Step::GATE_NORMAL},
        {5, Step::GATE_NORMAL},
        {7, Step::GATE_NORMAL},
        {9, Step::GATE_NORMAL},
        {11, Step::GATE_NORMAL},
        {12, Step::GATE_NORMAL},
        {11, Step::GATE_NORMAL},
        {9, Step::GATE_NORMAL},
        {7, Step::GATE_NORMAL},
        {5, Step::GATE_NORMAL},
        {4, Step::GATE_NORMAL},
        {2, Step::GATE_TIE},
        {0, Step::GATE_TIE},
        {0, Step::GATE_OFF}
    }
{}

void Sequence::Step::disp3Char(LCDBuffer& lcd, uint8_t startCol) const {
    auto num = note % 12;
    auto octave = note / 12; // c5 is middle c
    
    lcd.setCursor(startCol, 0);
    lcd.write('&');
    lcd.write("CCDDEFGGAABB"[num]);
    lcd.setCursor(startCol, 1);
    lcd.write(" # #   # # #"[num]);
    lcd.setCursor(startCol, 2);
    lcd.print(octave);
}

void Sequence::redrawSteps(LCDBuffer& lcd) const {
    for (uint8_t i = 0; i < 16; i++) {
        steps[i].disp3Char(lcd, i);
    }
}