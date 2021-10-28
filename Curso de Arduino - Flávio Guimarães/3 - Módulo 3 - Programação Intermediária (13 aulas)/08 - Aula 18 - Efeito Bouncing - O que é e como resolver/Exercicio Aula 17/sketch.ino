void setup() {
  Serial.begin(9600);

  Serial.println("08 - Aula 18 - Efeito Bouncing - O que é e como resolver - Exercicio Aula 17");
  Serial.println("Operadores de comparação");

  Serial.println("Tabela de Negação - Não (!)");

  Serial.print("/ !0 = ");
  Serial.print(!0);
  Serial.print(" / !1 = ");
  Serial.print(!1);
  Serial.print(" / !false = ");
  Serial.print(!false);
  Serial.print(" / !true = ");
  Serial.print(!true);
  Serial.print(" / !LOW = ");
  Serial.print(!LOW);
  Serial.print(" / !Hight = ");
  Serial.print(!HIGH);
  Serial.println(" /");

  Serial.println("Comparação: ");
  Serial.print(!0);
  Serial.print(!1);
  Serial.print(!false);
  Serial.print(!true);
  Serial.print(!LOW);
  Serial.print(!HIGH);

  Serial.println("");

  Serial.println("Tabela E - (&&)");

  Serial.print("/ 0 && 0 = ");
  Serial.print( 0 && 0);
  Serial.print(" / 1 && 0 = ");
  Serial.print( 1 && 0);
  Serial.print(" / 0 && 1 = ");
  Serial.print( 0 && 1);
  Serial.print(" / 1 && 1 = ");
  Serial.print( 1 && 1);
  Serial.println(" /");

  Serial.print("/ false && false = ");  
  Serial.print( false && false );
  Serial.print(" / true && false = ");
  Serial.print( true && false);
  Serial.print(" / false && true = ");
  Serial.print( false && true);
  Serial.print(" / true && true = ");
  Serial.print( true && true);
  Serial.println(" /");

  Serial.print("/ LOW && LOW = "); 
  Serial.print( LOW && LOW);
  Serial.print(" / HIGH && LOW = ");
  Serial.print( HIGH && LOW);
  Serial.print(" / LOW && HIGH = ");
  Serial.print( LOW && HIGH);
  Serial.print(" / HIGH && HIGH = ");
  Serial.print( HIGH && HIGH);
  Serial.println(" /");

  Serial.println("Comparação: ");
  Serial.print( 0 && 0);
  Serial.print( 1 && 0);
  Serial.print( 0 && 1);
  Serial.println( 1 && 1);
  
  Serial.print( false && false );
  Serial.print( true && false);
  Serial.print( false && true);
  Serial.println( true && true);

  Serial.print( LOW && LOW);
  Serial.print( HIGH && LOW);
  Serial.print( LOW && HIGH);
  Serial.print( HIGH && HIGH);

  Serial.println("");

  Serial.println("Tabela OU - (||)");

  Serial.print("/ 0 || 0 = ");
  Serial.print( 0 || 0);
  Serial.print(" /  1 || 0 = ");
  Serial.print( 1 || 0);
  Serial.print(" / 0 || 1 = ");
  Serial.print( 0 || 1);
  Serial.print(" / 1 || 1 = ");
  Serial.print( 1 || 1);
  Serial.println(" /");

  Serial.print("/ false || false = ");  
  Serial.print( false || false );
  Serial.print(" / true || false = ");
  Serial.print( true || false);
  Serial.print(" / false || true = ");
  Serial.print( false || true);
  Serial.print(" / true || true = ");
  Serial.print( true || true);
  Serial.println(" /");

  Serial.print("/ LOW || LOW = "); 
  Serial.print( LOW || LOW);
  Serial.print(" / HIGH || LOW = ");
  Serial.print( HIGH || LOW);
  Serial.print(" / LOW || HIGH = ");
  Serial.print( LOW || HIGH);
  Serial.print(" / HIGH || HIGH = ");
  Serial.print( HIGH || HIGH);
  Serial.println(" /");

  Serial.println("Comparação: ");
  Serial.print( 0 || 0);
  Serial.print( 1 || 0);
  Serial.print( 0 || 1);
  Serial.println( 1 || 1);
  
  Serial.print( false || false );
  Serial.print( true || false);
  Serial.print( false || true);
  Serial.println( true || true);

  Serial.print( LOW || LOW);
  Serial.print( HIGH || LOW);
  Serial.print( LOW || HIGH);
  Serial.print( HIGH || HIGH);

  Serial.println("");

  Serial.println("Operador Igual - (==)");

  Serial.print("/ 50 == 30 = ");
  Serial.print( 50 == 30);
  Serial.print(" / true == 1 = ");
  Serial.print( true == 1);
  Serial.print(" / 15 == 15 = ");
  Serial.print( 15 == 15);
  Serial.print(" / abc == def = ");
  Serial.print( "abc" == "def");
  Serial.print(" / def == def = ");
  Serial.print( "def" == "def");
  Serial.println(" /");

  Serial.println("Comparação: ");
  Serial.print( 50 == 30);
  Serial.print( true == 1);
  Serial.print( 15 == 15);
  Serial.print( "abc" == "def");
  Serial.println( "def" == "def");

  Serial.println("");

  Serial.println("Operador Diferente - (!=)");

  Serial.print("/ 50 != 30 = ");
  Serial.print( 50 != 30);
  Serial.print(" / true != 1 = ");
  Serial.print( true != 1);
  Serial.print(" / 15 != 15 = ");
  Serial.print( 15 != 15);
  Serial.print(" / abc != def = ");
  Serial.print( "abc" != "def");
  Serial.print(" / def != def = ");
  Serial.print( "def" != "def");
  Serial.println(" /");
  
  Serial.println("Comparação: ");
  Serial.print( 50 != 30);
  Serial.print( true != 1);
  Serial.print( 15 != 15);
  Serial.print( "abc" != "def");
  Serial.println( "def" != "def");

  Serial.println("");

  Serial.println("Operador Maior - (>)");

  Serial.print("/ 50 > 30 = ");
  Serial.print( 50 > 30);
  Serial.print(" / true > 1 = ");
  Serial.print( true > 1);
  Serial.print(" / 15 > 15 = ");
  Serial.print( 15 > 15);
  Serial.print(" / abc > def = ");
  Serial.print( "abc" > "def");
  Serial.print(" / def > def = ");
  Serial.print( "def" > "def");
  Serial.println(" /");

  Serial.println("Comparação: ");
  Serial.print( 50 > 30);
  Serial.print( true > 1);
  Serial.print( 15 > 15);
  Serial.print( "abc" > "def");
  Serial.println( "def" > "def");

  Serial.println("");

  Serial.println("Operador Menor - (<)");

  Serial.print("/ 50 < 30 = ");
  Serial.print( 50 < 30);
  Serial.print(" / true < 1 = ");
  Serial.print( true < 1);
  Serial.print(" / 15 < 15 = ");
  Serial.print( 15 < 15);
  Serial.print(" / abc < def = ");
  Serial.print( "abc" < "def");
  Serial.print(" / def < def = ");
  Serial.print( "def" < "def");
  Serial.println(" /");

  Serial.println("Comparação: ");
  Serial.print( 50 < 30);
  Serial.print( true < 1);
  Serial.print( 15 < 15);
  Serial.print( "abc" < "def");
  Serial.println( "def" < "def");

  Serial.println("");

  Serial.println("Operador Maior ou Igual - (>=)");

  Serial.print("/ 50 >= 30 = ");
  Serial.print( 50 >= 30);
  Serial.print(" / true >= 1 = ");
  Serial.print( true >= 1);
  Serial.print(" / 15 >= 15 = ");
  Serial.print( 15 >= 15);
  Serial.print(" / abc >= def = ");
  Serial.print( "abc" >= "def");
  Serial.print(" / def >= def = ");
  Serial.print( "def" >= "def");
  Serial.println(" /");

  Serial.println("Comparação: ");
  Serial.print( 50 >= 30);
  Serial.print( true >= 1);
  Serial.print( 15 >= 15);
  Serial.print( "abc" >= "def");
  Serial.println( "def" >= "def");

  Serial.println("");

  Serial.println("Operador Menor ou Igual - (<=)");

  Serial.print("/ 50 <= 30 = ");
  Serial.print( 50 <= 30);
  Serial.print(" / true <= 1 = ");
  Serial.print( true <= 1);
  Serial.print(" / 15 <= 15 = ");
  Serial.print( 15 <= 15);
  Serial.print(" / abc <= def = ");
  Serial.print( "abc" <= "def");
  Serial.print(" / def <= def = ");
  Serial.print( "def" <= "def");
  Serial.println(" /");

  Serial.println("Comparação: ");
  Serial.print( 50 <= 30);
  Serial.print( true <= 1);
  Serial.print( 15 <= 15);
  Serial.print( "abc" <= "def");
  Serial.println( "def" <= "def");
  
  Serial.println("");
}

void loop() {
  // put your main code here, to run repeatedly:

}
