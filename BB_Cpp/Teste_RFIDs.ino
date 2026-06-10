// DEFINIÇÕES
#define DEBUG

// LIBRARIES
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <SPI.h>
#include <MFRC522.h>

// ==========================================
// --- GLOBAIS (RFID) ---
// ==========================================
const byte numReaders = 4;
const byte ssPins[] = {2, 3, 4, 5};
const byte resetPins[] = {7, 8, 9, 10};

MFRC522 mfrc522[numReaders];
String currentIDs[numReaders];

// ==========================================
// --- GLOBAIS (TELAS OLED E MULTIPLEXADOR) ---
// ==========================================
const byte numScreens = 4;
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); 

// Canais físicos pares
const byte oledChannels[] = {0, 2, 4, 6}; 

void tcaselect(uint8_t canal) {
  if (canal > 7) return;
  Wire.beginTransmission(0x70); // Endereço físico correto do multiplexador
  Wire.write(1 << canal);
  Wire.endTransmission();
}

// ==========================================
// --- FUNÇÕES DE DESENHO (OTIMIZADAS) ---
// ==========================================

// OVERLOAD 1: Para textos fixos (Economiza muita RAM e resolve o bug de sumir)
void printCentralizado(const char* texto, int y, int tamanho_fonte) {
  display.setTextSize(tamanho_fonte);
  int largura_texto = strlen(texto) * (6 * tamanho_fonte);
  int x = (SCREEN_WIDTH - largura_texto) / 2;
  display.setCursor(x, y);
  display.print(texto);
}

// OVERLOAD 2: Para as leituras do RFID (Mantém suporte a String só onde precisa)
void printCentralizado(String texto, int y, int tamanho_fonte) {
  display.setTextSize(tamanho_fonte);
  int largura_texto = texto.length() * (6 * tamanho_fonte);
  int x = (SCREEN_WIDTH - largura_texto) / 2;
  display.setCursor(x, y);
  display.print(texto);
}

void desenharTelaAguardando(int indice_tela) {
  tcaselect(oledChannels[indice_tela]); 
  
  display.clearDisplay();
  
  // Força cor de texto branco em fundo preto (Evita transparências bugadas)
  display.setTextColor(SH110X_WHITE, SH110X_BLACK); 
  
  // Retângulo arredondado encolhido em 2px (Foge da moldura de plástico da tela)
  display.drawRoundRect(2, 2, 124, 60, 4, SH110X_WHITE); 
  
  printCentralizado("TELA", 8, 1);
  
  // Cria o número da tela usando um char super leve em vez da pesada classe String
  char numStr[2] = {(char)('1' + indice_tela), '\0'};
  printCentralizado(numStr, 22, 4);
  
  printCentralizado("Aguardando...", 50, 1);
  
  display.display();
}

void desenharTelaLido(int indice_tela, String tagID) {
  tcaselect(oledChannels[indice_tela]); 
  
  display.clearDisplay();
  
  display.setTextColor(SH110X_WHITE, SH110X_BLACK); 
  display.drawRoundRect(2, 2, 124, 60, 4, SH110X_WHITE); 
  
  printCentralizado("LIDO!", 8, 1);
  
  char numStr[2] = {(char)('1' + indice_tela), '\0'};
  printCentralizado(numStr, 22, 4);
  
  printCentralizado(tagID, 50, 1);
  
  display.display();
}

// ==========================================
// --- SETUP ---
// ==========================================
void setup(){
  #ifdef DEBUG
  Serial.begin(9600);
  Serial.println(F("Comunicacao serial inicializada."));
  #endif

  Wire.begin();
  Wire.setClock(100000); 
  SPI.begin();

  // --- SETUP DOS LEITORES ---
  for(uint8_t i=0; i<numReaders; i++) {
    mfrc522[i].PCD_Init(ssPins[i], resetPins[i]);
    mfrc522[i].PCD_SetAntennaGain(MFRC522::PCD_RxGain::RxGain_max);
    delay(10);
  }

  // --- SETUP DAS TELAS ---
  for (uint8_t i=0; i<numScreens; i++) {
    tcaselect(oledChannels[i]);
    if(display.begin(0x3C, true)) {
      display.clearDisplay(); 
      display.display();      
    } else {
      #ifdef DEBUG
      Serial.print(F("Falha ao iniciar tela no canal "));
      Serial.println(oledChannels[i]);
      #endif
    }
  }

  for (uint8_t i=0; i<numScreens; i++) {
    desenharTelaAguardando(i);
  }

  #ifdef DEBUG
  Serial.println(F("--- END SETUP ---"));
  #endif
}

// ==========================================
// --- LOOP ---
// ==========================================
void loop() {
  bool changedValue = false;
  
  for (uint8_t i=0; i<numReaders; i++) {
    mfrc522[i].PCD_Init();
    String readRFID = "";
    
    if(mfrc522[i].PICC_IsNewCardPresent() && mfrc522[i].PICC_ReadCardSerial()) {
      readRFID = dump_byte_array(mfrc522[i].uid.uidByte, mfrc522[i].uid.size);
    }
    
    if(readRFID != currentIDs[i]) {
      currentIDs[i] = readRFID;
      changedValue = true;

      if (readRFID != "") {
        desenharTelaLido(i, readRFID);
      } else {
        desenharTelaAguardando(i);
      }
    }

    mfrc522[i].PICC_HaltA();
    mfrc522[i].PCD_StopCrypto1();
  }

  if(changedValue){
    #ifdef DEBUG
    for (uint8_t i=0; i<numReaders; i++) {
      Serial.print(F("Leitor ")); Serial.print(String(i));
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
    if (i < bufferSize - 1) uidStr += " "; 
  }
  uidStr.toUpperCase(); 
  return uidStr;
}