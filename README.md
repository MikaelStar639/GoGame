# Go Game


## 📖 Introduction
This project is a implementation of the board game **Go**.

The game is built using **C++** language and the **SFML** library. This app simulates the board experience, handles user input, graphical rendering, and complex game logic.

## ✨ Features
* **Game Mode:** Player vs Player (PvP) on the same device.
* **Board:** Standard 19x19 grid.
* **Game Logic:**
    * ✅ Automatic capture of dead stones (0 liberties).
    * ✅ Suicide move prevention.
    * ✅ Ko rule enforcement.
    * ✅ Automatically detect and end the game. 
* **Scoring:** Chinese rules (Area Scoring, 7.5 komi).
* **Save/Load Game History**: save/load every moves from the beginning of the game to the current game state.
* **Change Style**: change the style of the board/stones.


## 🛠️ Tech Stack
* **Language:** C++ 17 (GCC 14.2.0)
* **Graphics:** SFML 3.0.2 (Simple and Fast Multimedia Library)
* **Build System:** CMake

## 🚀 Installation

### Prerequisites
Ensure you have the following installed:
* g++ (MinGW-w64) 14.2.0
* at least CMake 3.15

### How to run
Open your terminal in the project folder and run:

```bash
# 1. Create build directory
md build
cd build

# 2. Configure
cmake ..

# 3. Build
cmake --build .

# 4. Run
.\gogame