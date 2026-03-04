# 🌌 Galactic Star Wars Battle

A strategic, turn-based C++ terminal game where players command fleets in a high-stakes battle for the galaxy. Built with Object-Oriented Programming (OOP), the game features dynamic grid scaling, tactical shot modifiers, and a randomized gift system.

---

## 🎮 Game Mechanics

### 🚢 The Fleet
Each player commands a diverse fleet with different tactical footprints:
* **Star Destroyer:** 5 Cells
* **Mon Calamari Cruiser:** 4 Cells
* **X-Wing Squadron:** 3 Cells
* **TIE Fighter:** 1 Cell

### ⚡ Strategic Combat
* **Dynamic Shots:** Your maximum shots are determined by your level, but can be modified by bonuses or opponent penalties.
* **The Force (Gift System):** Landing **2 or more hits** in a single turn triggers a **30% chance** to receive a "Gift" (Bonus turns, shot caps, or armor).
* **Bonus Turns:** If you earn an extra turn, you can press the advantage before the opponent retaliates.

---

### Prerequisites
* A C++ compiler (GCC/G++ or Clang)
* **CMake** (Minimum version 3.20 recommended)
