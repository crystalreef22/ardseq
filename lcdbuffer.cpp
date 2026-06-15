#include <Arduino.h>
#include <Wire.h>

#include "lcdbuffer.h"
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h> // i2c expander i/o class header


LCDBuffer::LCDBuffer() {}

void LCDBuffer::enqueue(uint16_t data) {
    lcd->write((char)data);
}
void LCDBuffer::setCursor(uint8_t col, uint8_t row) {
    lcd->setCursor(col, row);
}
void LCDBuffer::writeString(char* data) {

}
void LCDBuffer::connect(hd44780_I2Cexp* lcd) {
    this->lcd = lcd;
}
void LCDBuffer::dequeue() {
    
}
