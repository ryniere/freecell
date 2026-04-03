import type { Card as CardType } from '../types';
import { SUIT_SYMBOLS, SUIT_COLORS, VALUE_NAMES } from '../types';

interface CardProps {
  card: CardType;
  selected?: boolean;
  dimmed?: boolean;
  style?: React.CSSProperties;
  onClick?: (e: React.MouseEvent) => void;
  onDoubleClick?: (e: React.MouseEvent) => void;
  onPointerDown?: (e: React.PointerEvent) => void;
  className?: string;
  'data-card-index'?: number;
}

export const CARD_W = 100;
export const CARD_H = 140;

export function Card({ card, selected, dimmed, style, onClick, onDoubleClick, onPointerDown, className = '', ...rest }: CardProps) {
  const color = SUIT_COLORS[card.suit];
  const symbol = SUIT_SYMBOLS[card.suit];
  const name = VALUE_NAMES[card.value];
  const isRed = color === 'red';
  const suitColor = isRed ? '#d40000' : '#111111';
  const dimBg = '#eaeade';

  return (
    <div
      className={`game-card absolute cursor-pointer select-none ${selected ? 'card-selected z-50' : ''} ${className}`}
      style={{
        width: CARD_W,
        height: CARD_H,
        background: dimmed ? dimBg : '#ffffff',
        border: selected ? '2px solid #003cc8' : '1px solid #555',
        borderRadius: 5,
        boxShadow: selected
          ? '0 0 0 2px #4488ff, 2px 3px 6px rgba(0,0,0,0.4)'
          : '1px 2px 3px rgba(0,0,0,0.25)',
        ...style,
      }}
      onClick={onClick}
      onDoubleClick={onDoubleClick}
      onPointerDown={onPointerDown}
      {...rest}
    >
      {/* Top-left value + suit */}
      <div style={{
        position: 'absolute',
        top: 5,
        left: 6,
        color: suitColor,
        fontFamily: "'Georgia', 'Times New Roman', serif",
        fontWeight: 700,
        fontSize: 15,
        lineHeight: 1.1,
        textAlign: 'center',
      }}>
        <div>{name}</div>
        <div style={{ fontSize: 16 }}>{symbol}</div>
      </div>

      {/* Center — large suit symbol */}
      <div style={{
        position: 'absolute',
        inset: 0,
        display: 'flex',
        alignItems: 'center',
        justifyContent: 'center',
        color: suitColor,
        fontSize: card.value === 1 ? 48 : 34,
        lineHeight: 1,
        pointerEvents: 'none',
      }}>
        {symbol}
      </div>

      {/* Bottom-right value + suit (rotated) */}
      <div style={{
        position: 'absolute',
        bottom: 5,
        right: 6,
        color: suitColor,
        fontFamily: "'Georgia', 'Times New Roman', serif",
        fontWeight: 700,
        fontSize: 15,
        lineHeight: 1.1,
        textAlign: 'center',
        transform: 'rotate(180deg)',
      }}>
        <div>{name}</div>
        <div style={{ fontSize: 16 }}>{symbol}</div>
      </div>
    </div>
  );
}
