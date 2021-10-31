/*
  Curso de Arduino .NET - Flávio Guimarães
  CANAL: Brincando com Ideias - https://www.youtube.com/c/BrincandocomIdeias
  SITE: https://www.brincandocomideias.com/
  Autor:  Argênio Silveira 
  Link:   https://wokwi.com/arduino/projects/313995651866165824
  MODULO: Módulo 4 - Programação avançada (10 aulas)
  SKETCH: 01 - Aula 20 - Estrutura de Dados e Array - Exercicio Aula 19
*/
String txtRecebido;
String txtInvertido;
int txtTamanho = 0;
byte tempoDelay = 200;
unsigned long delaySerial;

void setup() {
  Serial.begin(9600);
  Serial.println("");
}

void loop() {
  while(Serial.available()) {
    char lido = char (Serial.read()); 
    txtRecebido += lido;
    txtTamanho++;
    delaySerial = millis();
  }
  if (((millis() - delaySerial) > tempoDelay) && (txtRecebido != "")){
    txtInvertido = "";
    Serial.print("Texto Recebido: ");
    Serial.print(txtRecebido);
    Serial.println("");
    for (int contador = 0; contador <= txtTamanho; contador++){
      txtInvertido = txtRecebido.charAt(contador) + txtInvertido;
    }
    Serial.print("Texto Invertido: ");
    Serial.print(txtInvertido);
    Serial.println("");
    txtRecebido = "";    
    txtTamanho = 0;
  }
}