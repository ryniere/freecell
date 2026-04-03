# FreeCell

A modern reimagining of the FreeCell card game, originally developed as the final project for **INF1301 — Modular Programming** at **PUC-Rio** in June 2009.

## Origin

The original project was built in C for Windows XP by:

- **Carla Galdino**
- **Eliana Goldner**
- **Ryniere Silva**

The original implementation followed a modular architecture with separate modules for Card, Deck, Foundation Column, Tableau Column, Free Cell, Generic List, Persistence, Game Manager, and others — all with automated tests via scripts and the course's own testing framework. The original C source code, documentation, and test scripts are preserved in the `INF1301-Trab04-CGWELGRSS/` folder.

## This Version

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
