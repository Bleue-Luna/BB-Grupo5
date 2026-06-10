#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <MFRC522.h>

// --- CONFIGURAÇÃO DOS RFIDs ---
#define RST_PIN -1 

#define SS_PIN_1 5
#define SS_PIN_2 4
#define SS_PIN_3 3
#define SS_PIN_4 2

MFRC522 leitor1(SS_PIN_1, RST_PIN);
MFRC522 leitor2(SS_PIN_2, RST_PIN);
MFRC522 leitor3(SS_PIN_3, RST_PIN);
MFRC522 leitor4(SS_PIN_4, RST_PIN);

// --- CONFIGURAÇÃO DAS TELAS OLED ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
// Instância única com a biblioteca Adafruit GFX para economizar RAM
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Vetor com os 4 endereços falsos
const uint8_t oled_addrs[4] = {0x3C, 0x3D, 0x3E, 0x3F};

// Variáveis de tempo
unsigned long tempoLeitura[4] = {0, 0, 0, 0};
bool tagLida[4] = {false, false, false, false};
const unsigned long TEMPO_VISIVEL = 2000;

// --- FUNÇÃO PARA CENTRALIZAR TEXTO AUTOMATICAMENTE ---
void printCentralizado(String texto, int y, int tamanho_fonte) {
  display.setTextSize(tamanho_fonte);
  // A fonte padrão do Adafruit_GFX tem 6 pixels de largura (contando o espaço)
  int largura_texto = texto.length() * (6 * tamanho_fonte); 
  int x = (SCREEN_WIDTH - largura_texto) / 2; // Calcula a margem esquerda
  display.setCursor(x, y);
  display.print(texto);
}

void desenharTelaAguardando(int indice_tela, int num_leitor) {
  if(display.begin(SSD1306_SWITCHCAPVCC, oled_addrs[indice_tela])) {
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
    printCentralizado("TELA", 6, 1);
    printCentralizado(String(num_leitor), 20, 4);
    printCentralizado("Aguardando...", 50, 1);
    display.display();
  }
}

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.setClock(31000); 
  
  SPI.begin(); 

  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);
  delay(50); 

  leitor1.PCD_Init();
  leitor2.PCD_Init();
  leitor3.PCD_Init();
  leitor4.PCD_Init();

  // --- TELA INICIAL (AGUARDANDO TAG) ---
  for (int i = 0; i < 4; i++) {
    if(display.begin(SSD1306_SWITCHCAPVCC, oled_addrs[i])) {
      display.clearDisplay();
      display.setTextColor(WHITE);
      
      // Desenha a moldura (x, y, largura, altura, cor)
      display.drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
      
      // Escreve os textos centralizados
      printCentralizado("TELA", 6, 1);                 // Pequeno no topo
      printCentralizado(String(i + 1), 20, 4);         // Número GIGANTE no meio
      printCentralizado("Aguardando...", 50, 1);       // Pequeno na base
      
      display.display();
    }
  }
}

void checarLeitor(MFRC522 &leitor, int indice_tela, int num_leitor) {
  // Dispara as duas verificações (se é tag nova OU se a tag velha continua ali)
  bool presente = leitor.PICC_IsNewCardPresent();
  bool leuSerial = leitor.PICC_ReadCardSerial();

  if (presente || leuSerial) {
    // Como a tag está aqui, renovamos o cronômetro o tempo todo!
    tempoLeitura[indice_tela] = millis();

    // SÓ DESENHA NA TELA SE ELA ESTIVER NO MODO "AGUARDANDO..."
    // Isso evita que a tela fique piscando loucamente enquanto você segura a tag
    if (tagLida[indice_tela] == false) {
      
      String conteudo = "";
      for (byte i = 0; i < leitor.uid.size; i++) {
        conteudo.concat(String(leitor.uid.uidByte[i] < 0x10 ? " 0" : " "));
        conteudo.concat(String(leitor.uid.uidByte[i], HEX));
      }
      conteudo.toUpperCase();
      conteudo.trim();

      Serial.print("Leitor ");
      Serial.print(num_leitor);
      Serial.print(" leu a TAG: ");
      Serial.println(conteudo);

      display.begin(SSD1306_SWITCHCAPVCC, oled_addrs[indice_tela]);
      display.clearDisplay();
      display.setTextColor(WHITE);
      display.drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
      
      printCentralizado("LIDO!", 6, 1);                
      printCentralizado(String(num_leitor), 20, 4);    
      printCentralizado(conteudo, 50, 1);              
      
      display.display(); 

      // Avisa ao sistema que a tela agora está ocupada com essa ID
      tagLida[indice_tela] = true;
    }
  }
}

void loop() {
  checarLeitor(leitor1, 0, 1);
  checarLeitor(leitor2, 1, 2); 
  checarLeitor(leitor3, 2, 3); 
  checarLeitor(leitor4, 3, 4);
  for (int i = 0; i<4; i++) {
    if (tagLida[i] == true && (millis() - tempoLeitura[i] > TEMPO_VISIVEL)) {
      tagLida[i] = false;
      desenharTelaAguardando(i, i + 1);
    }
  }
}