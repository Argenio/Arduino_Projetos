/*
  Curso de Arduino .NET - Flávio Guimarães
  CANAL: Brincando com Ideias - https://www.youtube.com/c/BrincandocomIdeias
  SITE: https://www.brincandocomideias.com/
  Autor:  Argênio Silveira 
  Link:   https://wokwi.com/arduino/projects/313629848901780032
  MODULO: 3 - Módulo 3 - Programação Intermediária (13 aulas)
  SKETCH: 01 - Aula 16 - Programação de Condições IF, ELSE e ELSEIF
*/
#define pinLedVm 10
#define pinLedAm 9
#define PinLedAz 8

#define pinBotaoVm 7
#define pinBotaoAm 6
#define pinBotaoAz 5

void setup() {
  // put your setup code here, to run once:
  pinMode(pinLedVm, OUTPUT);
  pinMode(pinLedAm, OUTPUT);
  pinMode(PinLedAz, OUTPUT);

  pinMode(pinBotaoVm, INPUT_PULLUP);
  pinMode(pinBotaoAm, INPUT_PULLUP);
  pinMode(pinBotaoAz, INPUT_PULLUP);

}

void loop() {

  bool estadoBotaoVm = digitalRead(pinBotaoVm);
  bool estadoBotaoAm = digitalRead(pinBotaoAm);
  bool estadoBotaoAz = digitalRead(pinBotaoAz);

  // Controle do estado dos Botões
  byte estadoLed;
  if (!estadoBotaoVm) estadoLed = 1;
  if (!estadoBotaoAm) estadoLed = 2;
  if (!estadoBotaoAz) estadoLed = 3;
  if((estadoBotaoVm && estadoBotaoAm) && estadoBotaoAz) estadoLed = 4;
  
  /*
  if (!estadoBotaoVm){ // ! nega (ou seja inverte o valor booleano)
    // Efeito 01
    digitalWrite(pinLedVm, HIGH);
    digitalWrite(pinLedAm, LOW);
    digitalWrite(PinLedAz, LOW);
    delay(100);
    digitalWrite(pinLedVm, LOW);
    digitalWrite(pinLedAm, HIGH);
    digitalWrite(PinLedAz, LOW);
    delay(100);
    digitalWrite(pinLedVm, LOW);
    digitalWrite(pinLedAm, LOW);
    digitalWrite(PinLedAz, HIGH);
    delay(100);
  }
  if (!estadoBotaoAm){
    // Efeito 02
    digitalWrite(pinLedVm, LOW);
    digitalWrite(pinLedAm, LOW);
    digitalWrite(PinLedAz, LOW);
    delay(100);
    digitalWrite(pinLedVm, HIGH);
    digitalWrite(pinLedAm, HIGH);
    digitalWrite(PinLedAz, HIGH);
  }
  if (estadoBotaoAz) {
    /* codigo so executa se verdadeiro logo eu posso usar o 
    else como o mesmo estado negação*//*
  } else {  
    // Efeito 03
    digitalWrite(pinLedVm, HIGH);
    digitalWrite(pinLedAm, HIGH);
    digitalWrite(PinLedAz, HIGH);
  } 

  //if((estadoBotaoVm && estadoBotaoAm) && estadoBotaoAz)

  if(estadoBotaoVm || estadoBotaoAm || estadoBotaoAz){
    // Efeito 04
    digitalWrite(pinLedVm, LOW);
    digitalWrite(pinLedAm, LOW);
    digitalWrite(PinLedAz, LOW);
  }
  */
  if(estadoLed == 1){
    // Efeito 01
    digitalWrite(pinLedVm, HIGH);
    digitalWrite(pinLedAm, LOW);
    digitalWrite(PinLedAz, LOW);
    delay(100);
    digitalWrite(pinLedVm, LOW);
    digitalWrite(pinLedAm, HIGH);
    digitalWrite(PinLedAz, LOW);
    delay(100);
    digitalWrite(pinLedVm, LOW);
    digitalWrite(pinLedAm, LOW);
    digitalWrite(PinLedAz, HIGH);
    delay(100);
  } else if(estadoLed == 2){
    // Efeito 02
    digitalWrite(pinLedVm, LOW);
    digitalWrite(pinLedAm, LOW);
    digitalWrite(PinLedAz, LOW);
    delay(100);
    digitalWrite(pinLedVm, HIGH);
    digitalWrite(pinLedAm, HIGH);
    digitalWrite(PinLedAz, HIGH);
  } else if(estadoLed == 3){
    // Efeito 03
    digitalWrite(pinLedVm, HIGH);
    digitalWrite(pinLedAm, HIGH);
    digitalWrite(PinLedAz, HIGH);
  } else {
    // Efeito 04
    digitalWrite(pinLedVm, LOW);
    digitalWrite(pinLedAm, LOW);
    digitalWrite(PinLedAz, LOW);
  }
  /*
  if(estadoLed == 4){
    // Efeito 04
    digitalWrite(pinLedVm, LOW);
    digitalWrite(pinLedAm, LOW);
    digitalWrite(PinLedAz, LOW);
  }
  */
}
