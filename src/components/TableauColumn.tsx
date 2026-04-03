import { useEffect, useRef, useCallback } from 'react';
import { useGameState, canDropOn } from '../hooks/useGameState';
import { useDrag, useFly } from '../App';
import { Card, CARD_W, CARD_H } from './Card';
import { getSequenceStart, canPlaceOnFoundation } from '../game-logic';
import { registerDropZone, unregisterDropZone } from '../hooks/useDragAndDrop';

const STACK_OVERLAP = 36;

interface TableauColumnProps {
  index: number;
}

export function TableauColumn({ index }: TableauColumnProps) {
  const { state, dispatch } = useGameState();
  const drag = useDrag();
  const fly = useFly();
  const column = state.tableau[index];
  const seqStart = getSequenceStart(column);
  const isHighlighted = state.selection && canDropOn(state, { type: 'tableau', index });
  const ref = useRef<HTMLDivElement>(null);

  useEffect(() => {
    const id = `tableau-${index}`;
    if (ref.current) {
      registerDropZone(id, { type: 'tableau', index }, ref.current);
    }
    return () => unregisterDropZone(id);
  }, [index]);

  const overlap = column.length > 1 ? Math.min(STACK_OVERLAP, Math.floor(400 / column.length)) : STACK_OVERLAP;
  const columnHeight = column.length > 0 ? CARD_H + (column.length - 1) * overlap : CARD_H;

  const isDragSource = drag?.isDragging && drag.dragSource?.type === 'tableau' && drag.dragSource.index === index;
  const dragFromIdx = isDragSource && drag.dragSource?.cardIndex !== undefined ? drag.dragSource.cardIndex : column.length;

  const handleColumnClick = () => {
    if (column.length === 0) {
      dispatch({ type: 'SELECT', selection: { type: 'tableau', index } });
    }
  };

  const handleCardClick = (cardIndex: number) => {
    dispatch({ type: 'SELECT', selection: { type: 'tableau', index, cardIndex } });
  };

  const handleDoubleClick = useCallback(async (cardIndex: number, e: React.MouseEvent) => {
    if (cardIndex !== column.length - 1) return;
    const card = column[cardIndex];
    if (!card || !fly) return;

    // Find which foundation accepts this card
    for (let f = 0; f < 4; f++) {
      if (canPlaceOnFoundation(card, f, state.foundations)) {
        // Find the card element from the event
        const sourceEl = (e.currentTarget as HTMLElement);
        if (sourceEl) {
          await fly.flyToFoundation(card, sourceEl, f);
        }
        dispatch({ type: 'MOVE', source: { type: 'tableau', index }, dest: { type: 'foundation', index: f } });
        return;
      }
    }
  }, [column, state.foundations, fly, dispatch, index]);

  const handlePointerDown = (e: React.PointerEvent, cardIndex: number) => {
    if (!drag) return;
    const cards = column.slice(cardIndex);
    drag.onPointerDown(e, { type: 'tableau', index, cardIndex }, cards);
  };

  return (
    <div
      ref={ref}
      className={`${isHighlighted ? 'slot-highlight' : ''} ${column.length === 0 ? 'slot-empty' : ''}`}
      style={{
        position: 'relative',
        minHeight: CARD_H,
        height: columnHeight,
        borderRadius: 3,
      }}
      onClick={handleColumnClick}
      onPointerMove={drag?.onPointerMove}
      onPointerUp={drag?.onPointerUp}
    >
      {column.map((card, j) => {
        const isInSequence = j >= seqStart;
        const isSelected = state.selection?.type === 'tableau'
          && state.selection.index === index
          && state.selection.cardIndex !== undefined
          && j >= state.selection.cardIndex;
        const isHiddenByDrag = isDragSource && j >= dragFromIdx;

        const dealDelay = state.dealing ? (index * 7 + j) * 30 : 0;

        return (
          <Card
            key={`${card.suit}-${card.value}`}
            card={card}
            selected={isSelected && !drag?.isDragging}
            dimmed={false}
            data-card-index={isInSequence ? j : undefined}
            className={state.dealing ? 'card-dealing' : ''}
            style={{
              top: j * overlap,
              left: 0,
              right: 0,
              zIndex: j + 1,
              position: 'absolute',
              width: '100%',
              opacity: isHiddenByDrag ? 0.2 : undefined,
              animationDelay: state.dealing ? `${dealDelay}ms` : undefined,
            }}
            onClick={(e) => {
              e.stopPropagation();
              handleCardClick(j);
            }}
            onDoubleClick={(e) => {
              e.stopPropagation();
              handleDoubleClick(j, e);
            }}
            onPointerDown={(e) => handlePointerDown(e, j)}
          />
        );
      })}
    </div>
  );
}
