#include <Servo.h>
Servo myservo;

int periodo = 2040;  //microsegundos
int largura = 1020;

unsigned long momentoInicioCiclo;
unsigned int tempoCiclo;

void setup() {
  
   pinMode(8, OUTPUT);
   pinMode(3, OUTPUT);   //para uso do PWM interno
   
   myservo.attach(9);    //para uso da biblioteca Servo
   
   momentoInicioCiclo = micros();
}

void loop() {

   //PWM
   //largura = map(analogRead(A0), 0, 1023, 0, periodo); 
   
   //analogWrite(3, map(analogRead(A0), 0, 1023, 0, 255) );



   
   //TONE
   //periodo = map(analogRead(A0), 0, 1023, 200, 3300);
   //largura = periodo / 2;

   //tone(3, map(analogRead(A0), 0, 1023, 300, 5000)); 
   



   //SERVO
   //periodo = 20000;
   //largura = map(analogRead(A0), 0, 1023, 540, 2400); 
   
   myservo.write(map(analogRead(A0), 0, 1023, 0, 180)); 

   
   tempoCiclo = micros() - momentoInicioCiclo;
   if ( tempoCiclo <= largura ) {
      digitalWrite(8, HIGH); 
   } else {
      digitalWrite(8, LOW); 
   }
   if ( tempoCiclo >= periodo ) {
      momentoInicioCiclo = micros();
   } 
   

   /*
   int periodo = 100;  //milisegundos
   int largura = 20;
   
   tempoCiclo = millis() - momentoInicioCiclo;
   if ( tempoCiclo <= largura ) {
      digitalWrite(8, HIGH); 
   } else {
      digitalWrite(8, LOW); 
   }
   if ( tempoCiclo >= periodo ) {
      momentoInicioCiclo = millis();
   } 
   */  
}
