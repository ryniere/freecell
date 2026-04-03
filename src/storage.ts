import type { SnapshotState, GameStats } from './types';

const SAVE_KEY = 'freecell_save';
const STATS_KEY = 'freecell_stats';

export function saveGame(state: SnapshotState): void {
  localStorage.setItem(SAVE_KEY, JSON.stringify({
    freeCells: state.freeCells,
    foundations: state.foundations,
    tableau: state.tableau,
    moves: state.moves,
  }));
}

export function loadGame(): SnapshotState | null {
  const raw = localStorage.getItem(SAVE_KEY);
  if (!raw) return null;
  try {
    return JSON.parse(raw);
  } catch {
    return null;
  }
}

export function getStats(): GameStats {
  const raw = localStorage.getItem(STATS_KEY);
  if (!raw) return { gamesPlayed: 0, gamesWon: 0, bestTime: null, bestMoves: null, currentStreak: 0, bestStreak: 0 };
  try {
    return JSON.parse(raw);
  } catch {
    return { gamesPlayed: 0, gamesWon: 0, bestTime: null, bestMoves: null, currentStreak: 0, bestStreak: 0 };
  }
}

export function updateStats(won: boolean, time: number, moves: number): void {
  const stats = getStats();
  stats.gamesPlayed++;
  if (won) {
    stats.gamesWon++;
    stats.currentStreak++;
    if (stats.currentStreak > stats.bestStreak) stats.bestStreak = stats.currentStreak;
    if (stats.bestTime === null || time < stats.bestTime) stats.bestTime = time;
    if (stats.bestMoves === null || moves < stats.bestMoves) stats.bestMoves = moves;
  } else {
    stats.currentStreak = 0;
  }
  localStorage.setItem(STATS_KEY, JSON.stringify(stats));
}
