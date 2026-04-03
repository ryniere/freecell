import { useEffect, useRef } from 'react';
import { useGameState } from '../hooks/useGameState';
import { playWin } from '../sound';

interface WinOverlayProps {
  timerFormatted: string;
}

export function WinOverlay({ timerFormatted }: WinOverlayProps) {
  const { state, dispatch } = useGameState();
  const canvasRef = useRef<HTMLCanvasElement>(null);
  const playedRef = useRef(false);

  useEffect(() => {
    if (!state.won) {
      playedRef.current = false;
      return;
    }
    if (!playedRef.current) {
      playWin();
      playedRef.current = true;
    }

    const canvas = canvasRef.current;
    if (!canvas) return;
    const ctx = canvas.getContext('2d');
    if (!ctx) return;

    canvas.width = window.innerWidth;
    canvas.height = window.innerHeight;

    const particles: { x: number; y: number; vx: number; vy: number; color: string; size: number; life: number }[] = [];
    const colors = ['#FF0000', '#0000FF', '#00FF00', '#FFFF00', '#FF00FF', '#00FFFF'];

    for (let i = 0; i < 150; i++) {
      particles.push({
        x: canvas.width / 2 + (Math.random() - 0.5) * 200,
        y: canvas.height / 2,
        vx: (Math.random() - 0.5) * 12,
        vy: -Math.random() * 15 - 5,
        color: colors[Math.floor(Math.random() * colors.length)],
        size: Math.random() * 6 + 2,
        life: 1,
      });
    }

    let animId: number;
    function animate() {
      ctx!.clearRect(0, 0, canvas!.width, canvas!.height);
      let alive = false;
      for (const p of particles) {
        if (p.life <= 0) continue;
        alive = true;
        p.x += p.vx;
        p.y += p.vy;
        p.vy += 0.3;
        p.life -= 0.008;
        ctx!.globalAlpha = Math.max(0, p.life);
        ctx!.fillStyle = p.color;
        ctx!.fillRect(p.x, p.y, p.size, p.size);
      }
      ctx!.globalAlpha = 1;
      if (alive) animId = requestAnimationFrame(animate);
    }
    animate();
    return () => cancelAnimationFrame(animId);
  }, [state.won]);

  if (!state.won) return null;

  return (
    <div className="fixed inset-0 z-[100] flex items-center justify-center" style={{ background: 'rgba(0,0,0,0.4)' }}>
      <canvas ref={canvasRef} className="absolute inset-0 pointer-events-none" />
      <div
        className="relative z-10 text-center"
        style={{
          background: '#ece9d8',
          border: '2px solid',
          borderColor: '#fff #808080 #808080 #fff',
          padding: '6px',
        }}
      >
        {/* Title bar */}
        <div
          className="px-3 py-1 mb-3 text-white text-sm font-bold text-left"
          style={{ background: 'linear-gradient(to right, #0054e3, #2490f0)' }}
        >
          FreeCell
        </div>
        <div className="px-6 pb-4">
          <div className="text-base text-black mb-1 font-bold">Parabens!!</div>
          <p className="text-sm text-black mb-1">
            Voce venceu em <strong>{state.moves}</strong> movimentos!
          </p>
          <p className="text-xs text-gray-600 mb-4">
            Tempo: {timerFormatted}
          </p>
          <button
            onClick={() => dispatch({ type: 'NEW_GAME' })}
            className="header-btn px-6 py-1 text-sm"
          >
            Jogar Novamente
          </button>
        </div>
      </div>
    </div>
  );
}
