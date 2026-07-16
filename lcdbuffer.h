#pragma once

#include <Arduino.h>
#include <Print.h>

constexpr uint8_t LCDBUF_SIZE = 128;
constexpr uint8_t LCDBUF_MODULO_BITMASK = 127;

class hd44780;

class LCDBuffer : public Print {
public:
    LCDBuffer(); // default constructor
    void sendCommand(uint16_t data);
    inline size_t write(uint8_t data) override {sendCommand((uint16_t)data);return true;};
    void setCursor(uint8_t col, uint8_t row);
    void connect(hd44780* lcd);
    void flushOne();
    void flush();

    enum COMMAND_UPPERBYTE : uint8_t {
        CLEAR = 0x01,
        HOME,
        CURSORON,
        CURSOROFF,
        BLINKON,
        BLINKOFF,
        DISPLAYON,
        DISPLAYOFF,
        BACKLIGHTON,
        BACKLIGHTOFF
    }; // max is 127, 128 (0x80) is move cursor
private:
    uint16_t arr[LCDBUF_SIZE];
    hd44780* lcd;
    uint8_t head;
    uint8_t tail;
    inline bool full() {
        return ((tail - head) & LCDBUF_MODULO_BITMASK) == 1;
    }
    inline int availableForWrite() override {return !full();}
    inline bool empty() {
        return tail == head;
    }
};
