# 🍩 Donuts – Board Game in C

## 📌 Description

This project is an implementation of the board game **Donuts** (formerly called *Insert*) in the **C programming language**, developed as part of the *Introduction to Programming* course.

The game follows the traditional rules of Donuts: two players alternate turns placing their donuts on a **6x6 board**, trying to align five in a row while following directional constraints and flipping mechanics.

📺 For a video explanation of the rules: [YouTube link](https://www.youtube.com/watch?v=J42A1AoZ7rw)

---

## 🎮 Game Rules (Implemented Features)

### 1. Board Setup

* The board is a **6x6 grid**.
* Each cell is randomly assigned a movement type: **horizontal, vertical, main diagonal, or secondary diagonal**.
* There are exactly **9 cells of each movement type** (36 total).
* The board is displayed with **coordinates** (letters for rows, numbers for columns).

### 2. Playing a Piece

* Each turn, the player places one donut on the board.
* Placement rules:

  * Must be inside the board.
  * Must be on an empty space.
  * Must follow the movement constraint defined by the opponent’s previous move.
* If placement is impossible under the constraint, the player may place a donut anywhere valid.

### 3. Insertion Mechanic

* After placing a donut, if the new piece **sandwiches opponent’s pieces**, those donuts are flipped and become the current player’s color.

### 4. End of the Game

* The game ends if:

  * A player aligns **5 or more donuts** in any direction (horizontal, vertical, diagonal).
  * Or after **30 turns** (30 donuts placed).
* If the game ends by turn limit, the winner is the player with the **largest connected group of donuts**.

---

## 🛠️ Mandatory Functions

The following functions must be implemented:

```c
void exibeTabuleiro(void **tabuleiro, int linhas, int colunas);
// Prints the board.

int validaJogada(void **tabuleiro, int linha, int coluna, int linhas, int colunas);
// Validates if a move is legal.

int fazInsert(void **tabuleiro, int linha, int coluna, int linhas, int colunas);
// Performs the "insertion" (flipping) mechanic.

int verificaVitoria(void **tabuleiro, int linhas, int colunas);
// Checks if a player has won.
```

---

## ⚙️ Compilation & Execution

Compile with:

```bash
gcc src/*.c -o donuts
```

Run with:

```bash
./donuts
```

---

## ⭐ Extra Features (Optional)

* Save and load the current game state using files. (+1 point)
* Implement a replay system to review a completed match. (+1 point)

---

## 📅 Important Dates

* **Aug 27, 2025** – Project specification released
* **Aug 28, 2025** – Project demonstration
* **Sep 05, 2025** – Group formation deadline
* **Oct 08, 2025** – Final submission (by 23:59)
* **Oct 09, 2025** – Group presentations
* **Oct 15, 2025** – Grades release

---

## 👨‍💻 Author

Developed as part of the **Introduction to Programming (2025.1)** course under Professor Roberto Hugo Wanderley Pinheiro.


