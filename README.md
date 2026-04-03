# FreeCell

A modern reimagining of the FreeCell card game, originally developed as the final project for **INF1301 — Modular Programming** at **PUC-Rio** in June 2009.

## Origin

The original project was built in C for Windows XP by:

- **Carla Galdino**
- **Eliana Goldner**
- **Ryniere Silva**

The original implementation followed a modular architecture with separate modules for Card, Deck, Foundation Column, Tableau Column, Free Cell, Generic List, Persistence, Game Manager, and others — all with automated tests via scripts and the course's own testing framework. The original C source code, documentation, and test scripts are preserved in the `INF1301-Trab04-CGWELGRSS/` folder.

## Running the Original (2009) Version

The original game is a text-based console application. Pre-built binaries are included in `INF1301-Trab04-CGWELGRSS/Produto/`:

**macOS (Apple Silicon):**

```bash
cd INF1301-Trab04-CGWELGRSS/Produto
./FreeCell_mac
```

**Windows:**

```bash
cd INF1301-Trab04-CGWELGRSS\Produto
FreeCell.exe
```

**Commands:** the game uses text commands to move cards:

```
mover aleatoria <col> temporaria <cell>   — move from tableau column to free cell
mover aleatoria <col> base <foundation>   — move from tableau column to foundation
mover aleatoria <col> aleatoria <col>     — move between tableau columns
mover temporaria <cell> aleatoria <col>   — move from free cell to tableau column
fim                                        — quit (with option to save)
```

Indices are 1-based. At startup, choose `1` for a new game or `2` to load a saved game.

**Building from source (Windows with MSVC):**

```bash
cd INF1301-Trab04-CGWELGRSS\Batches
Tudo.bat
```

This compiles all modules, runs the automated test suites, and builds the executable.

## This Version (2026)

In 2026, Ryniere decided to recreate the game as a modern web application, keeping the visual style inspired by the classic Windows FreeCell.

### Stack

- **React 19** + **TypeScript**
- **Vite** (bundler)
- **Tailwind CSS v4**

### Getting Started

```bash
npm install
npm run dev
```

The game opens at `http://localhost:5173`.

### Features

- Full FreeCell game with classic rules
- Drag and drop to move cards
- Double-click to automatically send cards to the foundation (with fly animation)
- Auto-supermove: automatically moves blocking cards to free cells when needed
- Undo (Ctrl+Z), New Game (Ctrl+N)
- Save/Load game via localStorage
- Game statistics tracking
- Light/Dark theme
- Sound effects
- Win animation with confetti

## License

Academic / personal project.
