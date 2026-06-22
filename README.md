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
  Para alternar entre os modos presentes no <strong>BitBlock</strong>, basta girar o potenciômetro até o limite. Ao fazer isso, a interface mudará o comportamento do jogo.
</p>


## ⚠️ Problemas Enfrentados e Alterações no Sistema

<p align="justify">
  Durante a fase de desenvolvimento prático e testes de bancada do <strong>BitBlock</strong>, a equipe enfrentou desafios técnicos complexos que exigiram uma mudança estratégica no projeto de hardware. Embora a arquitetura ideal previsse a identificação dos cubos via sensores RFID RC522, o circuito final foi adaptado para operar utilizando <strong>botões físicos</strong> nos slots.

  A decisão de substituir os leitores RFID por botões mecânicos foi o resultado de muitas horas de debugging. Passamos pente fino atrás de pente fino e mesmo assim, os RFIDs não funcionavam mais sem motivo aparente. Nem com jumpers, nem com solda, nem com fios robustos. Um mistério. Tudo com continuidade e propriamente alimentado (com uma placa reguladora MB102).
  
  Professores, monitores, colegas de outros grupos, todos que avaliavam nosso circuito chegavam à mesma conclusão: do jeito que estava montado, era para funcionar. À tarde da quinta-feira decidimos levar a frente o nosso plano B, ao invés da seleção musical ser feita através de tags NFC e leitores, as músicas estariam em playlists e os botões serviriam para pular/dar play.
  
**Recontextualizamos os materiais que tínhamos disponíveis e conseguimos adaptar nosso sistema para que alcansasse os objetivos traçados pelo esboço inicial do projeto, mantendo a proposta lúdica, a lógica pedagógica e seu objetivo. Dessa forma, o protótipo mantém sua entrega de valor focada na acessibilidade e no estímulo sensorial para crianças com TEA.**
</p>

---

> [!IMPORTANT]
> **Nota de Desenvolvimento (MVP):** Os arquivos de esquemático original e o tutorial mantêm a documentação da arquitetura RFID como a visão de longo prazo para o produto. A implementação atual com botões representa a solução de engenharia adotada para a entrega de um MVP 100% funcional, estável e seguro.
---


> [!TIP]
> **O jogo é totalmente dinâmico!** Você pode trocar a face do cubo ou substituí-lo por outro a qualquer momento para mudar o som instantaneamente.


## 🔌 Circuito do Arduino:
<img width="356" height="371" alt="image" src="https://github.com/user-attachments/assets/9b95897b-8cdd-458b-9476-62062ee06078" />
<img width="815" height="371" alt="image" src="https://github.com/user-attachments/assets/12adfc12-76be-4d74-9c7f-ce1362fddf6e" />
<img width="430" height="255" alt="image" src="https://github.com/user-attachments/assets/e8907d4e-6b08-4020-93eb-d3e7fbdfa846" />
