# 🔌 Documentação Técnica e Esquemático de Conexões

<p align="justify">
  Este documento apresenta as especificações técnicas, a lógica de funcionamento de hardware e o mapeamento de pinos do protótipo <strong>BeatBlock</strong>, servindo como guia detalhado para engenharia e manutenção do circuito[.
</p>

---

## 🧠 Lógica de Funcionamento do Sistema

<ol>
  <li><strong>Processamento Central:</strong> A placa Arduino Uno R3 atua como a unidade central de processamento, gerenciando as leituras de entrada e atualizando as saídas visuais e sonoras simultaneamente.</li>
  <li><strong>Sensoriamento dos Slots:</strong> Os 4 Módulos Leitores RFID RC522 monitoram constantemente a presença das tags fixadas no interior dos cubos. Ao aproximar um cubo de um slot, o leitor decodifica o identificador único (UID) para determinar qual instrumento e ritmo foram inseridos.</li>
  <li><strong>Interface Visual Compartilhada:</strong> As 4 Telas OLED se comunicam de forma multiplexada ou individual utilizando um barramento de comunicação I2C compartilhado. Isso otimiza o uso de pinos do Arduino, permitindo exibir dados individuais de status para cada slot de maneira independente.</li>
  <li><strong>Controle de Modo:</strong> Um potenciômetro analógico realiza a leitura de tensão para alternar as instruções do sistema entre a reprodução livre e o Modo das Emoções.</li>
</ol>

---

## 📊 Matriz de Conexões (Pinout)

<p align="justify">
  A tabela abaixo detalha como os barramentos de pinos e componentes principais devem ser interligados à placa de desenvolvimento do Arduino Uno e à linha de alimentação da protoboard.
</p>

| Componente | Pino do Componente | Conexão no Arduino / Protoboard | Função Principal |
| :--- | :--- | :--- | :--- |
| **Módulos RFID (Todos)** | VCC | Linha Positiva da Protoboard (3.3V) | Alimentação dos Leitores |
| **Módulos RFID (Todos)** | GND | Linha de Terra da Protoboard (GND) | Aterramento do Circuito |
| **Módulos RFID (Todos)** | SCK / MOSI / MISO | Pinos Digitais SPI Padrão (D13, D11, D12) | Barramento de Dados Compartilhado |
| **RFID Slot 1 ao 4** | SDA (SS) | Pinos Digitais Exclusivos (Ex: D10, D9, D8, D7) | Seleção Individual de Leitura do Slot |
| **Telas OLED (Todas)** | VCC / GND | Linhas de Alimentação (5V / GND) | Alimentação das Interfaces Visuais |
| **Telas OLED (Todas)** | SDA | Pino Analógico A4 (ou SDA Dedicado) | Linha de Dados do Barramento I2C |
| **Telas OLED (Todas)** | SCL | Pino Analógico A5 (or SCL Dedicado) | Linha de Clock do Barramento I2C |
| **Potenciômetro** | Pino Central (Sinal) | Pino Analógico A0 | Leitura Analógica para Troca de Modos |

---

## 🗺️ Diagrama do Circuito

<p align="justify">
  Para auxiliar na correta disposição física dos componentes, pinos de identificação e jumpers na protoboard de 830 pinos, utilize a representação visual detalhada contida no repositório através do arquivo de imagem listado abaixo:
</p>

<p align="center">
  <img src="Foto do Circuito.png" width="850px" alt="Esquemático Geral do Circuito BeatBlock">
</p>

> [!NOTE]
> Certifique-se de conferir as soldas nas barras de pinos dos módulos RFID e das telas OLED para evitar mau contato nas trilhas da protoboard durante o manuseio dos cubos de jogo.

---

## 🎛️ Circuito Alternativo: Implementação com Push Buttons (MVP)

<p align="justify">
  Para a versão funcional implementada, o barramento de dados SPI (utilizado anteriormente pelo RFID) foi simplificado para leituras digitais diretas usando botões mecânicos. A lógica de ativação por nível lógico baixo (Low) garante estabilidade contra ruídos eletromagnéticos.
</p>

### 📊 Nova Matriz de Conexões para os Slots (Botões)

| Componente / Slot | Pino do Botão | Conexão no Arduino | Comportamento Lógico |
| :--- | :--- | :--- | :--- |
| **Slot 1 (Instrumento 1)** | Terminal A / Terminal B | GND / **Pino D2** | Solto: `HIGH` (5V) \| Pressionado: `LOW` (0V) |
| **Slot 2 (Instrumento 2)** | Terminal A / Terminal B | GND / **Pino D3** | Solto: `HIGH` (5V) \| Pressionado: `LOW` (0V) |
| **Slot 3 (Instrumento 3)** | Terminal A / Terminal B | GND / **Pino D4** | Solto: `HIGH` (5V) \| Pressionado: `LOW` (0V) |
| **Slot 4 (Instrumento 4)** | Terminal A / Terminal B | GND / **Pino D5** | Solto: `HIGH` (5V) \| Pressionado: `LOW` (0V) |

> [!NOTE]
> Os pinos digitais **[D2, D3, D4 e D5]** listados acima são sugestões padrão. Caso você tenha utilizado pinos diferentes na sua montagem final, lembre-se de alterar os valores nesta tabela e no código-fonte do projeto.

### 🧠 Fluxo Lógica de Operação (Botões)
