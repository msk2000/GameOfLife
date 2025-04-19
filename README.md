# Conway's Game of Life (C++ with SFML & Eigen)

This is a personal project that visualizes **Conway's Game of Life** using **C++**, **SFML** for graphics, and **Eigen** for matrix manipulation.

This program is fully functional but the code is intentionally left unfinished and unpolished. In the next update, I will refactor and attempt to add an immediate mode GUI for more interactavity.
##  Features

- Dynamic grid updates with custom patterns (glider, blinker, pulsar, etc.)
- SFML rendering with generation counter
- Uses matrix operations via Eigen
- Clean modular code structure

##  Note

This repository does **not** include:

- **SFML** (Simple and Fast Multimedia Library)
- **Eigen** (C++ template library for linear algebra)

You must download and install these separately:

### Installing SFML

Visit: [https://www.sfml-dev.org/download.php](https://www.sfml-dev.org/download.php)

### Installing Eigen

Visit: [https://eigen.tuxfamily.org/](https://eigen.tuxfamily.org/)

Both are open-source and freely available.

## Build Instructions

Example using g++:

```bash
g++ main.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system
./game
```

## How to Use the Code to Set Up a Simulation

This program simulates **Conway's Game of Life** using SFML for rendering and Eigen for grid data handling.

### Setting Initial Patterns

You can manually add patterns to specific grid locations using:

```cpp
addTestPattern(grid, "pattern_name", row, col);
```
**Available patterns:**

- "glider"
- "blinker"
- "block"
- "toad"
- "beacon"
- "lwss" (Lightweight Spaceship)
- "pulsar"
- "pentadecathlon"
- "diehard"
- "acorn"

**Example:**

```cpp
addTestPattern(grid, "glider", 5, 5);
addTestPattern(grid, "block", 10, 10);
```
You can also enable random initialization:
```cpp
randPopulate(grid, location);  // Called once at startup
```
**Starting the Simulation**

Once patterns are added (either manually or randomly), run the program. The main loop will:

Display the grid visually using SFML

Advance the simulation frame-by-frame

Show the current generation count on screen

**Customize Simulation Speed**
Modify the delay between frames:
```cpp
sf::sleep(sf::milliseconds(DELAY));  // e.g., DELAY = 100
```
