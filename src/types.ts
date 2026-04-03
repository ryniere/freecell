// Suit indices: 0=hearts, 1=diamonds, 2=clubs, 3=spades
export interface Card {
  suit: number;
  value: number; // 1(A) through 13(K)
}

export interface Selection {
  type: 'freecell' | 'tableau' | 'foundation';
  index: number;
  cardIndex?: number; // for multi-card tableau selection
}

export interface SnapshotState {
  freeCells: (Card | null)[];
  foundations: Card[][];
  tableau: Card[][];
  moves: number;
}

export interface GameState extends SnapshotState {
  history: SnapshotState[];
  selection: Selection | null;
  won: boolean;
  dealing: boolean;
  message: { text: string; timeout: number } | null;
}

export type GameAction =
  | { type: 'NEW_GAME' }
  | { type: 'SELECT'; selection: Selection }
  | { type: 'CLEAR_SELECTION' }
  | { type: 'MOVE'; source: Selection; dest: Selection }
  | { type: 'UNDO' }
  | { type: 'SAVE' }
  | { type: 'LOAD' }
  | { type: 'DEAL_COMPLETE' }
  | { type: 'CLEAR_MESSAGE' }
  | { type: 'SHOW_MESSAGE'; text: string };

export interface GameStats {
  gamesPlayed: number;
  gamesWon: number;
  bestTime: number | null; // seconds
  bestMoves: number | null;
  currentStreak: number;
  bestStreak: number;
}

// Display constants
export const SUITS = ['hearts', 'diamonds', 'clubs', 'spades'] as const;
export const SUIT_SYMBOLS = ['\u2665', '\u2666', '\u2663', '\u2660'];
export const SUIT_COLORS = ['red', 'red', 'black', 'black'] as const;
export const VALUE_NAMES = ['', 'A', '2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K'];
