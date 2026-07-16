#include <Arduino.h>
#include <Wire.h>

#include "lcdbuffer.h"
#include <hd44780.h>

LCDBuffer::LCDBuffer() {}

void LCDBuffer::sendCommand(uint16_t data) {
    if (full()) {
        flushOne();
        // LCD queue overflow!!
    }
    arr[head] = data;
    head = (head + 1) & LCDBUF_MODULO_BITMASK;
}
void LCDBuffer::setCursor(uint8_t col, uint8_t row) {
    sendCommand(((row | 0x80) << 8)|col);
}

void LCDBuffer::connect(hd44780* lcd) {
    this->lcd = lcd;
}
void LCDBuffer::flushOne() {
    if (!empty()) {
        switch (arr[tail] >> 8) {
        case 0x00:
            lcd->write((char)arr[tail]);
            break;
        case 0x80 ... 0x8f:
            lcd->setCursor((uint8_t)arr[tail], (arr[tail]>>8) - 0x80);
            break;
        case CLEAR:         lcd->clear(); break;
        case HOME:          lcd->home(); break;
        case CURSORON:      lcd->cursor(); break;
        case CURSOROFF:     lcd->noCursor(); break;
        case BLINKON:       lcd->blink(); break;
        case BLINKOFF:      lcd->noBlink(); break;
        case DISPLAYON:     lcd->display(); break;
        case DISPLAYOFF:    lcd->noDisplay(); break;
        case BACKLIGHTON:   lcd->backlight(); break;
        case BACKLIGHTOFF:  lcd->noBacklight(); break;
        }
        tail = (tail + 1) & LCDBUF_MODULO_BITMASK;
    }
}

void LCDBuffer::flush() {
    while (!empty()) {
        flushOne();
    }
}