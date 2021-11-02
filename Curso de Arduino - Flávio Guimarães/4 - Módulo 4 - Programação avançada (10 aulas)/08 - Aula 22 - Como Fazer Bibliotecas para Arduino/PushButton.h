#ifndef PushButton_h
#define PushButton_h

#include "Arduino.h"

class PushButton {
  public:
    PushButton(byte pinBotao,int tempoDebounce = 200);
    void button_loop();
    bool Pressed();
  private:
    unsigned long debounceBotao;
    bool estadoBotaoAnt = HIGH;
    bool apertado = false;
    byte pinButton;
    int tempoButton;
};

#endif