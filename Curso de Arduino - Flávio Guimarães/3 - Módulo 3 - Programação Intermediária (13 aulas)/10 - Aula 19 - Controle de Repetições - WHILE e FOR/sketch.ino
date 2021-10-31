/*
  Curso de Arduino .NET - Flávio Guimarães
  CANAL: Brincando com Ideias - https://www.youtube.com/c/BrincandocomIdeias
  SITE: https://www.brincandocomideias.com/
  Autor:  Argênio Silveira 
  Link:   https://wokwi.com/arduino/projects/313815033598444098
  MODULO: 3 - Módulo 3 - Programação Intermediária (13 aulas)
  SKETCH: 10 - Aula 19 - Controle de Repetições - WHILE e FOR
*/
String txtRecebido;
byte tempoDelay = 200;
unsigned long delaySerial;

void setup() {
  Serial.begin(9600);
  Serial.println("");

  // Conteudo for -------------
  for (int x = 32; x <= 127; x++){
    Serial.print(x);
    Serial.print("-");
    Serial.println(char(x));
  }
}

void loop() {

  // Conteudo while -------------

  // Serial.available()  - Retorna se existe alguma informação sendo recebina na porta serial
  while(Serial.available()) {
    //Serial.read(); // Ler uma informação enviada pelo Serial do tipo numero da tabela ASCII = a letra correspondente
    char lido0 = Serial.read();
    Serial.print("lido0 : ");
    Serial.write(lido0);
    Serial.println("");
    char lido = char (lido0); // char() Conversão de Tipo Numero da Tabela ASCII em Caracter da Letra.
    Serial.print("lido  : ");
    Serial.println(lido);
    txtRecebido += lido; // txtRecebido recebe os caracteres e agrupa como String
    delaySerial = millis();
  }
  if (((millis() - delaySerial) > tempoDelay) && (txtRecebido != "") ){
    Serial.print("Texto Recebido: ");
    Serial.println(txtRecebido);
    txtRecebido = "";
  }
}