#include <SoftwareSerial.h>
#include <Rfid134.h>

// Definição de Portas Arduino Uno
#define pinCartaoSD 10
#define RXD 9 // Pino  de Escrita de Dados (Não Utilizamos nesse Modulo)
#define TXD 8 // Pino de Leitura de Dados do Modulo RFID WL-134
#define RST 7 // Pino de Reset do Modulo RFID WL-134
#define buzzer 6 // Pino do Buzzer para ver que foi lido
/*
 ** SDCS - pin 10
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
*/

// implementar uma classe de notificação,
// seus métodos de membro serão chamados
//
class RfidNotify
{
  public:
    static void OnError(Rfid134_Error errorCode)
    {
      // veja Rfid134_Error para o significado do código
      Serial.println("");
      Serial.print("Com Error ");
      Serial.println(errorCode);
    }

    static void OnPacketRead(const Rfid134Reading& reading)
    {
      char temp[8];

      Serial.print("TAG: ");
      sprintf(temp, "%03u", reading.country); // Como print não suporta zeros à esquerda, usei sprintf
      Serial.print(temp);
      // uma vez que sprintf com AVR não suporta uint64_t (llu / lli), use /% trick para
      sprintf(temp, "%06lu", static_cast<uint32_t>(reading.id / 1000000)); // Como print não suporta zeros à esquerda, usei sprintf
      Serial.print(temp);
      sprintf(temp, "%06lu", static_cast<uint32_t>(reading.id % 1000000)); // Como print não suporta zeros à esquerda, usei sprintf
      Serial.print(temp);
      Serial.println(" #");      
      Serial.print("Pais Cod.: ");
      sprintf(temp, "%03u", reading.country); // Como print não suporta zeros à esquerda, usei sprintf
      Serial.print(temp);
      
      Serial.print(" ");
      Serial.print("ID.: ");
      // uma vez que sprintf com AVR não suporta uint64_t (llu / lli), use /% trick para
      sprintf(temp, "%06lu", static_cast<uint32_t>(reading.id / 1000000)); // Como print não suporta zeros à esquerda, usei sprintf
      Serial.print(temp);
      sprintf(temp, "%06lu", static_cast<uint32_t>(reading.id % 1000000)); // Como print não suporta zeros à esquerda, usei sprintf
      Serial.print(temp);
      
      Serial.print(" ");
      if (reading.isData)
      {
        Serial.print("Contem Dados ");
      }
      if (reading.isAnimal)
      {
        Serial.print("é de Animal ");
      }
      Serial.println();
      digitalWrite(buzzer, HIGH);
      delay(300);
    }
};

// instancia um objeto Rfid 134,
// definido com a classe de notificação acima e a classe serial de hardware
//
// Rfid134<HardwareSerial, RfidNotify> rfid(Serial1);
// Algumas placas arduino têm apenas uma porta serial de hardware, portanto, uma porta serial de software é necessária.
// comente a definição acima e descomente essas linhas
SoftwareSerial secondarySerial (TXD, RXD); // RX, TX (Inverte para leitura) // Leitor Serial Virtual RFID_Serial(8, ); //RX, TX  Virtual SoftwareSerial
Rfid134 <SoftwareSerial, RfidNotify> rfid (secondarySerial);

void setup(){
  pinMode(buzzer,OUTPUT);
  // devido a diferenças de design em (Software) SerialConfig que tornam o serial.begin
  // método inconsistente entre implementações, é necessário que o esboço
  // chame serial.begin () que é específico da plataforma
  Serial.begin(19200); // Monitor Serial PC
  Serial.println("Inicializando...");
  // hardware
  // Serial1.begin (9600, SERIAL_8N2); // ??
  // software ESP
  // secondarySerial.begin(9600, SWSERIAL_8N2);
  // software AVR
  // SoftwareSerial
  secondarySerial.begin(9600);  // Leitor Serial Virtual RFID_Serial(10,11); //TX, RX  Virtual SoftwareSerial
  rfid.begin();
  Serial.println("Monitor Serial Ok...");
  Serial.println("Lendo RFID WL-134...");
}
void loop(){
  digitalWrite(buzzer, LOW);
  rfid.loop();
}
/*
  Aviso: não suporta Tag HDX
  Modelo: WL-134
  Protocolo: FDX-B
  Leia-poder Chip: EM 4305 HITAG256 EM1001 TK4100
  Dimensão: 35x36mm
  Freqüência: 134.2 K
  Tensão: 5 ~ 9 V bateria ou alimentação LDO. usando DC-DC ou fonte de alimentação irá afetar a distância de leitura
  Corrente de trabalho: 120mA, 9 V
  Temperatura de trabalho:-40 ~ + 80C
  Antena indutância: 580uH
  Definições de pinos são como se segue:
  1 | + 5 V a + 9 V fonte de alimentação
  2 | RST_Redefinir, Baixo Nível eficaz
  3 | Número da porta de saída serial TX, 5 V nível TTL
  4 | GND

  L1| Antena 1
  L2| Antena 2 (360 V vpp)

  Leia o cartão distancereference lista:
  Comprimento uso 97x97mm praça antena distância de leitura do cartão são como se segue 2x12mm tubo de vidro é de cerca de 18 CM
  O diâmetro de 3 CM ear tag distância de leitura é de cerca de 36 CM

  Formato de Dados TX: (ASCII): Taxa de transmissão 9600, 8N2
  1:02 começar número (fixo)
  2:10 bit HEX formato ASCII número do cartão, LSB primeiro.
  3:4 bit HEX formato ASCII número do país, LSB primeiro:
  4: dados bandeira, 0 ou 1
  5: Aninal bandeira, 0 ou 1
  6,7 reseved.
  8: soma de verificação, todos os 26bit ACSII HEX XOR
  9: soma de verificação Bit A Bit invertido.
  10:03 número final (fixo)

  Por exemplo: no tag mostra: “900250000023921” (formato de Dezembro de 900 na parte da frente, então o número do cartão de 250000023921)
  Saída do módulo:  0231 37 31 41 39 32 35 33 41 33 34 38 33 30 30 31 30 30 30 30 30 30 30 30 30 3007 F8 03
  Igual ASCII: [1] 171A9253A34830010000000000?

  Nós podemos encontrar cartão nuber é 171A9253A3,número do País é de 483 (LSB Primeiro)
  Podemos traduzir esses números para Dezembro formato, número do cartão de igual: 250000023921,
  País número igual 900 E “31 37 31 41 39 32 35 33 41 33 34 38 33 30 30 31 30 30 30 30 30 30 30 30 30 30 ”feito todo o XOR caculate,
  nós temos a resposta é 07 (soma de verificaçãoResultado). F8 é 07's bit a bit invertido resultado.
  Se você precisa de um módulo conversor TTL para USB, por favor clique sigam o link e adicione
  Item ao carrinho de compras.
  Http://www.aliexpress.com/item/Info/33011842924.html
  Lista do pacote:
  10*134.2 Módulo Leitor
  10*97*97Antena
  1 * tag orelha
*/
