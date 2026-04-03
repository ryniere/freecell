import { useEffect, useRef } from 'react';
import { useGameState, canDropOn } from '../hooks/useGameState';
import { useDrag } from '../App';
import { Card, CARD_W, CARD_H } from './Card';
import { SUIT_SYMBOLS, SUIT_COLORS } from '../types';
import { registerDropZone, unregisterDropZone } from '../hooks/useDragAndDrop';

interface FoundationSlotProps {
  index: number;
}

export function FoundationSlot({ index }: FoundationSlotProps) {
  const { state, dispatch } = useGameState();
  const drag = useDrag();
  const foundation = state.foundations[index];
  const topCard = foundation.length > 0 ? foundation[foundation.length - 1] : null;
  const isHighlighted = state.selection && canDropOn(state, { type: 'foundation', index });
  const symbol = SUIT_SYMBOLS[index];
  const color = SUIT_COLORS[index];
  const ref = useRef<HTMLDivElement>(null);

  useEffect(() => {
    const id = `foundation-${index}`;
    if (ref.current) registerDropZone(id, { type: 'foundation', index }, ref.current);
    return () => unregisterDropZone(id);
  }, [index]);

  const handleClick = () => {
    dispatch({ type: 'SELECT', selection: { type: 'foundation', index } });
  };

  return (
    <div
      ref={ref}
      data-foundation-index={index}
      className={`slot-empty ${isHighlighted ? 'slot-highlight' : ''}`}
      style={{
        position: 'relative',
        width: CARD_W,
        height: CARD_H,
        display: 'flex',
        alignItems: 'center',
        justifyContent: 'center',
      }}
      onClick={handleClick}
      onPointerMove={drag?.onPointerMove}
      onPointerUp={drag?.onPointerUp}
    >
      {topCard ? (
        <Card
          card={topCard}
          onClick={handleClick}
          style={{ position: 'relative' }}
        />
      ) : (
        <span style={{
          fontSize: 36,
          color: color === 'red' ? '#550000' : '#003800',
          opacity: 0.5,
        }}>
          {symbol}
        </span>
      )}
      {foundation.length > 0 && (
        <div style={{
          position: 'absolute',
          bottom: -18,
          left: 0,
          right: 0,
          textAlign: 'center',
          fontSize: 11,
          fontWeight: 700,
          color: '#bbee66',
        }}>
          {foundation.length}/13
        </div>
      )}
    </div>
  );
}
