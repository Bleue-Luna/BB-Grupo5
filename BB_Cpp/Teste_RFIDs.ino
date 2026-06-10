//DEFINIÇÕES
#define DEBUG

//LIBRARIES
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <MFRC522.h>

// --- GLOBAIS (RFID) ---
const byte numReaders = 4;
// Cada leitor tem seu SS (SDA)
const byte ssPins[] = {2, 3, 4, 5};
// AGORA CADA LEITOR TEM UM RESET SEPARADO! (Ajuste os números para os pinos que você usou)
const byte resetPins[] = {7, 8, 9, 10};

// Inicializa a array de instanciamentos de MFRC522
MFRC522 mfrc522[numReaders];
// Guarda os IDs atuais (se for "", não tem tag encostada)
String currentIDs[numReaders];

// --- GLOBAIS (TELA OLED E MULTIPLEXADOR) ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Função para mudar o canal do TCA9548A no hardware real
void tcaselect(uint8_t canal) {
  if (canal > 7) return;
  Wire.beginTransmission(0x70); // Endereço físico padrão do Multiplexador
  Wire.write(1 << canal);
  Wire.endTransmission();
}

// --- FUNÇÕES DE DESENHO (INTERFACE) ---
void printCentralizado(String texto, int y, int tamanho_fonte) {
  display.setTextSize(tamanho_fonte);
  int largura_texto = texto.length() * (6 * tamanho_fonte);
  int x = (SCREEN_WIDTH - largura_texto) / 2;
  display.setCursor(x, y);
  display.print(texto);
}

void desenharTelaAguardando(int indice_tela) {
  tcaselect(indice_tela); // Abre a porta do multiplexador
  
  // No hardware real, TODAS as telas têm o endereço 0x3C
  if(display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
    printCentralizado("TELA", 6, 1);
    printCentralizado(String(indice_tela + 1), 20, 4);
    printCentralizado("Aguardando...", 50, 1);
    display.display();
  }
}

void desenharTelaLido(int indice_tela, String tagID) {
  tcaselect(indice_tela); 
  
  if(display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
    printCentralizado("LIDO!", 6, 1);
    printCentralizado(String(indice_tela + 1), 20, 4);
    printCentralizado(tagID, 50, 1);
    display.display();
  }
}

void setup(){
  #ifdef DEBUG
  // Inicializa canais de comunicação serial com o PC
  Serial.begin(9600);
  Serial.println(F("Comunicacao serial inicializada."));
  #endif

  Wire.begin();
  // No hardware real, não precisamos baixar a velocidade do clock I2C
  Wire.setClock(100000); 

  SPI.begin();

  // --- SETUP DOS LEITORES ---
  for(uint8_t i=0; i<numReaders; i++) {
    // Inicializa o leitor combinando os arrays de SS e RESET
    mfrc522[i].PCD_Init(ssPins[i], resetPins[i]);

    // Set o ganho para o máx
    mfrc522[i].PCD_SetAntennaGain(MFRC522::PCD_RxGain::RxGain_max);

    #ifdef DEBUG
    // Dump some debug info para o monitor serial
    Serial.print(F("Leitor ")); Serial.print(i);
    Serial.print(F(" inicializado. SS: ")); Serial.print(ssPins[i]);
    Serial.print(F(" | RST: ")); Serial.print(resetPins[i]);
    Serial.print(F(". Forca antena: ")); Serial.print(mfrc522[i].PCD_GetAntennaGain());
    Serial.print(F(". Versao: "));
    mfrc522[i].PCD_DumpVersionToSerial();
    #endif

    delay(10);
  }

  // --- SETUP DAS TELAS ---
  for (uint8_t i=0; i<numReaders; i++) {
    desenharTelaAguardando(i);
  }

  #ifdef DEBUG
  Serial.println(F("--- END SETUP ---"));
  #endif
}

void loop() {
  bool changedValue = false;
  
  // Loop por cada leitor
  for (uint8_t i=0; i<numReaders; i++) {
    // Inicialize o sensor (Isso é o segredo para detectar quando a tag é retirada!)
    mfrc522[i].PCD_Init();

    String readRFID = "";
    
    // Se o sensor detectar uma tag e conseguir ler
    if(mfrc522[i].PICC_IsNewCardPresent() && mfrc522[i].PICC_ReadCardSerial()) {
      readRFID = dump_byte_array(mfrc522[i].uid.uidByte, mfrc522[i].uid.size);
    }
    
    // Se a leitura atual for diferente da última leitura conhecida (Tag encostou ou tag saiu)
    if(readRFID != currentIDs[i]) {
      currentIDs[i] = readRFID;
      changedValue = true;

      // ATUALIZA A TELA IMEDIATAMENTE
      if (readRFID != "") {
        // Tag encostou
        desenharTelaLido(i, readRFID);
      } else {
        // Tag saiu
        desenharTelaAguardando(i);
      }
    }

    // Parar PICC
    mfrc522[i].PICC_HaltA();
    // Parar encript on PCD
    mfrc522[i].PCD_StopCrypto1();
  }

  // Se a flag de changeValue foi setada, fazemos o print debug
  if(changedValue){
    #ifdef DEBUG
    for (uint8_t i=0; i<numReaders; i++) {
      Serial.print(F("Leitor ")); Serial.print(String(i));
      Serial.print(F(" (Pino ")); Serial.print(String((ssPins[i])));
      Serial.print(F(") tag: "));
      Serial.println(currentIDs[i] == "" ? "NENHUMA" : currentIDs[i]);
    }
    Serial.println(F("---"));
    #endif
  }
}

// ============== FUNÇÕES AUXILIARES ==============
String dump_byte_array(byte *buffer, byte bufferSize) {
  String uidStr = "";
  for (byte i = 0; i < bufferSize; i++) {
    if(buffer[i] < 0x10) uidStr += "0";
    uidStr += String(buffer[i], HEX);
    // Adiciona um espaço entre os blocos (menos no último) pra ficar mais legível na tela
    if (i < bufferSize - 1) uidStr += " "; 
  }
  uidStr.toUpperCase(); 
  return uidStr;
}