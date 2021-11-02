/*
  Curso de Arduino .NET - Flávio Guimarães
  CANAL: Brincando com Ideias - https://www.youtube.com/c/BrincandocomIdeias
  SITE: https://www.brincandocomideias.com/
  Autor:  Argênio Silveira 
  Link:   https://wokwi.com/arduino/projects/314084504946868800
  MODULO: Módulo 4 - Programação avançada (10 aulas)
  SKETCH: 06 - Aula 21 - Programação Orientada a Objetos - Exercicio Aula 20
*/

#define tamanhoPortas 5
byte portas[tamanhoPortas] = {4,9,10,11,12};//0 a 4

struct estruturaDataLog {
  byte numeroLeitura;
  String data;
  String hora;
  byte umidade;
  int temperatura;
};

#define leiturasTamanho 50
estruturaDataLog Leituras[leiturasTamanho];// 0 a 49

void setup() {
  Serial.begin(9600);
  for(int i = 0;i < leiturasTamanho;i++){
    Leituras[i].numeroLeitura = i;
    Leituras[i].data = "01/11/2021";
    Leituras[i].hora = "09:00";
    Leituras[i].umidade = i;
    Leituras[i].temperatura = i;
  };

  for(int i = 0;i < leiturasTamanho;i++){
    Serial.print("Leitura N:");
    Serial.println(Leituras[i].numeroLeitura + 1);
    Serial.print("Data: ");
    Serial.println(Leituras[i].data);
    Serial.print("Hora: ");
    Serial.println(Leituras[i].hora);
    Serial.print("Umidade: ");
    Serial.println(Leituras[i].umidade);
    Serial.print("Temperatura: ");
    Serial.println(Leituras[i].temperatura);
  };

  for (int conta = 0; conta <tamanhoPortas ; conta++){
    pinMode(portas[conta], INPUT_PULLUP);
    Serial.println(portas[conta]);
  }
} 
void loop() {
}