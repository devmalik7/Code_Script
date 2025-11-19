# Pathfinding Visualizer (Code_Script Module)

A GUI-based C++17 + Qt6 pathfinding animation tool that visually demonstrates  
**BFS**, **Dijkstra**, and **A\*** exploring a 2D grid in real time.  
This module is intended for educational use and integration into the Code_Script project.

---

## 📄 Small Description

The Pathfinding Visualizer is an interactive Qt6 application that displays how classical pathfinding algorithms traverse a grid to find a path between two points. Users can place walls, change algorithms, adjust animation speed, and observe the search progress and final path.

---

## 🎯 Goals

- Visually demonstrate how BFS, Dijkstra, and A\* explore and find shortest paths.
- Provide an interactive 2D grid where users can toggle walls and set start/target nodes.
- Animate algorithm steps in real-time (visited nodes + final path).
- Maintain a thread-safe architecture using a background worker thread for algorithms.
- Offer adjustable animation speed and algorithm selection via a toolbar UI.
- Serve as a self-contained Code_Script module.

---

## 📁 File Structure

```
pathfinding_visualizer/
│
├── CMakeLists.txt
├── README.md
├── .gitignore
│
├── include/
│   ├── MainWindow.hpp
│   ├── Grid.hpp
│   ├── Node.hpp
│   └── Algorithms/
│       └── AlgorithmWorker.hpp
│
├── src/
│   ├── main.cpp
│   ├── MainWindow.cpp
│   ├── Grid.cpp
│   ├── Node.cpp
│   └── Algorithms/
│       └── AlgorithmWorker.cpp
│
├── ui/
│   └── MainWindow.ui        
```

---

## 🛠️ Prerequisites

### Software Requirements
- **Qt 6.9.3** (or later)  
  - MinGW 64-bit or MSVC 64-bit build tools installed via Qt Online Installer.
- **CMake 3.16+**
- **C++17 compatible compiler**
  - MSYS2 MinGW-w64 (preferred for simplicity)
  - or Microsoft Visual C++ (MSVC)
- **VS Code** (recommended) with:
  - *CMake Tools* extension
  - *C/C++* extension

### Optional
- Qt Creator (IDE)
- Git (if contributing back to Code_Script)

---

## ▶️ Usage Instructions

### Running the Application
After building the project, launch:

./build/pathfinding_visualizer.exe

This opens the main window containing the 2D grid and the control toolbar.

---

### Grid Interaction

- **Left Click** on a cell → Toggle Wall (White ↔ Black)
- **Right Click** on a cell → Set Start Node (Green)
- **Shift + Left Click** or **Middle Click** → Set Target Node (Red)

The grid updates visually using `Node` objects in a `QGraphicsScene`.

---

### Toolbar Controls

- **Run** 
  Starts the selected algorithm on a background thread (`AlgorithmWorker`).

- **Reset** 
  Clears all walls, visited cells, and path markings. Start/Target nodes return to defaults.

- **Algorithm Selector**  
  Choose between **BFS**, **Dijkstra**, or **A\***.

- **Speed Slider**  
  Controls animation delay (ms per step).  
  Lower value = faster, higher = slower.

---

### Visualization Colors
- **Start Node** → Green  
- **Target Node** → Red  
- **Walls** → Black  
- **Visited Cells** → Light Blue  
- **Final Path** → Yellow  

Updates are triggered by worker-thread signals:  
`visit(row,col)` and `pathNode(row,col)`.

---

## 🔧 Build Instructions (Windows — Qt 6.9.3)

### Requirements
- Qt **6.9.3**
  - Either **MinGW 64-bit** or **MSVC 2022 64-bit** Qt build installed
- CMake **3.16+**
- A C++17 compiler
- Optional: VS Code with **CMake Tools** extension

---

### 1️⃣ Configure (MinGW Example)

cmake -B build -S . -G "MinGW Makefiles" ^
-DCMAKE_PREFIX_PATH="C:/Qt/6.9.3/mingw_64/lib/cmake"

### 2️⃣ Build (MinGW)
cmake --build build

---

### 1️⃣ Configure (MSVC Example)

cmake -B build -S . -G "NMake Makefiles" `
-DCMAKE_PREFIX_PATH="C:/Qt/6.9.3/msvc2022_64/lib/cmake"

### 2️⃣ Build (MSVC)
cmake --build build --config Release

---

### 3️⃣ Run

./build/pathfinding_visualizer.exe
