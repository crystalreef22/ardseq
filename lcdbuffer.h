#pragma once

#include <Arduino.h>

#define BUFFER_SIZE 128
#define BUFFER_MODULO_BITMASK 127

class hd44780_I2Cexp;

class LCDBuffer {
public:
    LCDBuffer(); // default constructor
    void enqueue(uint16_t data);
    void setCursor(uint8_t col, uint8_t row);
    void writeString(char* data);
    void connect(hd44780_I2Cexp* lcd);
    void dequeue();
private:
    uint16_t commands[BUFFER_SIZE];
    hd44780_I2Cexp* lcd;
};
