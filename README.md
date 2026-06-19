## 🎲 Como o Jogo Funciona?

<p align="justify">
  O projeto consiste em um jogo musical e interativo projetado especialmente para crianças com TEA (Transtorno do Espectro Autista). A dinâmica é simples, altamente intuitiva e baseada em estímulos táteis e blocos físicos.
</p>

---

### 🧩 Os Componentes

<table>
  <tr>
    <td width="50%" valign="top">
      <h4>🎲 Os Cubos</h4>
      <p>O jogo possui <strong>5 cubos</strong> no total. Cada cubo representa um <strong>instrumento musical diferente</strong>, e cada face desse cubo possui um <strong>ritmo específico</strong> impresso.</p>
    </td>
    <td width="50%" valign="top">
      <h4>🎛️ O BitBlock</h4>
      <p>É o tabuleiro/mesa central do jogo. Possui <strong>4 slots disponíveis</strong> para encaixar e identificar os cubos.</p>
    </td>
  </tr>
</table>

---

### 🕹️ Passo a Passo para Jogar

<ol>
  <li><strong>Escolha os cubos:</strong> O jogador escolhe de 1 a 4 cubos para iniciar a partida.</li>
  <li><strong>Selecione o ritmo:</strong> Escolha qual face (ritmo) do cubo você quer deixar virada para cima.</li>
  <li><strong>Encaixe no slot:</strong> Insira o cubo em um dos slots vazios do tabuleiro. A música começará a ser reproduzida automaticamente!</li>
  <li><strong>Crie sua mistura:</strong> Adicione outros cubos nos slots restantes para combinar os instrumentos e criar uma música única.</li>
</ol>

---

## 🕹️ Como Alternar entre os Modos?

<p align="justify">
  Para alternar entre os modos presentes no <strong>BeatBlock</strong>, basta girar o potenciômetro até o limite. Ao fazer isso, a interface mudará o comportamento do jogo.
</p>

## 🔄 Engenharia e Adaptações de Hardware: De RFID para Botões

<p align="justify">
  Durante a fase de desenvolvimento prático e testes de bancada do <strong>BeatBlock</strong>, a equipe enfrentou desafios técnicos complexos que exigiram uma mudança estratégica no projeto de hardware. Embora a arquitetura ideal previsse a identificação dos cubos via sensores RFID RC522, o circuito final foi adaptado para operar utilizando <strong>botões físicos (push buttons)</strong> nos slots.
</p>

---

### ⚠️ Desafios Enfrentados com o RFID

<p align="justify">
  A decisão de substituir os leitores RFID por botões mecânicos foi fundamentada nos seguintes motivos:
</p>

<ul>
  <li><strong>Conflitos no Barramento SPI:</strong> O gerenciamento simultâneo de 4 leitores RFID compartilhando as mesmas linhas de dados do Arduino Uno apresentou alta complexidade de software, gerando atrasos na leitura e falsos positivos.</li>
  <li><strong>Problemas de Alimentação:</strong> Instabilidade na alimentação de 3.3V / Problemas de mau contato crônico na protoboard / Queima de um dos módulos durante as soldas.</li>
</ul>

---

### 🎯 O Impacto na Experiência do Usuário

<p align="justify">
  Apesar da substituição dos componentes internos, é importante destacar que <strong>a dinâmica lúdica, a lógica pedagógica e o objetivo do jogo permaneceram rigorosamente os mesmos</strong>. Os botões físicos foram posicionados estrategicamente no fundo de cada slot para que o próprio peso do cubo (ou o ato de encaixá-lo) acione o mecanismo. Dessa forma, o protótipo mantém sua entrega de valor focada na acessibilidade e no estímulo sensorial para crianças com TEA.
</p>

---

> [!IMPORTANT]
> **Nota de Desenvolvimento (MVP):** Os arquivos de esquemático original e o tutorial mantêm a documentação da arquitetura RFID como a visão de longo prazo para o produto. A implementação atual com botões representa a solução de engenharia adotada para a entrega de um MVP 100% funcional, estável e seguro.
---


> [!TIP]
> **O jogo é totalmente dinâmico!** Você pode trocar a face do cubo ou substituí-lo por outro a qualquer momento para mudar o som instantaneamente.


## 🔌 Circuito do Arduino:
<img src="Captura de Tela 2026-06-10 às 15.39.01.png" width="400px"></img>
<img width="356" height="371" alt="image" src="https://github.com/user-attachments/assets/9b95897b-8cdd-458b-9476-62062ee06078" />
<img width="815" height="371" alt="image" src="https://github.com/user-attachments/assets/12adfc12-76be-4d74-9c7f-ce1362fddf6e" />
<img width="430" height="255" alt="image" src="https://github.com/user-attachments/assets/e8907d4e-6b08-4020-93eb-d3e7fbdfa846" />




