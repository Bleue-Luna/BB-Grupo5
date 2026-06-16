#include <SPI.h>
#include <MFRC522.h>

const byte numLeitores = 4;

const byte sdaPins[numLeitores] = {10, 7, 6, 5};
const byte rstPin = 9; 

MFRC522 mfrc522[numLeitores] = {
  MFRC522(sdaPins[0], rstPin),
  MFRC522(sdaPins[1], rstPin),
  MFRC522(sdaPins[2], rstPin),
  MFRC522(sdaPins[3], rstPin)
};

void setup() {
  Serial.begin(9600);   //iniciando monitor serial
  SPI.begin();          //iniciando barramento SPI do arduino

  Serial.println("Preparando os leitores...");
  for(uint8_t i = 0; i < numLeitores; i++) {
    pinMode(sdaPins[i], OUTPUT);
    digitalWrite(sdaPins[i], HIGH);
  }
  delay(50);

  Serial.println("Inicializando os leitores...");
  for (uint8_t i = 0; i < numLeitores; i++) {
    mfrc522[i].PCD_Init();
    //mfrc522[i].PCD_SetAntennaGain(mfrc522[i].RxGain_max);

    Serial.print(F("Leitor ["));
    Serial.print(i);
    Serial.print(F("] Firmware do chip: "));
    mfrc522[i].PCD_DumpVersionToSerial();
  }

  Serial.println("Aguardando tag...");
}

void loop() {
  //O arduino vai ficar girando nesse carrossel olhando um leitor por vez
  for (uint8_t i = 0; i < numLeitores; i++) {

    // Se não houver cartão neste leitor específico, vá para o próximo
    if (!mfrc522[i].PICC_IsNewCardPresent()) {
      continue;
    }

    // Se houver cartão, mas houve falha na leitura de seu serial, também pula.
    if (!mfrc522[i].PICC_ReadCardSerial()) {
      Serial.print(F("-> LEITOR ["));
      Serial.print(i);
      Serial.println(F("] falhou a ler uma tag."));
      continue;
    }

    Serial.print(F("-> LEITOR ["));
    Serial.print(i);
    Serial.println(F("] leu a tag com UID: "));
    // Imprime UID da tag em hexadecimal
    for (byte j = 0; j < mfrc522[i].uid.size; j++) {
      Serial.print(mfrc522[i].uid.uidByte[j] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522[i].uid.uidByte[j], HEX);
    }
    Serial.println();

    // Manda esta RFID dormir para que não trave o loop
    mfrc522[i].PICC_HaltA();
  }
  delay(50);
}