/*  Programa para ESP32 Heltec LoRa Com Atualização OTA OLED SENDER*/
/*
  This is a simple example show the Heltec.LoRa sended data in OLED.

  The onboard OLED display is SSD1306 driver and I2C interface. In order to make the
  OLED correctly operation, you should output a high-low-high(1-0-1) signal by soft-
  ware to OLED's reset pin, the low-level signal at least 5ms.

  OLED pins to ESP32 GPIOs via this connecthin:
  OLED_SDA -- GPIO4
  OLED_SCL -- GPIO15
  OLED_RST -- GPIO16
*/

#include "heltec.h"
#include "images.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>
#include <SoftwareSerial.h>
#include <Rfid134.h>

/* Variáveis globais */
int contador_ms = 0;
unsigned int counter = 0;
String rssi = "RSSI --";  // REDE LORA
String packSize = "--";   // REDE LORA
String packet ;           // REDE LORA
String TAGText;           // LEITURA CHIP RFID

/* Constantes - conexão wi-fi e webserver */
const char* host = "Esp32 LoRa Sender"; // Nome do Dispositivo // webserver
const char* ssid = "GerenteMax FT";     // REDE WIFI // coloque aqui o nome da rede wi-fi que o ESP32 deve se conectar */
const char* password = "FFga10.123";    // REDE WIFI // coloque aqui a senha da rede wi-fi que o ESP32 deve se conectar */
String ip ;                             // REDE WIFI
const char* usuario = "admin";          // Servidor OTA HTML // webserver
const char* senha = "admin";            // Servidor OTA HTML // webserver

/* Defines */
/* Define da Banda - LoRa */
#define BAND    915E6   // REDE LORA // você pode definir a banda aqui,Ex. 868E6,915E6
#define RXD 22          // REDE LORA // Pino  de Escrita de Dados (Não Utilizamos nesse Modulo)
#define TXD 0           // REDE LORA // Pino de Leitura de Dados do Modulo RFID WL-134
#define RST 19          // REDE LORA // Pino de Reset do Modulo RFID WL-134


/* Webserver para se comunicar via browser com ESP32  */
WebServer server(80);
/* Códigos da página que será aberta no browser
   (quando comunicar via browser com o ESP32)
   Esta página exigirá um login e senha, de modo que somente
   quem tenha estas informações consiga atualizar o firmware
   do ESP32 de forma OTA */
const char* loginIndex =
  "<form name='loginForm'>"
  "<table width='20%' bgcolor='A09F9F' align='center'>"
  "<tr>"
  "<td colspan=2>"
  "<center><font size=4><b>ESP32 Heltec LoRa - identifique-se</b></font></center>"
  "<br>"
  "</td>"
  "<br>"
  "<br>"
  "</tr>"
  "<td>Login:</td>"
  "<td><input type='text' size=25 name='userid'><br></td>"
  "</tr>"
  "<br>"
  "<br>"
  "<tr>"
  "<td>Senha:</td>"
  "<td><input type='Password' size=25 name='pwd'><br></td>"
  "<br>"
  "<br>"
  "</tr>"
  "<tr>"
  "<td><input type='submit' onclick='check(this.form)' value='Identificar'></td>"
  "</tr>"
  "</table>"
  "</form>"
  "<script>"
  "function check(form)"
  "{"
  "if(form.userid.value=='admin'&& form.pwd.value=='admin')"
  /*
    O login e senha para acesso é admin e admin, respectivamente.
    Isso pode ser mudado alterando-se as palavras “admin” na linha do código-fonte acima
  */
  "{"
  "window.open('/serverIndex')"
  "}"
  "else"
  "{"
  " alert('Login ou senha inválidos')"
  "}"
  "}"
  "</script>";

const char* serverIndex =
  "<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>"
  "<form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>"
  "<input type='file' name='update'>"
  "<input type='submit' value='Update'>"
  "</form>"
  "<div id='prg'>Progresso: 0%</div>"
  "<script>"
  "$('form').submit(function(e){"
  "e.preventDefault();"
  "var form = $('#upload_form')[0];"
  "var data = new FormData(form);"
  " $.ajax({"
  "url: '/update',"
  "type: 'POST',"
  "data: data,"
  "contentType: false,"
  "processData:false,"
  "xhr: function() {"
  "var xhr = new window.XMLHttpRequest();"
  "xhr.upload.addEventListener('progress', function(evt) {"
  "if (evt.lengthComputable) {"
  "var per = evt.loaded / evt.total;"
  "$('#prg').html('Progresso: ' + Math.round(per*100) + '%');"
  "}"
  "}, false);"
  "return xhr;"
  "},"
  "success:function(d, s) {"
  "console.log('Sucesso!')"
  "},"
  "error: function (a, b, c) {"
  "}"
  "});"
  "});"
  "</script>";

void logo()
{
  Heltec.display->clear();
  Heltec.display->drawXbm(0, 5, logo_width, logo_height, logo_bits);
  Heltec.display->display();
}

