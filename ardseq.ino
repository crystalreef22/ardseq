#include "constants.h"

#include <SPI.h>

#include <Wire.h>
#include <hd44780.h>                       // main hd44780 header
#include <hd44780ioClass/hd44780_I2Cexp.h> // i2c expander i/o class header

#include "inputmanager.h"
#include "sequence.h"
InputManager inputManager;
Sequence sequence;

hd44780_I2Cexp lcd; // declare lcd object: auto locate & auto config expander chip

#include "lcdbuffer.h"

LCDBuffer lcdbuf; // declare lcd buffer object

constexpr uint8_t LCD_COLS = 20;
constexpr uint8_t LCD_ROWS = 4;

void setup() {
    Serial.begin(9600);

    pinMode(pinmap::dac_cs, OUTPUT);
    pinMode(pinmap::gate, OUTPUT);
    digitalWrite(pinmap::dac_cs,HIGH);
    digitalWrite(pinmap::gate,LOW);
    SPI.begin();
    lcd.begin(LCD_COLS, LCD_ROWS);
    lcd.backlight();
    lcd.setCursor(0,0);
    lcdbuf.connect(&lcd);
    lcdbuf.print(F("ardseq"));
    lcdbuf.flush();
    Serial.print("start");
}


unsigned int tempo = 200;
uint8_t step = 0;
uint8_t numSteps = 16;
uint8_t gatePercent = 50;
unsigned long tickMillis = 0;

void stepOn();
void stepOff();
void setVoltage(int dacpin, bool channel, bool gain, unsigned int mV);

void loop() {
    static unsigned long currentMillis;

    currentMillis = millis();
    if (currentMillis >= tickMillis) stepOn();

    if (currentMillis >= tickMillis - (150U*gatePercent)/tempo) stepOff();

    lcdbuf.flushOne();
}

void stepOn() {
    switch (sequence.sequenceSteps[step].gateMode) {
    case Sequence::SequenceStep::GATE_NORMAL:
    case Sequence::SequenceStep::GATE_TIE:
        setVoltage(pinmap::dac_cs, 0, 1, sequence.sequenceSteps[step].note * 1000U/12);
        digitalWrite(pinmap::gate, HIGH);
        break;
    case Sequence::SequenceStep::GATE_OFF:
        digitalWrite(pinmap::gate, LOW);
        break;
    }
    step++; if (step >= numSteps) step = 0;
    tickMillis += 15000/tempo;
    lcdbuf.setCursor(step,3);
    lcdbuf.write('^');
    lcdbuf.setCursor((step+numSteps-1)%numSteps,3);
    lcdbuf.write(' ');
}
void stepOff() {
    if (sequence.sequenceSteps[step].gateMode == Sequence::SequenceStep::GATE_NORMAL) {
        digitalWrite(pinmap::gate, LOW);
    }
}


void setVoltage(int dacpin, bool channel, bool gain, unsigned int mV) {
    unsigned int command = channel ? 0x9000 : 0x1000;

    command |= gain ? 0x0000 : 0x2000;
    command |= (mV & 0x0FFF);
    
    SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));
    digitalWrite(dacpin,LOW);
    SPI.transfer(command>>8);
    SPI.transfer(command&0xFF);
    digitalWrite(dacpin,HIGH);
    SPI.endTransaction();
}
