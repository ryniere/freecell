import { createContext, useContext, useReducer, type Dispatch } from 'react';
import type { GameState, GameAction, SnapshotState, Selection } from '../types';
import { deal, tryMove, cloneState, checkWin, getSequenceStart, getSelectedCards, canPlaceOnTableau, canMoveSequence, canPlaceOnFoundation } from '../game-logic';
import { saveGame, loadGame } from '../storage';
import { playCardPlace, playCardError, playShuffle, playUndo } from '../sound';

function createInitialState(): GameState {
  return {
    freeCells: [null, null, null, null],
    foundations: [[], [], [], []],
    tableau: deal(),
    moves: 0,
    history: [],
    selection: null,
    won: false,
    dealing: true,
    message: null,
  };
}

function snapshot(state: GameState): SnapshotState {
  return cloneState({
    freeCells: state.freeCells,
    foundations: state.foundations,
    tableau: state.tableau,
    moves: state.moves,
  });
}

function handleSelect(state: GameState, sel: Selection): GameState {
  // If nothing selected, select this
  if (!state.selection) {
    if (sel.type === 'freecell' && state.freeCells[sel.index]) {
      return { ...state, selection: sel };
    }
    if (sel.type === 'tableau' && state.tableau[sel.index].length > 0) {
      const cardIndex = sel.cardIndex !== undefined ? sel.cardIndex : state.tableau[sel.index].length - 1;
      return { ...state, selection: { ...sel, cardIndex } };
    }
    if (sel.type === 'foundation' && state.foundations[sel.index].length > 0) {
      return { ...state, selection: sel };
    }
    return state;
  }

  // Clicking the same column - re-select or deselect
  if (state.selection.type === 'tableau' && sel.type === 'tableau' && state.selection.index === sel.index) {
    const seqStart = getSequenceStart(state.tableau[sel.index]);
    if (sel.cardIndex !== undefined && sel.cardIndex >= seqStart && sel.cardIndex !== state.selection.cardIndex) {
      return { ...state, selection: { ...sel, cardIndex: sel.cardIndex } };
    }
    return { ...state, selection: null };
  }

  // Clicking same non-tableau spot - deselect
  if (state.selection.type === sel.type && state.selection.index === sel.index) {
    return { ...state, selection: null };
  }

  // Try to move
  const source = state.selection;
  const dest = sel;
  const selectedCards = getSelectedCards(state, source);

  // Multi-card to freecell/foundation not allowed
  if (selectedCards.length > 1 && (dest.type === 'freecell' || dest.type === 'foundation')) {
    return { ...state, selection: null, message: { text: 'Apenas 1 carta pode ir para celula livre ou base.', timeout: 2500 } };
  }

  const result = tryMove(snapshot(state), source, dest);
  if (result) {
    playCardPlace();
    const newHistory = [...state.history, snapshot(state)];
    if (newHistory.length > 200) newHistory.shift();
    const won = checkWin(result.foundations);
    return {
      ...state,
      freeCells: result.freeCells,
      foundations: result.foundations,
      tableau: result.tableau,
      moves: result.moves,
      history: newHistory,
      selection: null,
      won,
      message: null,
    };
  }

  // Move failed - re-select the clicked spot
  playCardError();
  if (sel.type === 'freecell' && state.freeCells[sel.index]) {
    return { ...state, selection: sel };
  }
  if (sel.type === 'tableau' && state.tableau[sel.index].length > 0) {
    const cardIndex = sel.cardIndex !== undefined ? sel.cardIndex : state.tableau[sel.index].length - 1;
    return { ...state, selection: { ...sel, cardIndex } };
  }
  if (sel.type === 'foundation' && state.foundations[sel.index].length > 0) {
    return { ...state, selection: sel };
  }
  return { ...state, selection: null };
}

function gameReducer(state: GameState, action: GameAction): GameState {
  switch (action.type) {
    case 'NEW_GAME': {
      playShuffle();
      return createInitialState();
    }
    case 'SELECT': {
      if (state.won) return state;
      return handleSelect(state, action.selection);
    }
    case 'MOVE': {
      if (state.won) return state;
      const selectedCards = getSelectedCards(state, action.source);
      if (selectedCards.length > 1 && (action.dest.type === 'freecell' || action.dest.type === 'foundation')) {
        return { ...state, selection: null };
      }
      const result = tryMove(snapshot(state), action.source, action.dest);
      if (result) {
        playCardPlace();
        const newHistory = [...state.history, snapshot(state)];
        if (newHistory.length > 200) newHistory.shift();
        const won = checkWin(result.foundations);
        return {
          ...state,
          freeCells: result.freeCells,
          foundations: result.foundations,
          tableau: result.tableau,
          moves: result.moves,
          history: newHistory,
          selection: null,
          won,
          message: null,
        };
      }
      playCardError();
      return { ...state, selection: null };
    }
    case 'CLEAR_SELECTION':
      return { ...state, selection: null };
    case 'UNDO': {
      if (state.history.length === 0) return { ...state, message: { text: 'Nada para desfazer.', timeout: 2000 } };
      playUndo();
      const prev = state.history[state.history.length - 1];
      return {
        ...state,
        freeCells: prev.freeCells,
        foundations: prev.foundations,
        tableau: prev.tableau,
        moves: prev.moves,
        history: state.history.slice(0, -1),
        selection: null,
        won: false,
        message: null,
      };
    }
    case 'SAVE': {
      saveGame(snapshot(state));
      return { ...state, message: { text: 'Jogo salvo!', timeout: 2000 } };
    }
    case 'LOAD': {
      const loaded = loadGame();
      if (!loaded) return { ...state, message: { text: 'Nenhum jogo salvo encontrado.', timeout: 2500 } };
      const won = checkWin(loaded.foundations);
      return {
        ...state,
        freeCells: loaded.freeCells,
        foundations: loaded.foundations,
        tableau: loaded.tableau,
        moves: loaded.moves,
        history: [],
        selection: null,
        won,
        dealing: false,
        message: won ? null : { text: 'Jogo carregado!', timeout: 2000 },
      };
    }
    case 'DEAL_COMPLETE':
      return { ...state, dealing: false };
    case 'SHOW_MESSAGE':
      return { ...state, message: { text: action.text, timeout: 2500 } };
    case 'CLEAR_MESSAGE':
      return { ...state, message: null };
    default:
      return state;
  }
}

// Context
interface GameContextValue {
  state: GameState;
  dispatch: Dispatch<GameAction>;
}

export const GameContext = createContext<GameContextValue | null>(null);

export function useGameState() {
  const ctx = useContext(GameContext);
  if (!ctx) throw new Error('useGameState must be used within GameProvider');
  return ctx;
}

export { gameReducer, createInitialState };

// Helper: check if a card can be dropped on a destination
export function canDropOn(state: GameState, dest: Selection): boolean {
  if (!state.selection) return false;
  const cards = getSelectedCards(state, state.selection);
  if (cards.length === 0) return false;
  const card = cards[0];

  if (dest.type === 'foundation') {
    return cards.length === 1 && canPlaceOnFoundation(card, dest.index, state.foundations);
  }
  if (dest.type === 'freecell') {
    return cards.length === 1 && state.freeCells[dest.index] === null;
  }
  if (dest.type === 'tableau') {
    if (!canPlaceOnTableau(card, state.tableau[dest.index])) return false;
    if (cards.length > 1 && state.selection!.type === 'tableau') {
      return canMoveSequence(state, state.selection!.index, state.selection!.cardIndex!, dest.index);
    }
    return true;
  }
  return false;
}
