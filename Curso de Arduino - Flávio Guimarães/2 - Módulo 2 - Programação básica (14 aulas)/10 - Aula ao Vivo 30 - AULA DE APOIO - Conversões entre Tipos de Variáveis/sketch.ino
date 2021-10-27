/*
  Curso de Arduino .NET - Flávio Guimarães
  CANAL: Brincando com Ideias - https://www.youtube.com/c/BrincandocomIdeias
  SITE: https://www.brincandocomideias.com/
  Autor:  Argênio Silveira 
  Link:   https://wokwi.com/arduino/projects/313543461092459074
  MODULO: 2 - Módulo 2 - Programação básica (14 aulas)
  SKETCH: 10 - Aula ao Vivo 30 - AULA DE APOIO - Conversões entre Tipos de Variáveis
*/

#define ledBit0 9 
#define ledBit1 8
#define ledBit2 7
#define ledBit3 6
#define ledBit4 5
#define ledBit5 4
#define ledBit6 3
#define ledBit7 2
// 8 LEDs = 8 Bits
int varInt = 0; // Variavel interia para converter em bit

String comando;

void setup() {
  Serial.begin(9600);
  Serial.println ("Aula sobre tipos de Dados e Comversão");
  Serial.println ("8 LED's = 8 Bits");
  Serial.println("");

  Serial.print("varInt contem: ");
  Serial.println(varInt);
  Serial.print("(print) ");
  Serial.write(varInt);
  Serial.println("");
  Serial.print("(write) ");
  Serial.println(varInt, BIN);
  Serial.print("(BIN) ");
  Serial.println("");

  pinMode(ledBit0, OUTPUT);
  pinMode(ledBit1, OUTPUT);
  pinMode(ledBit2, OUTPUT);
  pinMode(ledBit3, OUTPUT);
  pinMode(ledBit4, OUTPUT);
  pinMode(ledBit5, OUTPUT);
  pinMode(ledBit6, OUTPUT);
  pinMode(ledBit7, OUTPUT);
}

void loop() {
  digitalWrite(ledBit0,bitRead(varInt, 0));
  digitalWrite(ledBit1,bitRead(varInt, 1));
  digitalWrite(ledBit2,bitRead(varInt, 2));
  digitalWrite(ledBit3,bitRead(varInt, 3));
  digitalWrite(ledBit4,bitRead(varInt, 4));
  digitalWrite(ledBit5,bitRead(varInt, 5));
  digitalWrite(ledBit6,bitRead(varInt, 6));
  digitalWrite(ledBit7,bitRead(varInt, 7));

  if(Serial.available()){
    char lido = Serial.read();
    if (lido == ';'){
      varInt = comando.toInt();
      comando = "";
      
      Serial.print("varInt contem: ");
      Serial.println(varInt);
      Serial.print("(print) ");
      Serial.write(varInt);
      Serial.println("");
      Serial.print("(write) ");
      Serial.println(varInt, BIN);
      Serial.print("(BIN) ");
      Serial.println("");

    }else{
      comando += lido;
    }
  }
}
