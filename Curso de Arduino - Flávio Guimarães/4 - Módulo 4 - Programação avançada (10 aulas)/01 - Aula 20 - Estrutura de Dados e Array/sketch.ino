/*
  Curso de Arduino .NET - Flávio Guimarães
  CANAL: Brincando com Ideias - https://www.youtube.com/c/BrincandocomIdeias
  SITE: https://www.brincandocomideias.com/
  Autor:  Argênio Silveira 
  Link:   https://wokwi.com/arduino/projects/313998839611654720
  MODULO: Módulo 4 - Programação avançada (10 aulas)
  SKETCH: 01 - Aula 20 - Estrutura de Dados e Array
*/

//Estrutura
struct estruturaDataLog {
  String data;
  String hora;
  byte umidade;
  int temperatura;
};

// Variaveis do Tipo da Estrutura
estruturaDataLog leitura1;
estruturaDataLog leitura2;

//Array
#define tamanhoPortas 3
byte portas[tamanhoPortas]{8,9,10}; //0,1,2 = 3 (não existe a posição 3)
#define tamanhoArray3D 3
byte array3D[3][3][3]; //3*3*3 = nove espaços einicia em 0 

void setup() {
  Serial.begin(9600);

  //Lançamento de Dados nas Variaveis do tipo Estrutura
  leitura1.data = "01/11/2021";
  leitura1.hora = "09:00";
  leitura1.umidade = 50;
  leitura1.temperatura = 28;

  leitura2.data = "02/11/2021";
  leitura2.hora = "09:30";
  leitura2.umidade = 40;
  leitura2.temperatura = 30;

  // Leitura de Dados das Variaveis dp tipo Estutura
  Serial.println("Leitura1");
  Serial.print("Data: ");
  Serial.println(leitura1.data);
  Serial.print("Hora: ");
  Serial.println(leitura1.hora);
  Serial.print("Umidade: ");
  Serial.println(leitura1.umidade);
  Serial.print("Temperatura: ");
  Serial.println(leitura1.temperatura);

  Serial.println("Leitura2");
  Serial.print("Data: ");
  Serial.println(leitura2.data);
  Serial.print("Hora: ");
  Serial.println(leitura2.hora);
  Serial.print("Umidade: ");
  Serial.println(leitura2.umidade);
  Serial.print("Temperatura: ");
  Serial.println(leitura2.temperatura);
/*
  //Lançamento de Dados nas Variaveis do tipo Array 
  portas[0] = 8;
  portas[1] = 9;
  portas[2] = 10;
*/
  for (int conta = 0; conta <tamanhoPortas ; conta++){
    pinMode(portas[conta], INPUT_PULLUP);
    Serial.println(portas[conta]);
  }
} 
void loop() {
}