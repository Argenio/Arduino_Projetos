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

/* Constantes - conexão wi-fi e webserver */
const char* host = "Esp32 LoRa Receiver";
const char* ssid = "GerenteMax FT"; /* coloque aqui o nome da rede wi-fi que o ESP32 deve se conectar */
const char* password = "FFga10.123"; /* coloque aqui a senha da rede wi-fi que o ESP32 deve se conectar */
/*
 * O login e senha para acesso é admin e admin, respectivamente.
 * Isso pode ser mudado alterando-se as palavras “admin” na linha do código-fonte acima
 */
//const char* usuario = "admin";
//const char* senha = "admin";

/* Define da Banda - LoRa */
#define BAND    915E6  // você pode definir a banda aqui,Ex. 868E6,915E6

/* Variáveis globais */
int contador_ms = 0;
unsigned int counter = 0;
String rssi = "RSSI --";
String packSize = "--";
String packet ;
String ip ;
 
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
  Heltec.display->drawXbm(0,5,logo_width,logo_height,logo_bits);
  Heltec.display->display();
}

void LoRaData(){
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(0 , 15 , "Received "+ packSize + " bytes");
  Heltec.display->drawStringMaxWidth(0 , 26 , 128, packet);
  Heltec.display->drawString(0, 0, rssi);  
  Heltec.display->display();
}

void cbk(int packetSize) {
  packet ="";
  packSize = String(packetSize,DEC);
  for (int i = 0; i < packetSize; i++) { packet += (char) LoRa.read(); }
  rssi = "RSSI " + String(LoRa.packetRssi(), DEC) ;
  LoRaData();
}

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
    Heltec.display->drawString(0, 10, "Wait for incoming data...");
    Heltec.display->display();
    delay(3000);
     //LoRa.onReceive(cbk);
    LoRa.receive();
  
    Serial.begin(115200);
 
    /* Conecta-se a rede wi-fi */
    WiFi.begin(ssid, password);
    Serial.println("");
 
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(500);
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
    server.begin();
}
 
void loop(){
  server.handleClient();
  delay(1);
  contador_ms++;
  if (contador_ms >= 1000){
    Serial.println("Programa antes da atualizacao OTA");
    contador_ms = 0;
  }
  Heltec.display->clear();
  int packetSize = LoRa.parsePacket();
  if (packetSize) { cbk(packetSize);  }
  delay(10);
}
