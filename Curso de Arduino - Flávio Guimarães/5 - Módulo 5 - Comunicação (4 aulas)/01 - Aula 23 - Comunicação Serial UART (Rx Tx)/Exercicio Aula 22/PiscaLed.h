#ifndef PushButton_h
#define PushButton_h

#include "Arduino.h"

class PiscaLed {
  public:
    PiscaLed (byte pinLED, int tempoPisca = 1000);
    void loop();
    void play();
    void stop();
  private:
    unsigned long delayPisca;
    bool estadoPisca;
    byte pinLed;
    int tempoLed;
};

#endif