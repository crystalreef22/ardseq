
constexpr uint8_t GATE_P = 9;
constexpr uint8_t DAC_CS = 10;
#include <SPI.h>

#include <Wire.h>
#include <hd44780.h>                       // main hd44780 header
#include <hd44780ioClass/hd44780_I2Cexp.h> // i2c expander i/o class header
#include <Encoder.h>

constexpr uint8_t ENCODER_CLK= 3;
constexpr uint8_t ENCODER_DT = 4;
constexpr uint8_t ENCODER_BT = 5;
constexpr uint16_t DEBOUNCE_TIME = 50;
constexpr uint16_t HOLD_TIME = 1000;

//Encoder knob(ENCODER_CLK,ENCODER_DT);

hd44780_I2Cexp lcd; // declare lcd object: auto locate & auto config expander chip

#include "lcdbuffer.h"

LCDBuffer lcdbuf; // declare lcd buffer object

constexpr uint8_t LCD_COLS = 20;
constexpr uint8_t LCD_ROWS = 4;

void setup() {
        Serial.begin(9600);

    Serial.println("init\nok?");
    pinMode(DAC_CS, OUTPUT);
    pinMode(GATE_P, OUTPUT);
    //pinMode(ENCODER_BT, INPUT_PULLUP);
    digitalWrite(DAC_CS,HIGH);
    digitalWrite(GATE_P,LOW);
    SPI.begin();
    lcd.begin(LCD_COLS, LCD_ROWS);
    lcd.backlight();
    lcdbuf.connect(&lcd);
    lcdbuf.enqueue('a');
    Serial.println("ok");


}

struct SequenceStep {
    uint8_t note;
    enum GateMode : uint8_t { GATE_OFF, GATE_NORMAL, GATE_TIE };
    GateMode gateMode;
};
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

unsigned int tempo = 200;
uint8_t step = 0;
uint8_t numSteps = 16;
uint8_t gatePercent = 50;
unsigned long tickMillis = 0;

void stepOn();
void stepOff();
void updateEncoder();
void setVoltage(int dacpin, bool channel, bool gain, unsigned int mV);

void loop() {
    static unsigned long currentMillis;

    currentMillis = millis();
    if (currentMillis >= tickMillis) stepOn();

    if (currentMillis >= tickMillis - (150U*gatePercent)/tempo) stepOff();

    // lcdbuf.dequeue();
    // updateEncoder();
}

void stepOn() {
    switch (sequenceSteps[step].gateMode) {
    case SequenceStep::GATE_NORMAL:
    case SequenceStep::GATE_TIE:
        setVoltage(DAC_CS, 0, 1, sequenceSteps[step].note * 1000U/12);
        digitalWrite(GATE_P, HIGH);
        break;
    case SequenceStep::GATE_OFF:
        digitalWrite(GATE_P, LOW);
        break;
    }
    step++; if (step >= numSteps) step = 0;
    tickMillis += 15000/tempo;
    lcdbuf.setCursor(step,3);
    lcdbuf.enqueue((uint16_t)'^');
    lcdbuf.setCursor((step+numSteps-1)%numSteps,3);
    lcdbuf.enqueue((uint16_t)' ');

}
void stepOff() {
    if (sequenceSteps[step].gateMode == SequenceStep::GATE_NORMAL) {
        digitalWrite(GATE_P, LOW);
    }
}

/*void updateEncoder() {
    static int counter;
    short enc = knob.read();
    short steps;
    if (enc > 3 || enc < -3) {
        steps = enc / 4;
        counter += steps;
        Serial.println(counter);                                                                                                                                                                                                                                                                                 
        knob.write(enc - steps * 4);
    }
}*/

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
