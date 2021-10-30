/*
  Curso de Arduino .NET - Flávio Guimarães
  CANAL: Brincando com Ideias - https://www.youtube.com/c/BrincandocomIdeias
  SITE: https://www.brincandocomideias.com/
  Autor:  Argênio Silveira 
  Link:   https://wokwi.com/arduino/projects/313810224793256513
  MODULO: 3 - Módulo 3 - Programação Intermediária (13 aulas)
  SKETCH: 10 - Aula 19 - Controle de Repetições - WHILE e FOR - Exercicio Aula 18
*/
#define pinLedVm 10
#define pinLedAm 9
#define PinLedAz 8
#define pinBotaoVm 7

#define deboucingTempo 40

byte estadoLed = 4;

bool estadoAntBotaoVm = HIGH;
unsigned long deboucingBotaoVm;

void setup() {
  pinMode(pinLedVm, OUTPUT);
  pinMode(pinLedAm, OUTPUT);
  pinMode(PinLedAz, OUTPUT);

  pinMode(pinBotaoVm, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {

  bool estadoBotaoVm = digitalRead(pinBotaoVm);
  
  if ( (millis() - deboucingBotaoVm) > deboucingTempo) {
    if (!estadoBotaoVm && estadoAntBotaoVm ) {
      estadoLed++;
      if (estadoLed > 3 ){
        estadoLed = 1;
      }    
      deboucingBotaoVm = millis();
    }
  }
  
  Serial.print(estadoLed);
  Serial.println(estadoBotaoVm);
  switch (estadoLed) {
    case 1 : {
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
    case 2 : {
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
      delay(200);
      digitalWrite(pinLedVm, HIGH);
      digitalWrite(pinLedAm, HIGH);
      digitalWrite(PinLedAz, HIGH);
      delay(200);
    }
    case 4 :{
      // Efeito 03 - Funciona apenas quando liga
      digitalWrite(pinLedVm, HIGH);
      digitalWrite(pinLedAm, HIGH);
      digitalWrite(PinLedAz, HIGH);
    }
    default : {
      // Efeito 04
      digitalWrite(pinLedVm, LOW);
      digitalWrite(pinLedAm, LOW);
      digitalWrite(PinLedAz, LOW);
    }
  }
  estadoAntBotaoVm = estadoBotaoVm;
}
