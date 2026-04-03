import { useReducer, useEffect, useCallback, useState, useRef, createContext, useContext } from 'react';
import { GameContext, gameReducer, createInitialState } from './hooks/useGameState';
import { useTheme } from './hooks/useTheme';
import { useTimer } from './hooks/useTimer';
import { useDragAndDrop } from './hooks/useDragAndDrop';
import { updateStats } from './storage';
import { Header } from './components/Header';
import { GameBoard } from './components/GameBoard';
import { WinOverlay } from './components/WinOverlay';
import { StatsDialog } from './components/StatsDialog';
import { Card, CARD_W, CARD_H } from './components/Card';
import type { Selection, Card as CardType } from './types';

// ── Drag context ──
interface DragContextValue {
  isDragging: boolean;
  dragCards: CardType[];
  dragPos: { x: number; y: number };
  dragOffset: { x: number; y: number };
  dragSource: Selection | null;
  onPointerDown: (e: React.PointerEvent, source: Selection, cards: CardType[]) => void;
  onPointerMove: (e: React.PointerEvent) => void;
  onPointerUp: (e: React.PointerEvent) => void;
}

export const DragContext = createContext<DragContextValue | null>(null);
export function useDrag() {
  return useContext(DragContext);
}

// ── Flying card animation context ──
interface FlyingCardData {
  card: CardType;
  from: { x: number; y: number };
  to: { x: number; y: number };
  id: number;
}

interface FlyContextValue {
  flyToFoundation: (card: CardType, sourceEl: HTMLElement, foundationIndex: number) => Promise<void>;
}

export const FlyContext = createContext<FlyContextValue | null>(null);
export function useFly() {
  return useContext(FlyContext);
}

// Smooth flying card component using rAF
const FLY_DURATION = 350; // ms

function FlyingCard({ data, onDone }: { data: FlyingCardData; onDone: () => void }) {
  const ref = useRef<HTMLDivElement>(null);
  const startTime = useRef(0);

  useEffect(() => {
    startTime.current = performance.now();
    let rafId: number;

    // Cubic bezier ease-out approximation
    function easeOutCubic(t: number) {
      return 1 - Math.pow(1 - t, 3);
    }

    function animate(now: number) {
      const elapsed = now - startTime.current;
      const raw = Math.min(elapsed / FLY_DURATION, 1);
      const t = easeOutCubic(raw);

      const x = data.from.x + (data.to.x - data.from.x) * t;
      const y = data.from.y + (data.to.y - data.from.y) * t;
      // Slight arc upward at peak
      const arc = -40 * Math.sin(raw * Math.PI);
      // Subtle scale bump
      const scale = 1 + 0.04 * Math.sin(raw * Math.PI);

      if (ref.current) {
        ref.current.style.transform = `translate3d(${x}px, ${y + arc}px, 0) scale(${scale})`;
        ref.current.style.boxShadow = `${2 + 4 * (1 - raw)}px ${3 + 6 * (1 - raw)}px ${8 + 12 * (1 - raw)}px rgba(0,0,0,${0.25 + 0.2 * (1 - raw)})`;
      }

      if (raw < 1) {
        rafId = requestAnimationFrame(animate);
      } else {
        onDone();
      }
    }

    rafId = requestAnimationFrame(animate);
    return () => cancelAnimationFrame(rafId);
  }, [data, onDone]);

  return (
    <div
      ref={ref}
      className="fixed pointer-events-none z-[150]"
      style={{
        left: 0,
        top: 0,
        transform: `translate3d(${data.from.x}px, ${data.from.y}px, 0)`,
        willChange: 'transform',
      }}
    >
      <Card
        card={data.card}
        style={{ position: 'relative' }}
      />
    </div>
  );
}

