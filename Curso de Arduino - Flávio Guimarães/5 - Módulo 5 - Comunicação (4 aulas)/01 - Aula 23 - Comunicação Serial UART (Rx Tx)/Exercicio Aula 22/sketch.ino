/*
  Curso de Arduino .NET - Flávio Guimarães
  CANAL: Brincando com Ideias - https://www.youtube.com/c/BrincandocomIdeias
  SITE: https://www.brincandocomideias.com/
  Autor:  Argênio Silveira 
  Link:   https://wokwi.com/arduino/projects/314243845403443776
  MODULO: Módulo 4 - Programação avançada (10 aulas)
  SKETCH: 01 - Aula 23 - Comunicação Serial UART (Rx Tx) - Exercicio Aula 22
*/
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
#include "PiscaLed.h"

#define pinLedVm 10
#define pinLedAm 9
#define pinLedAz 8
#define pinBotaoVm 7
#define pinBotaoAm 6
#define pinBotaoAz 5

byte contador = 0;

PushButton BotaoVM (pinBotaoVm);
PushButton BotaoAM (pinBotaoAm);
PushButton BotaoAZ (pinBotaoAz);
PiscaLed LedVm (pinLedVm, 1000);
PiscaLed LedAm (pinLedAm, 200);
PiscaLed LedAz (pinLedAz, 3000);

void setup() {
  Serial.begin(9600);
  Serial.println(" ");
}

void loop() {
  LedVm.loop();
  LedAm.loop();
  LedAz.loop();

  BotaoVM.button_loop();
  BotaoAM.button_loop();
  BotaoAZ.button_loop();

  if (BotaoVM.Pressed()) {
    contador++;
    Serial.print("Contador :");
    Serial.println(contador);
  }

  if (BotaoAM.Pressed()) {
    contador--;
    Serial.print("Contador :");
    Serial.println(contador);
  }

  if (BotaoAZ.Pressed()) {
    contador = 0;
    Serial.print("Contador :");
    Serial.println(contador);
  }

  if (contador >= 5) {
    LedVm.play();
  } else {
    LedVm.stop();
  }

  if (contador >= 10) {
    LedAm.play();
  } else {
    LedAm.stop();
  }

  if (contador >= 15) {
    LedAz.play();
  } else {
    LedAz.stop();
  }
}