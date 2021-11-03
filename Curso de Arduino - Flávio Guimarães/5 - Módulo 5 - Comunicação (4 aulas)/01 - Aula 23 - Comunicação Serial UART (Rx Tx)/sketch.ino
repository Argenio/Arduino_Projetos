/*
  Curso de Arduino .NET - Flávio Guimarães
  CANAL: Brincando com Ideias - https://www.youtube.com/c/BrincandocomIdeias
  SITE: https://www.brincandocomideias.com/
  Autor:  Argênio Silveira 
  Link:   https://wokwi.com/arduino/projects/314243845403443776
  MODULO: Módulo 5 - Programação avançada (4 aulas)
  SKETCH: 01 - Aula 23 - Comunicação Serial UART (Rx Tx)
*/
void setup(){
  Serial.begin(9600);
  Serial.println("Ola Mundo.");
  Serial.println("Sketch iniciado e preparado para receber dados via serial (Rx)");
}
void loop(){
  if(Serial.available()){
    char recebido = Serial.read();

    Serial.print(recebido);
  }

}