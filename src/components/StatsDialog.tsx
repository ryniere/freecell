import { getStats } from '../storage';

interface StatsDialogProps {
  open: boolean;
  onClose: () => void;
}

export function StatsDialog({ open, onClose }: StatsDialogProps) {
  if (!open) return null;

  const stats = getStats();
  const winRate = stats.gamesPlayed > 0 ? Math.round((stats.gamesWon / stats.gamesPlayed) * 100) : 0;
  const bestTime = stats.bestTime !== null
    ? `${Math.floor(stats.bestTime / 60)}:${(stats.bestTime % 60).toString().padStart(2, '0')}`
    : '--';

  return (
    <div className="fixed inset-0 z-[100] flex items-center justify-center" style={{ background: 'rgba(0,0,0,0.4)' }} onClick={onClose}>
      <div
        onClick={e => e.stopPropagation()}
        style={{
          background: '#ece9d8',
          border: '2px solid',
          borderColor: '#fff #808080 #808080 #fff',
          padding: '6px',
          minWidth: '300px',
        }}
      >
        {/* Title bar */}
        <div
          className="px-3 py-1 mb-3 text-white text-sm font-bold text-left"
          style={{ background: 'linear-gradient(to right, #0054e3, #2490f0)' }}
        >
          Estatisticas
        </div>
        <div className="px-4 pb-3">
          <table className="w-full text-sm text-black" style={{ fontFamily: "'Tahoma', sans-serif" }}>
            <tbody>
              <StatRow label="Jogos" value={stats.gamesPlayed} />
              <StatRow label="Vitorias" value={stats.gamesWon} />
              <StatRow label="Taxa de Vitoria" value={`${winRate}%`} />
              <StatRow label="Melhor Tempo" value={bestTime} />
              <StatRow label="Menos Movimentos" value={stats.bestMoves ?? '--'} />
              <StatRow label="Melhor Sequencia" value={stats.bestStreak} />
              <StatRow label="Sequencia Atual" value={stats.currentStreak} />
            </tbody>
          </table>

          <div className="flex justify-center mt-3">
            <button onClick={onClose} className="header-btn px-8 py-1 text-sm">
              Fechar
            </button>
          </div>
        </div>
      </div>
    </div>
  );
}

function StatRow({ label, value }: { label: string; value: string | number }) {
  return (
    <tr>
      <td className="py-1 pr-4 text-gray-700">{label}:</td>
      <td className="py-1 font-bold text-right">{value}</td>
    </tr>
  );
}
