import { useGameState } from '../hooks/useGameState';
import { isSoundEnabled, setSoundEnabled } from '../sound';
import { useState } from 'react';

interface HeaderProps {
  timerFormatted: string;
  onToggleTheme: () => void;
  theme: 'dark' | 'light';
  onShowStats: () => void;
}

export function Header({ timerFormatted, onToggleTheme, theme, onShowStats }: HeaderProps) {
  const { state, dispatch } = useGameState();
  const [soundOn, setSoundOn] = useState(isSoundEnabled);

  const toggleSound = () => {
    setSoundEnabled(!soundOn);
    setSoundOn(!soundOn);
  };

  return (
    <header className="win-toolbar px-3 py-1.5 flex items-center justify-between flex-wrap gap-2">
      <div className="flex items-center gap-1">
        <span className="text-sm font-bold text-[#003399]" style={{ fontFamily: "'Tahoma', sans-serif" }}>
          FreeCell
        </span>
        <span className="text-[10px] text-gray-500 ml-1">INF1301 PUC-Rio</span>
      </div>

      <div className="flex items-center gap-4 text-[12px] text-gray-700" style={{ fontFamily: "'Tahoma', sans-serif" }}>
        <span>Movimentos: <strong className="text-black">{state.moves}</strong></span>
        <span>Tempo: <strong className="text-black">{timerFormatted}</strong></span>
      </div>

      <div className="flex items-center gap-0.5">
        <button onClick={() => dispatch({ type: 'NEW_GAME' })} className="header-btn" title="Novo Jogo (Ctrl+N)">
          Novo Jogo
        </button>
        <button onClick={() => dispatch({ type: 'UNDO' })} className="header-btn" title="Desfazer (Ctrl+Z)">
          Desfazer
        </button>
        <button onClick={() => dispatch({ type: 'SAVE' })} className="header-btn" title="Salvar">
          Salvar
        </button>
        <button onClick={() => dispatch({ type: 'LOAD' })} className="header-btn" title="Carregar">
          Carregar
        </button>
        <button onClick={onShowStats} className="header-btn" title="Estatisticas">
          Stats
        </button>
        <button onClick={toggleSound} className="header-btn" title={soundOn ? 'Mudo' : 'Som'}>
          {soundOn ? '🔊' : '🔇'}
        </button>
        <button onClick={onToggleTheme} className="header-btn" title="Tema">
          {theme === 'dark' ? '☀️' : '🌙'}
        </button>
      </div>
    </header>
  );
}
