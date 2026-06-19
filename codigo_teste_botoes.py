import serial
import pygame
import time

# ==========================================
# 1. INICIALIZAÇÃO DO ÁUDIO
# ==========================================
pygame.mixer.pre_init(44100, -16, 2, 512)
pygame.mixer.init()

canais_audio = [pygame.mixer.Channel(i) for i in range(4)]

# ==========================================
# 2. MAPA DE SONS (Organizado por Canal e Faixa)
# ==========================================
# Preencha com os caminhos corretos dos seus arquivos .wav
mapa_sons = {
    0: { # CANAL 1
        "T1": "sons/c1_faixa1.wav", "T2": "sons/c1_faixa2.wav",
        "T3": "sons/c1_faixa3.wav", "T4": "sons/c1_faixa4.wav",
        "T5": "sons/c1_faixa5.wav", "T6": "sons/c1_faixa6.wav"
    },
    1: { # CANAL 2
        "T1": "sons/c2_faixa1.wav", "T2": "sons/c2_faixa2.wav",
        "T3": "sons/c2_faixa3.wav", "T4": "sons/c2_faixa4.wav",
        "T5": "sons/c2_faixa5.wav", "T6": "sons/c2_faixa6.wav"
    },
    2: { # CANAL 3
        "T1": "sons/c3_faixa1.wav", "T2": "sons/c3_faixa2.wav",
        "T3": "sons/c3_faixa3.wav", "T4": "sons/c3_faixa4.wav",
        "T5": "sons/c3_faixa5.wav", "T6": "sons/c3_faixa6.wav"
    },
    3: { # CANAL 4
        "T1": "sons/c4_faixa1.wav", "T2": "sons/c4_faixa2.wav",
        "T3": "sons/c4_faixa3.wav", "T4": "sons/c4_faixa4.wav",
        "T5": "sons/c4_faixa5.wav", "T6": "sons/c4_faixa6.wav"
    }
}

# ==========================================
# 3. CONEXÃO SERIAL
# ==========================================
porta_usb = 'COM3' # Atualize para a porta correta

try:
    arduino = serial.Serial(porta_usb, 9600, timeout=0.1)
    print("=======================================")
    print("MESA DE SOM PRONTA! 🎛️ (Modo Botões)")
    print("=======================================")
except:
    print(f"ERRO: Não conectou na {porta_usb}. Feche o Monitor Serial da IDE!")
    exit()

# ==========================================
# 4. LOOP PRINCIPAL
# ==========================================
try:
    while True:
        if arduino.in_waiting > 0:
            linha = arduino.readline().decode('utf-8').strip()
            
            if ":" in linha:
                canal_str, comando = linha.split(":")
                
                try:
                    num_canal = int(canal_str[1]) - 1 # Converte "C1" para o índice 0
                except ValueError:
                    continue 

                # AÇÃO: Desligar som do canal
                if comando == "VAZIO":
                    print(f"[-] Canal {num_canal + 1} -> DESATIVADO")
                    canais_audio[num_canal].stop()
                    
                # AÇÃO: Tocar faixa do canal
                elif comando.startswith("T"):
                    # Verifica se a faixa existe no dicionário daquele canal
                    if comando in mapa_sons[num_canal]:
                        caminho_audio = mapa_sons[num_canal][comando]
                        print(f"[+] Canal {num_canal + 1} -> TOCANDO: {comando} ({caminho_audio})")
                        
                        try:
                            som = pygame.mixer.Sound(caminho_audio)
                            canais_audio[num_canal].play(som, loops=-1)
                        except FileNotFoundError:
                            print(f"[ERRO] Arquivo de som não encontrado: {caminho_audio}")
                    else:
                        print(f"[!] Comando {comando} não mapeado no Canal {num_canal + 1}.")

        time.sleep(0.01)

except KeyboardInterrupt:
    print("\nEncerrando sistema...")
    pygame.quit()
  
