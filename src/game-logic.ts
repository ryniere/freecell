import type { Card, SnapshotState, Selection } from './types';
import { SUIT_COLORS } from './types';

export function cardColor(card: Card): 'red' | 'black' {
  return SUIT_COLORS[card.suit] as 'red' | 'black';
}

export function createDeck(): Card[] {
  const deck: Card[] = [];
  for (let suit = 0; suit < 4; suit++) {
    for (let value = 1; value <= 13; value++) {
      deck.push({ suit, value });
    }
  }
  return deck;
}

export function shuffle(deck: Card[]): Card[] {
  const arr = [...deck];
  for (let i = arr.length - 1; i > 0; i--) {
    const j = Math.floor(Math.random() * (i + 1));
    [arr[i], arr[j]] = [arr[j], arr[i]];
  }
  return arr;
}

export function deal(): Card[][] {
  const deck = shuffle(createDeck());
  const tableau: Card[][] = [[], [], [], [], [], [], [], []];
  for (let i = 0; i < 52; i++) {
    tableau[i % 8].push(deck[i]);
  }
  return tableau;
}

export function canPlaceOnTableau(card: Card, column: Card[]): boolean {
  if (column.length === 0) return true;
  const top = column[column.length - 1];
  return cardColor(card) !== cardColor(top) && card.value === top.value - 1;
}

export function canPlaceOnFoundation(card: Card, foundationIndex: number, foundations: Card[][]): boolean {
  const foundation = foundations[foundationIndex];
  // Each foundation index maps to a suit: 0=hearts, 1=diamonds, 2=clubs, 3=spades
  if (card.suit !== foundationIndex) return false;
  if (foundation.length === 0) return card.value === 1;
  return card.value === foundation[foundation.length - 1].value + 1;
}

export function getSequenceStart(column: Card[]): number {
  if (column.length === 0) return -1;
  let start = column.length - 1;
  while (start > 0) {
    const below = column[start];
    const above = column[start - 1];
    if (cardColor(above) !== cardColor(below) && above.value === below.value + 1) {
      start--;
    } else {
      break;
    }
  }
  return start;
}

export function maxMovableCards(state: SnapshotState, destIsEmpty: boolean): number {
  const freeCells = state.freeCells.filter(c => c === null).length;
  let emptyCols = state.tableau.filter(c => c.length === 0).length;
  if (destIsEmpty) emptyCols = Math.max(0, emptyCols - 1);
  return (1 + freeCells) * Math.pow(2, emptyCols);
}

export function canMoveSequence(state: SnapshotState, colIndex: number, cardIndex: number, destColIndex: number): boolean {
  const col = state.tableau[colIndex];
  const destCol = state.tableau[destColIndex];
  const numCards = col.length - cardIndex;
  const topCard = col[cardIndex];
  if (!canPlaceOnTableau(topCard, destCol)) return false;
  if (numCards > maxMovableCards(state, destCol.length === 0)) return false;
  return true;
}

export function isSafeAutoMove(card: Card, foundations: Card[][]): boolean {
  if (card.value <= 2) return true;
  const color = cardColor(card);
  const oppositeMinValues = [0, 1, 2, 3]
    .filter(s => SUIT_COLORS[s] !== color)
    .map(s => {
      const f = foundations[s];
      return f.length > 0 ? f[f.length - 1].value : 0;
    });
  return oppositeMinValues.every(v => v >= card.value - 1);
}

export function autoMoveToFoundation(state: SnapshotState): SnapshotState {
  // Deep clone to avoid mutation
  let s = cloneState(state);
  let moved = true;
  while (moved) {
    moved = false;
    // Check free cells
    for (let i = 0; i < 4; i++) {
      const card = s.freeCells[i];
      if (card) {
        for (let f = 0; f < 4; f++) {
          if (canPlaceOnFoundation(card, f, s.foundations) && isSafeAutoMove(card, s.foundations)) {
            s.foundations[f] = [...s.foundations[f], card];
            s.freeCells[i] = null;
            moved = true;
          }
        }
      }
    }
    // Check tableau
    for (let c = 0; c < 8; c++) {
      if (s.tableau[c].length > 0) {
        const card = s.tableau[c][s.tableau[c].length - 1];
        for (let f = 0; f < 4; f++) {
          if (canPlaceOnFoundation(card, f, s.foundations) && isSafeAutoMove(card, s.foundations)) {
            s.foundations[f] = [...s.foundations[f], card];
            s.tableau[c] = s.tableau[c].slice(0, -1);
            moved = true;
          }
        }
      }
    }
  }
  return s;
}

export function checkWin(foundations: Card[][]): boolean {
  return foundations.every(f => f.length === 13);
}

export function cloneState(state: SnapshotState): SnapshotState {
  return JSON.parse(JSON.stringify(state));
}

function removeCardFromSource(state: SnapshotState, source: Selection): SnapshotState {
  const s = { ...state };
  if (source.type === 'freecell') {
    s.freeCells = [...s.freeCells];
    s.freeCells[source.index] = null;
  } else if (source.type === 'tableau') {
    s.tableau = s.tableau.map((col, i) => i === source.index ? col.slice(0, -1) : col);
  } else if (source.type === 'foundation') {
    s.foundations = s.foundations.map((f, i) => i === source.index ? f.slice(0, -1) : f);
  }
  return s;
}

