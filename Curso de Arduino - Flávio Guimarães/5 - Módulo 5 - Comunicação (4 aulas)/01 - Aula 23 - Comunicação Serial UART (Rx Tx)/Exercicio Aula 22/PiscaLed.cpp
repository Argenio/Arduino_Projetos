#include "PiscaLed.h"

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "Arduino.h">

PiscaLed::PiscaLed (byte pinLED, int tempoPisca){
  pinMode(pinLED, OUTPUT);
  pinLed = pinLED;
  tempoLed = tempoPisca;
  estadoPisca = false;
}
void PiscaLed::loop() {
  if (estadoPisca) {
    if ((millis() - delayPisca) < tempoLed) {
      digitalWrite(pinLed, LOW);
    } else if ((millis() - delayPisca) < (tempoLed * 2) ){
      digitalWrite(pinLed, HIGH);
    } else {
      delayPisca = millis();
    }
  } else {
    digitalWrite(pinLed, LOW);
  }
}
void PiscaLed::play() {
  estadoPisca = true;
  //delayPisca = millis(); // Se deicho ativado como na aula o codigo não funciona
}
void PiscaLed::stop () {
  estadoPisca = false;
  digitalWrite(pinLed, LOW);
}