# Glitch Cube 3D Cellular Automata Simulation

---

## Features

* **3D Grid Space:** $30 \times 30 \times 30$ toroidal grid implementing custom neighbor-counting logic.
* **Interactive Camera:** Free-roaming 3D camera controls for inspecting the cellular lattice from any angle.
* **Real-Time Controls:** Adjust simulation parameters (glitch bias and cell size) on the fly.
* **Dynamic Visualization:** Procedural color mapping for active cells updated per frame.

---

## Requirements

* **C++ Compiler:** Supporting C++11 or later.
* **Raylib:** Installed and linked in your development environment.

---

## Building and Running

Compile the code and link it against Raylib. For example, using `g++` on Linux/macOS:

```bash
g++ main.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o cellular_3d
./cellular_3d
