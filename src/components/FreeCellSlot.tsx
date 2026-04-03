import { useEffect, useRef } from 'react';
import { useGameState, canDropOn } from '../hooks/useGameState';
import { useDrag, useFly } from '../App';
import { Card, CARD_W, CARD_H } from './Card';
import { canPlaceOnFoundation } from '../game-logic';
import { registerDropZone, unregisterDropZone } from '../hooks/useDragAndDrop';

interface FreeCellSlotProps {
  index: number;
}

export function FreeCellSlot({ index }: FreeCellSlotProps) {
  const { state, dispatch } = useGameState();
  const drag = useDrag();
  const fly = useFly();
  const card = state.freeCells[index];
  const isSelected = state.selection?.type === 'freecell' && state.selection.index === index;
  const isHighlighted = state.selection && !card && canDropOn(state, { type: 'freecell', index });
  const ref = useRef<HTMLDivElement>(null);
  const cardRef = useRef<HTMLDivElement>(null);
  const isDragSource = drag?.isDragging && drag.dragSource?.type === 'freecell' && drag.dragSource.index === index;

  useEffect(() => {
    const id = `freecell-${index}`;
    if (ref.current) registerDropZone(id, { type: 'freecell', index }, ref.current);
    return () => unregisterDropZone(id);
  }, [index]);

  const handleClick = () => {
    dispatch({ type: 'SELECT', selection: { type: 'freecell', index } });
  };

  const handleDoubleClick = async () => {
    if (!card || !fly) return;
    // Find which foundation accepts this card
    for (let f = 0; f < 4; f++) {
      if (canPlaceOnFoundation(card, f, state.foundations)) {
        const sourceEl = cardRef.current;
        if (sourceEl) {
          await fly.flyToFoundation(card, sourceEl, f);
        }
        dispatch({ type: 'MOVE', source: { type: 'freecell', index }, dest: { type: 'foundation', index: f } });
        return;
      }
    }
  };

  const handlePointerDown = (e: React.PointerEvent) => {
    if (!drag || !card) return;
    drag.onPointerDown(e, { type: 'freecell', index }, [card]);
  };

  return (
    <div
      ref={ref}
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
      {card ? (
        <div ref={cardRef}>
          <Card
            card={card}
            selected={isSelected && !drag?.isDragging}
            onClick={handleClick}
            onDoubleClick={handleDoubleClick}
            onPointerDown={handlePointerDown}
            style={{ position: 'relative', opacity: isDragSource ? 0.2 : undefined }}
          />
        </div>
      ) : null}
    </div>
  );
}
