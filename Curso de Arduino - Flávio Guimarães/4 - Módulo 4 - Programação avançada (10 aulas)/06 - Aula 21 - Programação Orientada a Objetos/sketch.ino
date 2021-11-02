/*
  Curso de Arduino .NET - Flávio Guimarães
  CANAL: Brincando com Ideias - https://www.youtube.com/c/BrincandocomIdeias
  SITE: https://www.brincandocomideias.com/
  Autor:  Argênio Silveira 
  Link:   https://wokwi.com/arduino/projects/314086624342311488
  MODULO: Módulo 4 - Programação avançada (10 aulas)
  SKETCH: 06 - Aula 21 - Programação Orientada a Objetos
*/
#define pinLedVm 10
#define pinLedAm 9
#define pinLedAz 8
#define pinButtonVm 7
#define pinButtonAm 6
#define pinButtonAz 5

byte contador = 0;

//**************************************************************************************************************
// -------------------- DECLARAÇÃO DA CLASSE --------------------
class PushButton {
  public:
    PushButton(byte pinButton,int debouncingTime = 200);// valor padrao do debouncing // Função Construtora!
    void Button_loop(); // função loop
    bool Pressed();// verifica o status do Botao
  private:
    unsigned long debouncingButton; // Variamel para controlar o tempo de debouncing
    bool PreviousStateButton = HIGH; // Porque estamos trabalhando com INPUT_PULLUP
    bool state = false; // Estado do botão começa como state "false" - Não
    byte pin; // Gardamos o pin da porta
    int time; // Controlamos o tempo
}; // Declaração da Classe

// -------------------- INICIO DO IMPLEMENTPO DA CLASSE --------------------
PushButton::PushButton(byte pinButton,int debouncingTime) {
  pinMode(pinButton, INPUT_PULLUP);
  pin = pinButton;
  time = debouncingTime;
}

void PushButton::Button_loop() {
  bool stateButton = digitalRead(pin);
  bool state = false;
  if ((millis() - debouncingButton) > time){
    if (!stateButton && PreviousStateButton) {
      state = true;
      //Serial.println(state);
      debouncingButton = millis();
    } 
  }
  PreviousStateButton = stateButton;
}

bool PushButton::Pressed(){
  //Serial.println(state);
  return state;
}
// -------------------- FIM DO IMPLEMENTPO DA CLASSE --------------------
//**************************************************************************************************************

PushButton ButtonVm (pinButtonVm);
PushButton ButtonAm (pinButtonAm);
PushButton ButtonAz (pinButtonAz);

void setup() {
  pinMode(pinLedVm, OUTPUT);
  pinMode(pinLedAm, OUTPUT);
  pinMode(pinLedAz, OUTPUT);

  Serial.begin(9600);
  Serial.print(" ");
}

void loop() {
  ButtonVm.Button_loop();
  ButtonAm.Button_loop();
  ButtonAz.Button_loop();

  if (ButtonVm.Pressed()){
    contador++;
    Serial.println(contador);
  }

  if (ButtonAm.Pressed()){
    contador--;
    Serial.println(contador);
  }

  if (ButtonAz.Pressed()){
    contador = 0;
    Serial.println(contador);
  }

  if(contador >= 5){
    digitalWrite(pinLedVm, HIGH);
  } else{
    digitalWrite(pinLedVm, LOW);
  }

  if(contador >= 10){
    digitalWrite(pinLedAm, HIGH);
  } else{
    digitalWrite(pinLedAm, LOW);
  }

  if(contador >= 15){
    digitalWrite(pinLedAz, HIGH);
  } else{
    digitalWrite(pinLedAz, LOW);
  }
}
