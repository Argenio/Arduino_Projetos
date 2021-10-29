 /*
  Curso de Arduino .NET - Flávio Guimarães
  CANAL: Brincando com Ideias - https://www.youtube.com/c/BrincandocomIdeias
  SITE: https://www.brincandocomideias.com/
  Autor:  Argênio Silveira 
  Link:   https://wokwi.com/arduino/projects/313785925601591874
  MODULO: 3 - Módulo 3 - Programação Intermediária (13 aulas)
  SKETCH: 08 - Aula 18 - Efeito Bouncing - O que é e como resolver
*/
#define pinLedVm 10
#define pinLedAm 9
#define pinLedAz 8

#define pinBotaoVm 7
#define pinBotaoAm 6
#define pinBotaoAz 5

#define debouncingTempo 40 // atraso no código "TEMPO"

byte contador = 0;
// Começa em HIGH porque estamos usando INPUT_PULLUP
bool estadoAntBotVm = HIGH;
bool estadoAntBotAm = HIGH;
bool estadoAntBotAz = HIGH;

// Debouncing usando Variavel de Tempo
unsigned long debouncingBotVm;
unsigned long debouncingBotAm;
unsigned long debouncingBotAz;


void setup() {
  pinMode(pinLedVm, OUTPUT);
  pinMode(pinLedAm, OUTPUT);
  pinMode(pinLedAz, OUTPUT);

  pinMode(pinBotaoVm, INPUT_PULLUP);
  pinMode(pinBotaoAm, INPUT_PULLUP);
  pinMode(pinBotaoAz, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  bool estadoBotaoVm = digitalRead(pinBotaoVm);
  bool estadoBotaoAm = digitalRead(pinBotaoAm);
  bool estadoBotaoAz = digitalRead(pinBotaoAz);

  /* PROBLEMA:
  Quando trabalhamos com um circuito que envolve chaves mecânicas,
  tem-se o surgimento de um efeito conhecido como “bouncing”.
  
  Basicamente isto apresenta-se como um pequeno problema em nosso circuito,
  já que esse tipo de efeito pode indicar equivocadamente,
  que ocorreram diversos acionamentos em um pequeno intervalo de tempo.
  */
  /* SOLUÇÃO 1:
  é utilizar um pequeno atraso no código "TEMPO" , que seria o tempo suficiente
  para que a etapa do efeito bouncing passasse, e desta forma minimizar esse problema.
  */
  // Usamoa a Negação (!) porque stamos usando INPUT_PULLUP
  /* millis () - Retorna o número de milissegundos passados desde que a placa Arduino começou a executar
  o programa atual. Esse número irá sofrer overflow (chegar ao maior número possível e então voltar pra zero).
  */
  
  // if (!estadoBotaoVm && estadoAntBotVm) contador++;
  if ((millis() - debouncingBotVm) > debouncingTempo){ 
    // Verifica se o tenpo que ja se passou e menor que o tenpo da ultima execução do botão!
    if (!estadoBotaoVm && estadoAntBotVm) {
      contador++;
      debouncingBotVm = millis(); // Guardo na variavel o Tempo atual da execução!
    }    
  }
  // if (!estadoBotaoAm && estadoAntBotAm) contador--;
  if ((millis() - debouncingBotAm) > debouncingTempo){ 
    if (!estadoBotaoAm && estadoAntBotAm) {
      contador--;
      debouncingBotVm = millis();
    }    
  }
  //if (!estadoBotaoAz && estadoAntBotAz) contador = 0;
  if ((millis() - debouncingBotAz) > debouncingTempo){ 
    if (!estadoBotaoAz && estadoAntBotAz) {
      contador = 0;
      debouncingBotVm = millis();
    }    
  }

  if(contador >= 5){
    digitalWrite(pinLedVm, HIGH);
  } else{
    digitalWrite(pinLedVm, LOW);
  };

  if(contador >= 10){
    digitalWrite(pinLedAm, HIGH);
  } else{
    digitalWrite(pinLedAm, LOW);
  };

  if(contador >= 15){
    digitalWrite(pinLedAz, HIGH);
  } else{
    digitalWrite(pinLedAz, LOW);
  };
  Serial.print("Contador : ");
  Serial.println(contador);

  Serial.println("Vm-Am-Az");
  Serial.print(" ");
  Serial.print(estadoAntBotVm);
  Serial.print("- ");
  Serial.print(estadoAntBotAm);
  Serial.print("- ");
  Serial.print(estadoAntBotAz);
  Serial.println(" ");
  estadoAntBotVm = estadoBotaoVm;
  estadoAntBotAm = estadoBotaoAm;
  estadoAntBotAz = estadoBotaoAz;
}
