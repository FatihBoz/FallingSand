# Falling Sand Simulator

A real-time, cell-based physics sandbox built in C++ with SFML. Place sand, water, lava, walls, and plants on a grid and watch them interact according to their own physical rules.

## Controls

| Key | Material |
|-----|----------|
| `1` | Sand |
| `2` | Water |
| `3` | Wall |
| `4` | Lava |
| `5` | Plant |

Hold **left mouse button** to paint the selected material onto the grid.

---

## Architecture

### Factory Pattern — Material Construction

Each material has a dedicated factory class that inherits from the abstract `BehaviourFactory`:

```cpp
class BehaviourFactory {
public:
    virtual std::unique_ptr<MaterialBehaviour> createBehaviour() = 0;
};
```

Concrete factories (e.g. `SandFactory`, `WaterFactory`, `LavaFactory`) override `createBehaviour()` to instantiate the correct `MaterialBehaviour` subclass. During initialization, `Game::initializeBehaviours()` calls each factory and stores the resulting behaviours in a `std::vector<std::unique_ptr<MaterialBehaviour>>` indexed by material ID. This decouples object creation from usage and makes adding new materials straightforward — only a new factory and behaviour class are needed.

---

### Strategy Pattern — Movement Behaviours

Movement logic is separated from material identity through a `MovementBehaviour` interface:

```cpp
class MovementBehaviour {
public:
    virtual bool tryMove(Grid& grid, int x, int y) = 0;
};
```

Two concrete strategies are implemented:

- **`FallingMovement`** — tries to move down, then diagonally down-left or down-right. Used by sand.
- **`FluidMovement`** — extends falling movement with horizontal spreading (left and right). Used by water and lava.

Each `MaterialBehaviour` subclass holds its movement strategy as a member, composing behavior rather than duplicating movement logic per material.

---

### Strategy Pattern — Material Behaviours

Similarly, per-cell update logic is abstracted behind `MaterialBehaviour`:

```cpp
class MaterialBehaviour {
public:
    virtual void update(Grid& grid, int x, int y) = 0;
};
```

Each material's `update()` delegates to its movement strategy and handles any material-specific logic (e.g. plant growth on water contact). The `Grid` calls `behaviours[value]->update(...)` for every non-empty cell each tick — it has no knowledge of what a specific material does.

---

### Interaction Table — Lookup Table for Chemical Reactions

Cross-material interactions (e.g. lava destroying sand, lava + water forming a wall) are resolved through `InteractionTable`, a 2D lookup table indexed by material ID pairs:

```cpp
struct InteractionResult {
    int result;       // what material the target cell becomes
    bool affectSource; // whether the source cell is also transformed
};
```

The table is populated once at startup. When `Grid::trySwap()` encounters two non-empty cells, it queries the table:

- If no interaction is defined, movement is simply blocked.
- If an interaction exists, the target (and optionally the source) cell is replaced with the result material.

This keeps interaction rules data-driven and centralized. Adding a new reaction requires only setting one entry in the table — no changes to movement or behaviour classes.

---

### Grid Update Loop — Cellular Automaton

The grid is updated bottom-to-top, left-to-right each tick:

```cpp
for (int y = rows - 2; y >= 0; --y)
    for (int x = 0; x < columns; ++x)
        behaviours[value]->update(*this, x, y);
```

Updating from the bottom ensures falling materials settle correctly in a single tick without requiring multiple passes. Each cell swap is resolved immediately, so later cells in the same tick see the already-updated state.

---

## Dependencies

- [SFML](https://www.sfml-dev.org/) — windowing, rendering, input
