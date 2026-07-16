#pragma once

#include <Arduino.h>

#include <Bounce2.h>

Bounce2::Button buttons[8];

void setup() {
  for(int i = 0; i < 8; i++) {
    buttons[i].attach(2+(i%4), INPUT_PULLUP);
    buttons[i].interval(10);
    buttons[i].setPressedState(HIGH); 
  }

  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  for (int i = 0; i < 4; i++) {
    buttons[i].update();
  }

  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  for (int i = 4; i < 8; i++) {
    buttons[i].update();
  }

for (int i = 0; i < 8; i++) {
  Serial.print(buttons[i].pressed(), '\r');
}

