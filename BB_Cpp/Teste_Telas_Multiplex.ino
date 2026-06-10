// #include <Wire.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SH110X.h> // Biblioteca atualizada para o SH1106

// #define TCA_ADDR 0x70      // Endereço padrão do TCA9548A
// #define OLED_ADDR 0x3C     // Endereço padrão do SH1106

// #define SCREEN_WIDTH 128
// #define SCREEN_HEIGHT 64
// #define OLED_RESET -1

// // Cria o objeto do display específico para o SH1106G
// Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// int channels[] = {0, 2, 4, 6};

// void tcaSelect(uint8_t channel) {
//   if (channel > 7) return;

//   Wire.beginTransmission(TCA_ADDR);
//   Wire.write(1 << channel);
//   Wire.endTransmission();
// }

// void setup() {
//   Wire.begin();
//   Serial.begin(9600);

//   for (int i = 0; i < 4; i++) {
//     int ch = channels[i];

//     tcaSelect(ch);
//     delay(100);

//     // Inicialização ajustada para o SH1106
//     if (!display.begin(OLED_ADDR, true)) {
//       Serial.print("OLED falhou no canal ");
//       Serial.println(ch);
//       continue;
//     }

//     display.clearDisplay();
//     display.setTextSize(2);
//     display.setTextColor(SH110X_WHITE); // Constante de cor atualizada

//     display.setCursor(0, 0);
//     display.print("OLED");

//     display.setCursor(0, 25);
//     display.print("CH ");
//     display.print(ch);

//     display.display();

//     Serial.print("OLED OK no canal ");
//     Serial.println(ch);
//   }
// }

// void loop() {
//   for (int i = 0; i < 4; i++) {
//     int ch = channels[i];

//     tcaSelect(ch);

//     display.clearDisplay();
//     display.setTextSize(1);
//     display.setTextColor(SH110X_WHITE); // Constante de cor atualizada

//     display.setCursor(0, 0);
//     display.print("TCA9548A test");

//     display.setCursor(0, 20);
//     display.print("Screen channel: ");
//     display.print(ch);

//     display.setCursor(0, 40);
//     display.print("Millis: ");
//     display.print(millis() / 1000);

//     display.display();

//     delay(500);
//   }
// }