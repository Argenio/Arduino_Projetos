/*
  Curso de Arduino .NET - Flávio Guimarães
  CANAL: Brincando com Ideias - https://www.youtube.com/c/BrincandocomIdeias
  SITE: https://www.brincandocomideias.com/
  Autor:  Argênio Silveira 
  Link:   https://wokwi.com/arduino/projects/313692398154678850
  MODULO: 3 - Módulo 3 - Programação Intermediária (13 aulas)
  SKETCH: 07 - Aula 17 - Operadores Lógicos e Comandos SWITCH, CASE e DEFAULT
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
  if (!estadoBotaoVm ||!estadoBotaoAm ) {
    if (!estadoBotaoVm && !estadoBotaoAm ) {
      estadoLed = 4;
    }else {
      estadoLed = 1;
    }    
  }
  if (!estadoBotaoAz) estadoLed = 2;
  if ((estadoBotaoVm && estadoBotaoAm) && estadoBotaoAz) estadoLed = 4;

  switch (estadoLed){
    case 1:{
      // Efeito 01
      digitalWrite(pinLedVm, HIGH);
      digitalWrite(pinLedAm, LOW);
      digitalWrite(PinLedAz, LOW);
      delay(200);
      digitalWrite(pinLedVm, LOW);
      digitalWrite(pinLedAm, HIGH);
      digitalWrite(PinLedAz, LOW);
      delay(200);
      digitalWrite(pinLedVm, LOW);
      digitalWrite(pinLedAm, LOW);
      digitalWrite(PinLedAz, HIGH);
      delay(200);
      break;
    }
    case 2: {
      // Efeito 02
      digitalWrite(pinLedVm, LOW);
      digitalWrite(pinLedAm, LOW);
      digitalWrite(PinLedAz, LOW);
      delay(200);
      digitalWrite(pinLedVm, HIGH);
      digitalWrite(pinLedAm, HIGH);
      digitalWrite(PinLedAz, HIGH);
      delay(200);
      digitalWrite(pinLedVm, LOW);
      digitalWrite(pinLedAm, LOW);
      digitalWrite(PinLedAz, LOW); 
      break;
    }
    case 3: {
      // Efeito 03
      digitalWrite(pinLedVm, HIGH);
      digitalWrite(pinLedAm, HIGH);
      digitalWrite(PinLedAz, HIGH);
      break;
    }
    default : {
      // Efeito 04
      digitalWrite(pinLedVm, LOW);
      digitalWrite(pinLedAm, LOW);
      digitalWrite(PinLedAz, LOW);
    }
  }
}
