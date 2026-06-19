# 📖 Artigo Tutorial: Como Construir e Jogar o BeatBlock

<p align="justify">
  Seja muito bem-vindo ao tutorial oficial do BeatBlock! Este material foi desenvolvido de forma didática e acessível para que educadores, terapeutas, makers e entusiastas possam replicar e utilizar este protótipo focado no estímulo de crianças com Transtorno do Espectro Autista (TEA).
</p>

---

## 🛠️ Pré-requisitos e Materiais

<p align="justify">
  Antes de iniciar a montagem, certifique-se de ter todos os componentes de hardware e ferramentas de software preparados para o projeto.
</p>

### 💻 Software Necessário
* **Arduino IDE:** Software utilizado para escrever e enviar o código para a placa Arduino.
* **Bibliotecas RFID (MFRC522):** Necessária para a comunicação com os leitores de cartões/tags.
* **Bibliotecas de Tela OLED (Adafruit SSD1306 / GFX):** Para gerenciar a interface gráfica das telas.

### 🔌 Componentes de Hardware
* **1x Placa Arduino Uno R3:** O cérebro do nosso tabuleiro.
* **1x Protoboard de 830 Pinos:** Para realizar as conexões elétricas de teste.
* **4x Módulos Leitores RFID RC522:** Responsáveis por identificar os blocos nos slots.
* **4x Telas OLED I2C:** Exibem o status de cada slot e feedbacks visuais.
* **1x Potenciômetro:** Utilizado para alternar dinamicamente os modos de jogo.
* **4x Resistores e Barras de Pinos:** Para suporte às conexões físicas.
* **40x Fios Jumper Coloridos:** Para interconectar todos os módulos.
* **5x Cubos Didáticos:** Blocos físicos com tags RFID internas que representam os instrumentos.

---

## 🏗️ Passo a Passo da Montagem e Configuração

### Passo 1: Preparação da Base e Barramento I2C
<p align="justify">
  Posicione o Arduino Uno e a protoboard lado a lado. Como utilizaremos quatro telas OLED que compartilham a mesma comunicação I2C, crie linhas de barramento de dados (SDA e SCL) e de alimentação (5V e GND) na protoboard para facilitar a distribuição dos fios para todas as telas de forma organizada.
</p>

### Passo 2: Conexão dos Leitores RFID
<p align="justify">
  Cada um dos 4 slots do tabuleiro possui um leitor RFID RC522 posicionado internamente. Conecte os pinos de dados SPI (MOSI, MISO e SCK) de todos os leitores em paralelo nos pinos correspondentes do Arduino, mas certifique-se de separar um pino digital exclusivo de "SDA/SS" para cada leitor, permitindo que o Arduino identifique qual slot está ativo.
</p>

### Passo 3: Programação do Arduino
<ol>
  <li>Conecte o Arduino Uno ao seu computador utilizando um cabo USB.</li>
  <li>Abra a <strong>Arduino IDE</strong> e certifique-se de instalar as bibliotecas necessárias para o RFID e displays OLED via Gerenciador de Bibliotecas.</li>
  <li>Cole o código-fonte do projeto na IDE, selecione a placa "Arduino Uno" e a porta COM correspondente.</li>
  <li>Clique em <strong>Carregar (Upload)</strong> e aguarde a inicialização das telas.</li>
</ol>

---

## 🕹️ Como Jogar na Prática

<table>
  <tr>
    <td width="50%" valign="top">
      <h4>🎵 Modo Musical Livre</h4>
      <p>1. Escolha de 1 a 4 cubos de instrumentos.<br>
      2. Escolha a face com o ritmo desejado para cima.<br>
      3. Encaixe no slot do tabuleiro para iniciar o som automaticamente.<br>
      4. Combine múltiplos cubos nos slots vizinhos para criar arranjos musicais exclusivos.</p>
    </td>
    <td width="50%" valign="top">
      <h4>😀 Modo das Emoções</h4>
      <p>1. Gire o potenciômetro até o limite para ativar a interface das emoções.<br>
      2. Observe a emoção exibida na tela principal.<br>
      3. O objetivo é sintonizar e encaixar os cubos cujos ritmos e sonoridades combinem e expressem o sentimento proposto.</p>
    </td>
  </tr>
</table>

> [!TIP]
> **Dica Pedagógica:** O jogo é totalmente em tempo real! Incentive a criança a girar os cubos ou trocá-los de lugar de forma livre para explorar novas texturas sonoras e associações afetivas.
