# Campo Minado em C 🧨

Este repositório contém uma implementação em **C** do clássico jogo Campo Minado (Minesweeper).  
O projeto foi escrito com fins **educacionais**, servindo como estudo de **estruturas de dados**, programação procedural e manipulação de arquivos.

---

## ✨ Principais conceitos abordados

| Conceito | Onde é utilizado | Por que é importante? |
|----------|-----------------|-----------------------|
| Matrizes dinâmicas (`int **`) | Representação do tabuleiro visível, tabuleiro oculto e coordenadas lidas | Exercita alocação/liberação dinâmica de memória |
| Recursão (Flood‑Fill) | `libera_campo` | Abre casas vizinhas vazias replicando o comportamento do jogo original |
| Geração pseudo‑aleatória | `insereBomba` com `rand()` | Sorteia posições das bombas de forma uniforme |
| Manipulação de arquivos texto | Módulo **log** (`campo_minado.txt`) | Salva cada jogada e o estado do tabuleiro para depuração |
| Encapsulamento de funcionalidades | Arquivos `matriz.*` e `log.*` | Separa responsabilidades, facilita manutenção/testes |

---

## 🏗️ Arquitetura de arquivos

```
.
├── main.c             # Contém função `main` e loop principal do jogo
├── matriz.c / matriz.h# Criação, inicialização, impressão e liberação de matrizes
├── log.c / log.h      # Criação e escrita do arquivo‑log da partida
└── README.md          # Este documento
```

> **Dica:** Os nomes dos ficheiros podem mudar; ajuste o `gcc` conforme necessário.

---

## 🎮 Como compilar e jogar

> Requer **GCC** ou outro compilador C99‑compatível em um sistema Unix‑like ou Windows (via MinGW).

```bash
# Compile
gcc main.c matriz.c log.c -o campo_minado

# Rode
./campo_minado
```

Durante a execução, escolha a dificuldade:

| Opção | Ordem da Matriz | Bombas |
|-------|-----------------|--------|
| 1 – Fácil   | 10×10 | 15  |
| 2 – Médio   | 20×20 | 60  |
| 3 – Difícil | 30×30 | 135 |

### Controles

- Digite `x,y` para revelar a casa (ex.: `3,7`).
- Digite `0` para sair da partida.

---

## 🔍 Detalhes de implementação

### 1. Geração e marcação das bombas

```c
void insereBomba(int **mat, int bomba, int ordem);
```

1. Cria coordenadas aleatórias até posicionar **N** bombas (`-1` na matriz escondida).  
2. Chama `vizinhaDasBombas` para incrementar o contador numérico nas casas adjacentes.

### 2. Abertura recursiva de casas

```c
void libera_campo(int **visivel, int **escondido,
                  int x, int y, int ordem, int *movimentos);
```

- Se a casa for **vazia (`0`)** abre‑a e propaga a chamada recursivamente para as 8 vizinhas.  
- Contabiliza o número de movimentos para verificar condição de vitória.

### 3. Condições de fim de jogo

| Função | Quando retorna **0** |
|--------|----------------------|
| `perdeu`  | Usuário revelou uma bomba |
| `ganhou`  | Casas abertas = `ordem² − bombas` |
| `sair`    | Usuário digitou `0` |

---

## 🗃️ Arquivo de log

Todas as ações do jogador são registradas em **`campo_minado.txt`**:

- Coordenadas reveladas
- Tabuleiro visível após cada jogada
- Mensagens de _Game over_ ou de vitória

Isso facilita **debugging** e análise posterior das partidas.

---

## 🧩 Possíveis melhorias

- Marcar bandeiras (flag) para indicar suspeitas de bombas  
- Interface gráfica (SDL, ncurses ou React Native via WebAssembly!)  
- Testes unitários com **CUnit**  
- Suporte a cores no terminal

---

## 📄 Licença

Distribuído sob a [MIT License](LICENSE). Sinta‑se livre para estudar, modificar e contribuir!

---

> Feito com 💻 & ☕ para fins acadêmicos. Bons estudos!
