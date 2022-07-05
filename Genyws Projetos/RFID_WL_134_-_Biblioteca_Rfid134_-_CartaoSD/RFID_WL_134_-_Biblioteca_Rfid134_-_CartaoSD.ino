#include <SoftwareSerial.h>
#include <Rfid134.h>
#include <SPI.h>
#include <SD.h>

// Definição de Portas Arduino Uno
#define pinCartaoSD 10
#define RXD 9 // Pino  de Escrita de Dados (Não Utilizamos nesse Modulo)
#define TXD 8 // Pino de Leitura de Dados do Modulo RFID WL-134 // Número da porta de saída serial TX, 5V nível TTL
#define RST 7 // Pino de Reset do Modulo RFID WL-134 // RST_Redefinir, Baixo Nível eficacia
#define buzzer 6 // Pino do Buzzer para ouvir que houve leitura
/* CartaoSD Pinos Usados
 ** SDCS - pin 10
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
*/
File arqDados; // Objeto do Cartão SD
String nome; // Variavel lida no Arquivo de Configuração.txt

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

    static void OnPacketRead(const Rfid134Reading& reading) // Leitura do Pacote de Dados RFID
    {

      // Criar Arquivo no SD
      arqDados = SD.open("dataLog.csv", FILE_WRITE); // Cria / Abre arquivo .txt
      if (!arqDados) {
        Serial.println("Nao foi possivel abrir o arquivo dataLog.csv!");
        while (1);
      }
      char temp[8];
      Serial.print("TAG: ");
      sprintf(temp, "%03u", reading.country); // Como print não suporta zeros à esquerda, usei sprintf
      Serial.print(temp);
      arqDados.print("TAG: ;");
      arqDados.print(temp);
      // uma vez que sprintf com AVR não suporta uint64_t (llu / lli), use /% trick para
      sprintf(temp, "%06lu", static_cast<uint32_t>(reading.id / 1000000)); // Como print não suporta zeros à esquerda, usei sprintf
      Serial.print(temp);
      arqDados.print(temp);
      sprintf(temp, "%06lu", static_cast<uint32_t>(reading.id % 1000000)); // Como print não suporta zeros à esquerda, usei sprintf
      Serial.print(temp);
      arqDados.print(temp);
      Serial.println(" #");
      Serial.print("Pais Cod.: ");
      arqDados.print("; Pais Cod.: ;");
      sprintf(temp, "%03u", reading.country); // Como print não suporta zeros à esquerda, usei sprintf
      Serial.print(temp);
      arqDados.print(temp);

      Serial.print(" ");
      Serial.print("ID.: ");
      arqDados.print("; ID.: ;");
      // uma vez que sprintf com AVR não suporta uint64_t (llu / lli), use /% trick para
      sprintf(temp, "%06lu", static_cast<uint32_t>(reading.id / 1000000)); // Como print não suporta zeros à esquerda, usei sprintf
      Serial.print(temp);
      arqDados.print(temp);
      sprintf(temp, "%06lu", static_cast<uint32_t>(reading.id % 1000000)); // Como print não suporta zeros à esquerda, usei sprintf
      Serial.print(temp);
      arqDados.print(temp);

      Serial.print(" ");
      if (reading.isData)
      {
        Serial.print("Contem Dados ");
        arqDados.print("; Contem Dados");
      }
      if (reading.isAnimal)
      {
        Serial.print("Tag de Animal ");
        arqDados.print("; Tag de Animal ");
      }
      arqDados.print("; Dados gravados por: ");
      arqDados.print(";");
      arqDados.print(nome); // Variavel carregada atraves do Arquivo de Configuração
      arqDados.println();
      Serial.println();
      digitalWrite(buzzer, HIGH);
      delay(300);
      arqDados.close();
    }
};

// instancia um objeto Rfid 134,
// definido com a classe de notificação acima e a classe serial de hardware
//
// Rfid134<HardwareSerial, RfidNotify> rfid(Serial1);
// Algumas placas arduino têm apenas uma porta serial de hardware, portanto, uma porta serial de software é necessária.
// comente a definição acima e descomente essas linhas
SoftwareSerial secondarySerial (TXD, RXD); // RX, TX (Inverte para leitura) // Leitor Serial Virtual RFID_Serial(10, 11); //RX, TX  Virtual SoftwareSerial
Rfid134 <SoftwareSerial, RfidNotify> rfid (secondarySerial);

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(pinCartaoSD, OUTPUT);
  // devido a diferenças de design em (Software) SerialConfig que tornam o serial.begin
  // método inconsistente entre implementações, é necessário que o esboço
  // chame serial.begin () que é específico da plataforma
  Serial.begin(19200); // Monitor Serial PC
  Serial.println("Inicializando...");
  while (!Serial);
  Serial.print("Iniciando cartao SD...");
  if (!SD.begin(pinCartaoSD)) { // Inicio o Cartão SD
    Serial.println("Erro de inicio do cartao SD!");
    while (1);
  }
  Serial.println("Cartao SD pronto...");
  lerConfiguracao(); // Ler arquivo no SD
  // hardware
  // Serial1.begin (9600, SERIAL_8N2); // ??
  // software ESP
  // secondarySerial.begin(9600, SWSERIAL_8N2);
  // software AVR
  // SoftwareSerial
  secondarySerial.begin(9600);  // Leitor Serial Virtual RFID_Serial(10,11); //TX, RX  Virtual SoftwareSerial
  rfid.begin();
  Serial.println();
  Serial.println("Monitor Serial Ok...");
  Serial.println("Lendo RFID WL-134...");
}
void loop() {
  digitalWrite(buzzer, LOW);
  rfid.loop();
}

void lerConfiguracao() {
  File arqConfig;

  arqConfig = SD.open("config.txt"); // arquivo txt no Cartão SD
  if (arqConfig) {
    Serial.println("Lendo Arquivo: config.txt:");

    String cVar   = "";
    String cValor = "";
    bool lendoValor = false;
    bool fimLinha = false;

    while (arqConfig.available()) {
      char cLido = arqConfig.read();
      Serial.write(cLido);

      if (lendoValor) {
        if (cLido == 13) {
          fimLinha = true;
        } else {
          cValor += cLido;
        }
      } else {
        //Lendo nome da variavel
        if (cLido == ':') {
          lendoValor = true;
        } else if (cLido == 13) {
          fimLinha = true;
        } else {
          if (cLido != 10) cVar += cLido;  //Ignora o char= 10 (CR)
        }
      }

      if (fimLinha || !arqConfig.available()) {
        cVar.trim();

        //******* Grava variaveis de configuração ********
        if (cVar == "nome") {
          nome = cValor; // Coleta o seu Nome do Cartão SD
        }
        //***********************************************

        cVar   = "";
        cValor = "";
        lendoValor = false;
        fimLinha   = false;
      }
    }

    arqConfig.close();
  } else {
    Serial.println("Arquivo config.txt nao encontrado ou não pode ser Aberto!");
  }
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
