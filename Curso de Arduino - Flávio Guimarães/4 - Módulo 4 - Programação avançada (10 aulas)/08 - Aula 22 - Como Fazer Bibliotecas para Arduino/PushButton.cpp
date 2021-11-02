#include "PushButton.h"

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "Arduino.h">


PushButton::PushButton(byte pinBotao,int tempoDebounce) {
  pinMode(pinBotao, INPUT_PULLUP);
  pinButton = pinBotao;
  tempoButton = tempoDebounce;
}

void PushButton::button_loop() {
  bool estadoBotao = digitalRead(pinButton);
  apertado = false;
  if ((millis() - debounceBotao) > tempoButton){
    if (!estadoBotao && estadoBotaoAnt) {
      apertado = true;
      debounceBotao = millis();
    } 
  }
  estadoBotaoAnt = estadoBotao;
}

bool PushButton::Pressed(){
  return apertado;
}