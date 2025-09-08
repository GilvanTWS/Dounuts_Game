# Dounuts_Game# 🍩 Donuts – Board Game in C

## 📌 Description
This project is a **C implementation** of the board game **Donuts**, originally designed by Bruno Cathala.  
The goal of the game is to align **5 donuts of your color** in a row (horizontally, vertically, or diagonally), while following placement and flipping rules.

## 🎮 Rules Summary
- The board is made of **4 tiles of 3x3**, forming a **6x6 grid**.
- Each player starts with **15 donuts** (vanilla or chocolate).
- The first move can be placed on any square.
- The **line drawn on the chosen square** indicates the direction where the next player must play.
- If no spaces are available in that direction, the player may play anywhere (**Disobedience**).
- When a donut is placed between opponent’s donuts, they are flipped and become your color (**Insertion**).
- The game ends when:
  - A player achieves **5 consecutive donuts** in a row, column, or diagonal.  
  - Or when all donuts are placed — the winner is the player with the **largest connected group**.

## 🏗️ Project Structure
/donuts
│── src/
│   ├── main.c        
│   ├── board.c       
│   ├── board.h
│   ├── game.c        
│   ├── game.h
│   ├── utils.c       
│   ├── utils.h
│
│── assets/           
│── README.md         
