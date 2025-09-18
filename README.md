# 🍩 Donuts – Board Game in C

## 📌 Description
This project is an implementation of the **Donuts** board game (formerly called *Insert*) in the **C programming language**, developed as part of the *Introduction to Programming* course.

The game follows the traditional rules of Donuts: two players take turns placing their donuts on the board, trying to align five in a row while following directional restrictions and the flipping mechanic.

📺 For a video explanation of the rules: *YouTube link*

---

## 🎮 Game Rules (Implemented Features)

### 1. Board Setup
- The game is played on an **N x N** grid, where **N** is defined by the user.  
- Each cell is randomly assigned a **movement type**: horizontal, vertical, main diagonal, or secondary diagonal.  
- All movement types have an equal number of cells on the board.  
- The board is displayed with **coordinates** (letters for rows, numbers for columns).  

### 2. Placing a Piece
- Each turn, a player places a piece on the board.  
- Placement rules:  
  * Must be within the board limits.  
  * Must be on an empty space.  
  * Must follow the movement restriction set by the opponent’s previous move.  
- If it is impossible to place a piece under the restriction, the player may place a donut **anywhere valid** on the board.  

### 3. Insertion Mechanic
- After placing a donut, if the new piece encloses the opponent’s donuts, the surrounded pieces are flipped and become the current player’s color.  

### 4. End of the Game
The game ends if:  
- A player aligns **5 or more donuts** in any direction (horizontal, vertical, or diagonal).  
- Or after **30 turns** (30 donuts placed).  

If the game ends by the turn limit, the winner is the player with the **largest connected group of donuts**.  

---
⚙️ Compilation & Execution

Compile with:

gcc src/*.c -o donuts
⭐ Extra Features (Optional)

Save and load the current game state using files. (+1 point)

Implement a replay system to review a complete match. (+1 point)

📅 Important Dates

Aug 27, 2025 – Project specification release

Aug 28, 2025 – Project demonstration

Sep 05, 2025 – Deadline for group formation

Oct 08, 2025 – Final submission (by 23:59)

Oct 09, 2025 – Group presentations

Oct 15, 2025 – Grades release

## 🛠️ Required Functions

```c
void exibeTabuleiro(Celula **tabuleiro, int N);
// Prints the board.

int validaJogada(Celula **tabuleiro, int linha, int coluna, int ultimaLinha, int ultimaColuna, int N, int jogadaLivre);
// Validates if a move is legal, considering the direction of the last move and allowing a "free move" if necessary.

void fazInsert(Celula **tabuleiro, int linha, int coluna, int jogador, int N);
// Executes the "insertion" mechanic (flipping pieces).

int verificaVitoria(Celula **tabuleiro, int jogador, int N);
// Checks if a player has won.

void inicializaTabuleiro(Celula **tabuleiro, int N);
// Initializes the board with empty cells and random directions.

int encontrarMaiorRegiao(Celula **tabuleiro, int jogador, int N);
// Finds the largest connected group of a player’s pieces.

*
