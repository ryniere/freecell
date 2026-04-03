import { useRef, useEffect, useState } from 'react';
import { FreeCellSlot } from './FreeCellSlot';
import { FoundationSlot } from './FoundationSlot';
import { TableauColumn } from './TableauColumn';
import { useGameState } from '../hooks/useGameState';

const BOARD_W = 1080;

export function GameBoard() {
  const { dispatch } = useGameState();
  const containerRef = useRef<HTMLDivElement>(null);
  const [scale, setScale] = useState(1);

  useEffect(() => {
    const updateScale = () => {
      const width = window.innerWidth;
      if (width < BOARD_W + 32) {
        setScale(Math.min(1, (width - 16) / BOARD_W));
      } else {
        setScale(1);
      }
    };
    updateScale();
    window.addEventListener('resize', updateScale);
    return () => window.removeEventListener('resize', updateScale);
  }, []);

  const handleBoardClick = (e: React.MouseEvent) => {
    if (e.target === e.currentTarget) {
      dispatch({ type: 'CLEAR_SELECTION' });
    }
  };

  return (
    <div className="flex-1 overflow-hidden" onClick={handleBoardClick}>
      <div
        ref={containerRef}
        className="mx-auto origin-top"
        style={{ width: BOARD_W, padding: '16px 12px', transform: `scale(${scale})` }}
      >
        {/* Top row: free cells + foundations */}
        <div style={{ display: 'flex', justifyContent: 'space-between', marginBottom: 28, gap: 10 }}>
          <div style={{ display: 'flex', gap: 10 }}>
            {[0, 1, 2, 3].map(i => (
              <FreeCellSlot key={i} index={i} />
            ))}
          </div>
          <div style={{ display: 'flex', gap: 10 }}>
            {[0, 1, 2, 3].map(i => (
              <FoundationSlot key={i} index={i} />
            ))}
          </div>
        </div>

        {/* Tableau */}
        <div style={{ display: 'grid', gridTemplateColumns: 'repeat(8, 1fr)', gap: 10 }}>
          {[0, 1, 2, 3, 4, 5, 6, 7].map(i => (
            <TableauColumn key={i} index={i} />
          ))}
        </div>
      </div>
    </div>
  );
}
