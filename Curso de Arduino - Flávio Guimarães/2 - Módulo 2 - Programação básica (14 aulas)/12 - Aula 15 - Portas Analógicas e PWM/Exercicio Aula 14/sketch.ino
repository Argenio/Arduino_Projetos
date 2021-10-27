/*
  Curso de Arduino .NET - Flávio Guimarães
  CANAL: Brincando com Ideias - https://www.youtube.com/c/BrincandocomIdeias
  SITE: https://www.brincandocomideias.com/
  Autor:  Argênio Silveira 
  Link:   https://wokwi.com/arduino/projects/313613653566816832
  MODULO: 2 - Módulo 2 - Programação básica (14 aulas)
  SKETCH: 12 - Aula 15 - Portas Analógicas e PWM - Exercicio Aula 14
*/
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  byte varByte;
  int varInt;
  long varLong;
  float varFloat;

  unsigned int varUnsignetInt;
  unsigned long varUnsignedLong;
  
  Serial.println("Valores que Cabem da Variavel: ");
  varByte = 255; // Valor Maximo
  varInt = 32767; // Valor Maximo
  varLong = 2147483647; // Valor Maximo
  varFloat = 15350.456;
  varUnsignetInt = 65535; // Valor Maximo
  varUnsignedLong = 4294967295; // Valor Maximo
  Serial.print("varByte: ");
  Serial.println(varByte); 
  Serial.print("varInt: ");
  Serial.println(varInt);
  Serial.print("varLong: ");
  Serial.println(varLong);
  Serial.print("varFloat: ");
  Serial.println(varFloat);
  Serial.print("varUnsignetInt: ");
  Serial.println(varUnsignetInt); 
  Serial.print("varUnsignedLong: ");
  Serial.println(varUnsignedLong);

  Serial.println("Valores que 'Não' Cabem da Variavel: ");
  varByte = 521;
  varInt = -55000;
  varLong = 9000000000;
  varFloat = 654654135615350.456;
  varUnsignetInt = -15;
  varUnsignedLong = -10;
  Serial.print("varByte: ");
  Serial.println(varByte); 
  Serial.print("varInt: ");
  Serial.println(varInt);
  Serial.print("varLong: ");
  Serial.println(varLong);
  Serial.print("varFloat: ");
  Serial.println(varFloat);
  Serial.print("varUnsignetInt: ");
  Serial.println(varUnsignetInt); 
  Serial.print("varUnsignedLong: ");
  Serial.println(varUnsignedLong);

}

void loop() {
  // put your main code here, to run repeatedly:
  

}
