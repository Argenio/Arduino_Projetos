/*
  Curso de Arduino .NET - Flávio Guimarães
  CANAL: Brincando com Ideias - https://www.youtube.com/c/BrincandocomIdeias
  SITE: https://www.brincandocomideias.com/
  Autor:  Argênio Silveira 
  Link:   https://wokwi.com/arduino/projects/313626449954210368
  MODULO: 3 - Módulo 3 - Programação Intermediária (13 aulas) 
  SKETCH: 01 - Aula 16 - Programação de Condições IF, ELSE e ELSEIF - Exercicio Aula 15
*/
  #define potenciometro A0
  #define led1 10
  #define led2 11

  int lido;
  int tensao;
  float volts;
  byte portaPWM; // 0 a 255 0 = 0 Vlts 255 = 5 Volts

void setup() {

  Serial.begin(9600);
  //Portas PWM temos o Simbolo ~ proximo a porta!
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

}

void loop() {

  lido = analogRead(potenciometro);
  tensao = map(lido, 0, 1023, 0, 500);
  volts = (float)tensao / 100;
  portaPWM = map(lido, 0, 1023, 0, 255);

  Serial.print("Valor Lido: ");
  Serial.println(lido); // Imprime valor Lido
  Serial.print("Valor Tensao: ");
  Serial.print(volts); //Imprime o valor convertido pata tensao
  Serial.println(" Volts ");
  Serial.print("Valor PortaPWM: ");
  Serial.println(portaPWM);
  analogWrite(led2,portaPWM); // 0 a 255 0 = 0 Vlts 255 = 5 Volts
  analogWrite(led1,portaPWM);
  delay(2000);
}