/* implementar uma classe de notificação, seus métodos de membro serão chamados */
class RfidNotify
{
  public:
    static void OnError(Rfid134_Error errorCode)
    {
      // veja Rfid134_Error para o significado do código
      Serial.println("");
      Serial.print("Com Error ");
      Serial.println(errorCode);
      TAGText = "Error :" + errorCode;
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
      //digitalWrite(buzzer, HIGH);
      TAGText = temp;
      delay(300);
      Heltec.display->clear();
      Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
      Heltec.display->setFont(ArialMT_Plain_10);
      Heltec.display->drawString(0, 0, "TAG: ");
      Heltec.display->drawString(0, 25, TAGText);
      Heltec.display->drawString(0, 50, "Lendo RFID WL-134...");
      Heltec.display->display();

      LoRa.beginPacket();
      LoRa.setTxPower(14, RF_PACONFIG_PASELECT_PABOOST);
      LoRa.print("TAG: ");
      LoRa.print(TAGText);
      LoRa.endPacket();
    }
    /*
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(1000);               // wait for a second
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
      delay(1000);               // wait for a second
    */
};

/*
    Instancia um objeto Rfid 134,
    definido com a classe de notificação acima e a classe serial de hardware
    Rfid134<HardwareSerial, RfidNotify> rfid(Serial1);

    Algumas placas arduino têm apenas uma porta serial de hardware, portanto, uma porta serial de software é necessária.
    comente a definição acima e descomente essas linhas
*/
SoftwareSerial secondarySerial (RXD, TXD); // RX, TX (Inverte para leitura) // Leitor Serial Virtual RFID_Serial(8, ); //RX, TX  Virtual SoftwareSerial
Rfid134 <SoftwareSerial, RfidNotify> rfid (secondarySerial);
/* hardware
  Serial1.begin (9600, SERIAL_8N2); // ??
   software ESP
  secondarySerial.begin(9600, SWSERIAL_8N2);
   software AVR
   SoftwareSerial
*/

void setup(void)
{

  //WIFI Kit series V1 not support Vext control
  /* Exibir Logo no OLED  */
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.Heltec.Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);

  Heltec.display->init();
  Heltec.display->flipScreenVertically();
  Heltec.display->setFont(ArialMT_Plain_10);
  logo();
  delay(1500);
  Heltec.display->clear();
  Heltec.display->drawString(0, 0, "Heltec LoRa OK!");
  Heltec.display->display();
  delay(2000);

  Serial.begin(115200); // Serial PC ESP32
  /* Conecta-se a rede wi-fi */
  WiFi.begin(ssid, password);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Conectando a WIFI:");
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Conectado a rede wi-fi ");
  Serial.println(ssid);
  Serial.print("IP obtido: ");
  Serial.println(WiFi.localIP());
  ip = WiFi.localIP().toString();
  Heltec.display->clear();
  Heltec.display->drawString(0, 0, "REDE : ");
  Heltec.display->drawString(40, 0, ssid);
  Heltec.display->drawString(0, 25, "IP : ");
  Heltec.display->drawString(40, 25, ip);
  Heltec.display->display();
  delay(10000);

  /* Usa MDNS para resolver o DNS */
  if (!MDNS.begin(host))
  {
    //http://esp32.local
    Serial.println("Erro ao configurar mDNS. O ESP32 vai reiniciar em 1s...");
    delay(1000);
    ESP.restart();
  }

  Serial.println("mDNS configurado e inicializado;");

  /* Configfura as páginas de login e upload de firmware OTA */
  server.on("/", HTTP_GET, []()
  {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", loginIndex);
  });

  server.on("/serverIndex", HTTP_GET, []()
  {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", serverIndex);
  });

  /* Define tratamentos do update de firmware OTA */
  server.on("/update", HTTP_POST, []()
  {
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    ESP.restart();
  }, []() {
    HTTPUpload& upload = server.upload();

    if (upload.status == UPLOAD_FILE_START)
    {
      /* Inicio do upload de firmware OTA */
      Serial.printf("Update: %s\n", upload.filename.c_str());
      if (!Update.begin(UPDATE_SIZE_UNKNOWN))
        Update.printError(Serial);
    }
    else if (upload.status == UPLOAD_FILE_WRITE)
    {
      /* Escrevendo firmware enviado na flash do ESP32 */
      if (Update.write(upload.buf, upload.currentSize) != upload.currentSize)
        Update.printError(Serial);
    }
    else if (upload.status == UPLOAD_FILE_END)
    {
      /* Final de upload */
      if (Update.end(true))
        Serial.printf("Sucesso no update de firmware: %u\nReiniciando ESP32...\n", upload.totalSize);
      else
        Update.printError(Serial);
    }
  });
  server.begin(); // Inicializa Servidro WEB
  Serial.println("Inicializando...");

  secondarySerial.begin(9600);  // Leitor Serial Virtual RFID_Serial(10,11); //TX, RX  Virtual SoftwareSerial
  //secondarySerial.begin(9600, SWSERIAL_8N2);
  rfid.begin(); // IniCializa o Leitor RFID
  Serial.println("Monitor Serial Ok...");
  Serial.println("Lendo RFID WL-134...");
  Heltec.display->clear();
  Heltec.display->drawString(0, 0, "Lendo RFID WL-134...");
  Heltec.display->display();
  delay(5000);
}

void loop() {
  server.handleClient();
  delay(1);
  /*
  contador_ms++;
  if (contador_ms >= 1000) {
    Serial.println("Programa antes da atualizacao OTA");
    contador_ms = 0;
  }
  */
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
