/*
  Curso de Arduino .NET - Flávio Guimarães
  CANAL: Brincando com Ideias - https://www.youtube.com/c/BrincandocomIdeias
  SITE: https://www.brincandocomideias.com/
  Autor:  Argênio Silveira 
  Link:   https://wokwi.com/arduino/projects/314259276451283521
  MODULO: Módulo 5 - Programação avançada (4 aulas)
  SKETCH: 04 - Aula 24 - Comunicação I2C - Exercicio Aula 23
*/
void setup(){
  Serial.begin(9600);
  Serial.println("Ola Mundo.");
  Serial.println("Sketch iniciado e preparado para receber dados via serial (Rx)");
  pinMode(LED_BUILTIN, OUTPUT);
}
void loop(){
  if(Serial.available()){
    char recebido = Serial.read();
    Serial.print(recebido);
    if (recebido == 'L'){
      digitalWrite(LED_BUILTIN, HIGH);
    }
    if (recebido == 'D'){
      digitalWrite(LED_BUILTIN, LOW);
    }
    if (recebido == 'P'){
      for(int i=0 ; i<5 ; i++){
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500);
        digitalWrite(LED_BUILTIN, LOW);
        delay(500);
      }
    }
  }
}