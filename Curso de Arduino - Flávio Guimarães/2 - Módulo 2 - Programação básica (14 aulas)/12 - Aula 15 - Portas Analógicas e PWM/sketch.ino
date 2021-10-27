/*
  Curso de Arduino .NET - Flávio Guimarães
  CANAL: Brincando com Ideias - https://www.youtube.com/c/BrincandocomIdeias
  SITE: https://www.brincandocomideias.com/
  Autor:  Argênio Silveira 
  Link:   https://wokwi.com/arduino/projects/313616325715952193
  MODULO: 2 - Módulo 2 - Programação básica (14 aulas)
  SKETCH: 12 - Aula 15 - Portas Analógicas e PWM
*/
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(8, OUTPUT); //Portas PWM temos o Simbolo ~ proximo a porta! nese caso aporta 8 não é!
  analogWrite(8,255);// 0 a 255 0 = 0 Vlts 255 = 5 Volts

  /*
  Foi Visto nessa aula um pouco sobre o Divisor de tensão
  Ficou claro que um Divisor de tensao deve ser usado apemapara leitura digital
  para alimentar devemos usar o Regulador de tensao "Nunca" um divisor de tensao!

  [(R2 / R1 + R2) * Vin = Vout]
  Exemplo: 
  5.6 /( 3.3 + 5.6) * 5 = 3.14
  (5.6 / 8,9) * 5 = 3.14
  0,6292 * 5 = 3.14

  */
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int lido = analogRead(A0);
  int tensao = map(lido, 0, 1023, 0, 500);

  Serial.print("Valor Lido: ");
  Serial.println(lido); // Imprime valor Lido
  Serial.print("Valor Tensao: ");
  Serial.println(tensao); //Imprime o valor convertido pata tensao
  delay(2000);
}