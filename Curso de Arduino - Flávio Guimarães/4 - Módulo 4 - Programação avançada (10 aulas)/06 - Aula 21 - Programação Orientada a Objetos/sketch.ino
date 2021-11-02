/*
  Curso de Arduino .NET - Flávio Guimarães
  CANAL: Brincando com Ideias - https://www.youtube.com/c/BrincandocomIdeias
  SITE: https://www.brincandocomideias.com/
  Autor:  Argênio Silveira 
  Link:   https://wokwi.com/arduino/projects/314098327106880064
  MODULO: Módulo 4 - Programação avançada (10 aulas)
  SKETCH: 06 - Aula 21 - Programação Orientada a Objetos
*/
#define pinLedVm 10
#define pinLedAm 9
#define pinLedAz 8
#define pinBotaoVm 7
#define pinBotaoAm 6
#define pinBotaoAz 5

byte contador = 0;

//**************************************************************************************************************
// -------------------- DECLARAÇÃO DA CLASSE --------------------
class PushButton {
  public:
    PushButton(byte pinBotao,int tempoDebounce = 200);// valor padrao do debouncing // Função Construtora!
    void button_loop(); // função loop
    bool Pressed();// verifica o status do Botao
  private:
    unsigned long debounceBotao; // Variamel para controlar o tempo de debouncing
    bool estadoBotaoAnt = HIGH; // Porque estamos trabalhando com INPUT_PULLUP
    bool apertado = false; // Estado do botão começa como apertado "false" - Não
    byte pino; // Gardamos o pin da porta
    int tempo; // Controlamos o tempo
}; // Declaração da Classe

// -------------------- INICIO DO IMPLEMENTPO DA CLASSE --------------------
PushButton::PushButton(byte pinBotao,int tempoDebounce = 200) {
  pinMode(pinBotao, INPUT_PULLUP);
  pino = pinBotao;
  tempo = tempoDebounce;
}

void PushButton::button_loop() {
  bool estadoBotao = digitalRead(pino);
  apertado = false;
  if ((millis() - debounceBotao) > tempo){
    if (!estadoBotao && estadoBotaoAnt) {
      apertado = true;
      //Serial.println(apertado);
      debounceBotao = millis();
    } 
  }
  estadoBotaoAnt = estadoBotao;
}

bool PushButton::Pressed(){
  return apertado;
}
// -------------------- FIM DO IMPLEMENTPO DA CLASSE --------------------
//**************************************************************************************************************
PushButton botao1 (pinBotaoVm);
PushButton botao2 (pinBotaoAm);
PushButton botao3 (pinBotaoAz);

void setup() {
  pinMode(pinLedVm, OUTPUT);
  pinMode(pinLedAm, OUTPUT);
  pinMode(pinLedAz, OUTPUT);

  Serial.begin(9600);
  Serial.println(" ");
}

void loop() {
  botao1.button_loop();
  botao2.button_loop();
  botao3.button_loop();

  if (botao1.Pressed()) {
    contador++;
  };

  if (botao2.Pressed()) {
    contador--;
  };

  if (botao3.Pressed()) {
    contador = 0;
  };

  if(contador >= 5) {
    digitalWrite(pinLedVm, HIGH);
  } else{
    digitalWrite(pinLedVm, LOW);
  };

  if(contador >= 10) {
    digitalWrite(pinLedAm, HIGH);
  } else{
    digitalWrite(pinLedAm, LOW);
  };

  if(contador >= 15) {
    digitalWrite(pinLedAz, HIGH);
  } else{
    digitalWrite(pinLedAz, LOW);
  };
  Serial.print("Contador :");
  Serial.println(contador);
}