function App() {
  const [state, dispatch] = useReducer(gameReducer, null, createInitialState);
  const { theme, toggle: toggleTheme } = useTheme();
  const timer = useTimer();
  const [showStats, setShowStats] = useState(false);
  const [flyingCards, setFlyingCards] = useState<FlyingCardData[]>([]);
  const flyIdRef = useRef(0);
  const flyResolvers = useRef<Map<number, () => void>>(new Map());

  const flyToFoundation = useCallback((card: CardType, sourceEl: HTMLElement, foundationIndex: number): Promise<void> => {
    return new Promise((resolve) => {
      const sourceRect = sourceEl.getBoundingClientRect();
      const targetEl = document.querySelector(`[data-foundation-index="${foundationIndex}"]`);
      if (!targetEl) {
        resolve();
        return;
      }
      const targetRect = targetEl.getBoundingClientRect();

      const id = ++flyIdRef.current;
      flyResolvers.current.set(id, resolve);

      setFlyingCards(prev => [...prev, {
        card,
        from: { x: sourceRect.left, y: sourceRect.top },
        to: { x: targetRect.left, y: targetRect.top },
        id,
      }]);
    });
  }, []);

  const handleFlyDone = useCallback((id: number) => {
    setFlyingCards(prev => prev.filter(f => f.id !== id));
    const resolve = flyResolvers.current.get(id);
    if (resolve) {
      flyResolvers.current.delete(id);
      resolve();
    }
  }, []);

  const flyContextValue: FlyContextValue = { flyToFoundation };

  const handleDragMove = useCallback((source: Selection, dest: Selection) => {
    dispatch({ type: 'MOVE', source, dest });
  }, []);

  const handleDragSelect = useCallback((selection: Selection) => {
    dispatch({ type: 'SELECT', selection });
  }, []);

  const { dragState, startDrag, moveDrag, endDrag } = useDragAndDrop(handleDragMove, handleDragSelect);

  const dragContextValue: DragContextValue = {
    isDragging: dragState.isDragging,
    dragCards: dragState.cards,
    dragPos: dragState.currentPos,
    dragOffset: dragState.offset,
    dragSource: dragState.source,
    onPointerDown: startDrag,
    onPointerMove: moveDrag,
    onPointerUp: endDrag,
  };

  useEffect(() => {
    if (state.moves > 0 && !state.won && !timer.running) timer.start();
  }, [state.moves, state.won, timer.running]);

  useEffect(() => {
    if (state.won) { timer.stop(); updateStats(true, timer.elapsed, state.moves); }
  }, [state.won]);

  useEffect(() => {
    if (state.moves === 0 && state.history.length === 0) timer.reset();
  }, [state.moves, state.history.length]);

  useEffect(() => {
    if (state.dealing) {
      const timeout = setTimeout(() => dispatch({ type: 'DEAL_COMPLETE' }), 800);
      return () => clearTimeout(timeout);
    }
  }, [state.dealing]);

  useEffect(() => {
    if (state.message) {
      const timeout = setTimeout(() => dispatch({ type: 'CLEAR_MESSAGE' }), state.message.timeout);
      return () => clearTimeout(timeout);
    }
  }, [state.message]);

  const handleKeyDown = useCallback((e: KeyboardEvent) => {
    if (e.key === 'Escape') dispatch({ type: 'CLEAR_SELECTION' });
    else if (e.key === 'z' && (e.ctrlKey || e.metaKey)) { e.preventDefault(); dispatch({ type: 'UNDO' }); }
    else if (e.key === 'n' && (e.ctrlKey || e.metaKey)) { e.preventDefault(); dispatch({ type: 'NEW_GAME' }); }
  }, []);

  useEffect(() => {
    document.addEventListener('keydown', handleKeyDown);
    return () => document.removeEventListener('keydown', handleKeyDown);
  }, [handleKeyDown]);

  return (
    <GameContext.Provider value={{ state, dispatch }}>
      <DragContext.Provider value={dragContextValue}>
        <FlyContext.Provider value={flyContextValue}>
          <div className="min-h-screen flex flex-col">
            <Header
              timerFormatted={timer.formatted}
              onToggleTheme={toggleTheme}
              theme={theme}
              onShowStats={() => setShowStats(true)}
            />
            <GameBoard />
            <WinOverlay timerFormatted={timer.formatted} />
            <StatsDialog open={showStats} onClose={() => setShowStats(false)} />

            {/* Drag ghost */}
            {dragState.isDragging && dragState.cards.length > 0 && (
              <div
                className="fixed pointer-events-none z-[200]"
                style={{
                  left: dragState.currentPos.x - dragState.offset.x,
                  top: dragState.currentPos.y - dragState.offset.y,
                  willChange: 'left, top',
                }}
              >
                {dragState.cards.map((card, i) => (
                  <Card
                    key={`${card.suit}-${card.value}`}
                    card={card}
                    style={{ top: i * 36, zIndex: i + 1, boxShadow: '4px 6px 16px rgba(0,0,0,0.45)' }}
                  />
                ))}
              </div>
            )}

            {/* Flying cards — rAF-driven smooth animation */}
            {flyingCards.map((fc) => (
              <FlyingCard key={fc.id} data={fc} onDone={() => handleFlyDone(fc.id)} />
            ))}

            {/* Toast message */}
            {state.message && (
              <div className="fixed bottom-6 left-1/2 -translate-x-1/2 z-50 toast-enter">
                <div className="text-black text-sm px-5 py-3 font-bold" style={{ background: '#ece9d8', border: '2px outset #ddd' }}>
                  {state.message.text}
                </div>
              </div>
            )}
          </div>
        </FlyContext.Provider>
      </DragContext.Provider>
    </GameContext.Provider>
  );
}

export default App;