export function tryMove(state: SnapshotState, source: Selection, dest: Selection): SnapshotState | null {
  // Multi-card tableau-to-tableau move (valid sequence)
  if (source.type === 'tableau' && dest.type === 'tableau' && source.cardIndex !== undefined) {
    const col = state.tableau[source.index];
    if (source.cardIndex >= col.length) return null;

    // Check if this is a valid sequence from cardIndex to end
    const seqStart = getSequenceStart(col);
    if (source.cardIndex >= seqStart) {
      // Valid sequence — try normal supermove
      if (canMoveSequence(state, source.index, source.cardIndex, dest.index)) {
        const cards = col.slice(source.cardIndex);
        const newTableau = state.tableau.map((c, i) => {
          if (i === source.index) return c.slice(0, source.cardIndex);
          if (i === dest.index) return [...c, ...cards];
          return c;
        });
        let result: SnapshotState = { ...state, tableau: newTableau, moves: state.moves + 1 };
        result = autoMoveToFoundation(result);
        return result;
      }
      return null;
    }

    // Card is NOT part of a valid sequence — try auto-supermove:
    // Move blocking cards (below selected card) to free cells, move the card, then restore
    return tryAutoSupermove(state, source.index, source.cardIndex, dest);
  }

  // Single card move
  let card: Card | undefined;
  let needsAutoSupermove = false;
  if (source.type === 'freecell') {
    card = state.freeCells[source.index] ?? undefined;
  } else if (source.type === 'tableau') {
    const col = state.tableau[source.index];
    if (source.cardIndex !== undefined && source.cardIndex < col.length - 1) {
      // Selected a non-bottom card — try auto-supermove
      card = col[source.cardIndex];
      needsAutoSupermove = true;
    } else {
      card = col.length > 0 ? col[col.length - 1] : undefined;
    }
  } else if (source.type === 'foundation') {
    const f = state.foundations[source.index];
    card = f.length > 0 ? f[f.length - 1] : undefined;
  }

  if (!card) return null;

  if (needsAutoSupermove && source.type === 'tableau' && source.cardIndex !== undefined) {
    return tryAutoSupermove(state, source.index, source.cardIndex, dest);
  }

  let newState: SnapshotState;

  if (dest.type === 'foundation') {
    if (!canPlaceOnFoundation(card, dest.index, state.foundations)) return null;
    newState = removeCardFromSource(state, source);
    newState.foundations = newState.foundations.map((f, i) =>
      i === dest.index ? [...f, card] : f
    );
  } else if (dest.type === 'tableau') {
    if (!canPlaceOnTableau(card, state.tableau[dest.index])) return null;
    newState = removeCardFromSource(state, source);
    newState.tableau = newState.tableau.map((c, i) =>
      i === dest.index ? [...c, card] : c
    );
  } else if (dest.type === 'freecell') {
    if (state.freeCells[dest.index] !== null) return null;
    newState = removeCardFromSource(state, source);
    newState.freeCells = [...newState.freeCells];
    newState.freeCells[dest.index] = card;
  } else {
    return null;
  }

  newState.moves = state.moves + 1;
  newState = autoMoveToFoundation(newState);
  return newState;
}

/**
 * Auto-supermove: temporarily move blocking cards below the selected card
 * to free cells, then move the selected card to the destination.
 * The blocking cards stay in the free cells (the player moved them conceptually).
 */
function tryAutoSupermove(state: SnapshotState, colIndex: number, cardIndex: number, dest: Selection): SnapshotState | null {
  const col = state.tableau[colIndex];
  const card = col[cardIndex];
  const blockingCards = col.slice(cardIndex + 1); // cards below the selected card

  // Check if there are enough free cells for the blocking cards
  const freeCellSlots: number[] = [];
  for (let i = 0; i < 4; i++) {
    if (state.freeCells[i] === null) freeCellSlots.push(i);
  }
  if (freeCellSlots.length < blockingCards.length) return null;

  // Check if the card can actually go to the destination
  if (dest.type === 'tableau') {
    if (!canPlaceOnTableau(card, state.tableau[dest.index])) return null;
  } else if (dest.type === 'foundation') {
    if (!canPlaceOnFoundation(card, dest.index, state.foundations)) return null;
  } else if (dest.type === 'freecell') {
    if (state.freeCells[dest.index] !== null) return null;
  } else {
    return null;
  }

  // Execute: move blocking cards to free cells (bottom card first)
  let s = cloneState(state);
  for (let i = blockingCards.length - 1; i >= 0; i--) {
    const slotIdx = freeCellSlots[blockingCards.length - 1 - i];
    s.freeCells[slotIdx] = blockingCards[i];
  }

  // Remove all cards from cardIndex onward from the source column
  s.tableau = s.tableau.map((c, i) => i === colIndex ? c.slice(0, cardIndex) : c);

  // Place the selected card at the destination
  if (dest.type === 'tableau') {
    s.tableau = s.tableau.map((c, i) => i === dest.index ? [...c, card] : c);
  } else if (dest.type === 'foundation') {
    s.foundations = s.foundations.map((f, i) => i === dest.index ? [...f, card] : f);
  } else if (dest.type === 'freecell') {
    s.freeCells[dest.index] = card;
  }

  s.moves = state.moves + 1;
  s = autoMoveToFoundation(s);
  return s;
}

export function getSelectedCards(state: SnapshotState, selection: Selection): Card[] {
  if (selection.type === 'freecell') {
    const card = state.freeCells[selection.index];
    return card ? [card] : [];
  }
  if (selection.type === 'foundation') {
    const f = state.foundations[selection.index];
    return f.length > 0 ? [f[f.length - 1]] : [];
  }
  if (selection.type === 'tableau') {
    const col = state.tableau[selection.index];
    const idx = selection.cardIndex ?? col.length - 1;
    return col.slice(idx);
  }
  return [];
}
