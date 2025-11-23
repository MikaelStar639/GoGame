# Go Game


## 📖 Introduction
This project is a implementation of the board game **Go**.

The game is built using **C++** language and the **SFML** library. This app simulates the board experience, handles user input, graphical rendering, and complex game logic.

## ✨ Features
* **Game Mode:** Player vs Player (PvP) on the same device.
* **Board Support:** Standard 19x19 grid.
* **Game Logic:**
    * ✅ Automatic capture of dead stones (0 liberties).
    * ✅ Suicide move prevention.
    * ✅ Ko rule enforcement.
    * ✅ Automatically detect and end the game. ()
* **Scoring:** Territory counting algorithm using Flood Fill.
* **UI/UX:** Mouse interaction, sound effects, and previous move indicators.

## 🛠️ Tech Stack
* **Language:** C++ (Standard 17)
* **Graphics:** SFML 2.5.1 (Simple and Fast Multimedia Library)
* **Build System:** CMake
* **IDE:** Visual Studio Code

## 🚀 Installation & Build Instructions

### Prerequisites
Ensure you have the following installed:
* g++ (MinGW-w64)
* CMake
* SFML (Located at `C:/SFML-2.5.1` or configured in environment variables)

### How to Compile (Windows)
Open your terminal in the project folder and run:

```bash
# 1. Create a build directory
mkdir build
cd build

# 2. Generate Makefiles using CMake
cmake -G "MinGW Makefiles" ..

# 3. Compile the executable
make