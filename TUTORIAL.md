# 📖 Artigo Tutorial: Como Construir e Jogar o BeatBlock

<p align="justify">
  Seja bem-vindo ao tutorial oficial do BeatBlock! Este material foi desenvolvido de forma didática e acessível para que educadores, terapeutas, makers e entusiastas possam replicar e utilizar este protótipo focado no estímulo de crianças com Transtorno do Espectro Autista (TEA).
</p>

---

## 🛠️ Pré-requisitos e Materiais

<p align="justify">
  Antes de iniciar a montagem, certifique-se de ter todos os componentes de hardware e ferramentas de software preparados para o projeto.
</p>

### 💻 Software Necessário
* **Arduino IDE:** Software utilizado para escrever e enviar o código para a placa Arduino[cite: 1].
* **Bibliotecas RFID (MFRC522):** Necessária para a comunicação com os leitores de cartões/tags[cite: 1].
* **Bibliotecas de Tela OLED (Adafruit SSD1306 / GFX):** Para gerenciar a interface gráfica das telas[cite: 1].

### 🔌 Componentes de Hardware
* **1x Placa Arduino Uno R3:** O cérebro do nosso tabuleiro[cite: 1].
* **1x Protoboard de 830 Pinos:** Para realizar as conexões elétricas de teste[cite: 1].
* **4x Módulos Leitores RFID RC522:** Responsáveis por identificar os blocos nos slots[cite: 1].
* **4x Telas OLED I2C:** Exibem o status de cada slot e feedbacks visuais[cite: 1].
* **1x Potenciômetro:** Utilizado para alternar dinamicamente os modos de jogo[cite: 1].
* **4x Resistores e Barras de Pinos:** Para suporte às conexões físicas[cite: 1].
* **40x Fios Jumper Coloridos:** Para interconectar todos os módulos[cite: 1].
* **5x Cubos Didáticos:** Blocos físicos com tags RFID internas que representam os instrumentos[cite: 1].

---

## 🏗️ Passo a Passo da Montagem e Configuração

### Passo 1: Preparação da Base e Barramento I2C
<p align="justify">
  Posicione o Arduino Uno e a protoboard lado a lado[cite: 1]. Como utilizaremos quatro telas OLED que compartilham a mesma comunicação I2C, crie linhas de barramento de dados (SDA e SCL) e de alimentação (5V e GND) na protoboard para facilitar a distribuição dos fios para todas as telas de forma organizada[cite: 1].
</p>

### Passo 2: Conexão dos Leitores RFID
<p align="justify">
  Cada um dos 4 slots do tabuleiro possui um leitor RFID RC522 posicionado internamente[cite: 1]. Conecte os pinos de dados SPI (MOSI, MISO e SCK) de todos os leitores em paralelo nos pinos correspondentes do Arduino, mas certifique-se de separar um pino digital exclusivo de "SDA/SS" para cada leitor, permitindo que o Arduino identifique qual slot está ativo[cite: 1].
</p>

### Passo 3: Programação do Arduino
<ol>
  <li>Conecte o Arduino Uno ao seu computador utilizando um cabo USB[cite: 1].</li>
  <li>Abra a <strong>Arduino IDE</strong> e certifique-se de instalar as bibliotecas necessárias para o RFID e displays OLED via Gerenciador de Bibliotecas[cite: 1].</li>
  <li>Cole o código-fonte do projeto na IDE, selecione a placa "Arduino Uno" e a porta COM correspondente[cite: 1].</li>
  <li>Clique em <strong>Carregar (Upload)</strong> e aguarde a inicialização das telas[cite: 1].</li>
</ol>

---

## 🕹️ Como Jogar na Prática

<table>
  <tr>
    <td width="50%" valign="top">
      <h4>🎵 Modo Musical Livre</h4>
      <p>1. Escolha de 1 a 4 cubos de instrumentos[cite: 1].<br>
      2. Escolha a face com o ritmo desejado para cima[cite: 1].<br>
      3. Encaixe no slot do tabuleiro para iniciar o som automaticamente[cite: 1].<br>
      4. Combine múltiplos cubos nos slots vizinhos para criar arranjos musicais exclusivos[cite: 1].</p>
    </td>
    <td width="50%" valign="top">
      <h4>😀 Modo das Emoções</h4>
      <p>1. Gire o potenciômetro até o limite para ativar a interface das emoções[cite: 1].<br>
      2. Observe a emoção exibida na tela principal[cite: 1].<br>
      3. O objetivo é sintonizar e encaixar os cubos cujos ritmos e sonoridades combinem e expressem o sentimento proposto[cite: 1].</p>
    </td>
  </tr>
</table>

> [!TIP]
> **Dica Pedagógica:** O jogo é totalmente em tempo real! Incentive a criança a girar os cubos ou trocá-los de lugar de forma livre para explorar novas texturas sonoras e associações afetivas[cite: 1].
