let enabled = localStorage.getItem('freecell_sound') !== 'off';

// We'll use the Web Audio API to generate simple sounds
let audioCtx: AudioContext | null = null;

function getCtx(): AudioContext {
  if (!audioCtx) audioCtx = new AudioContext();
  return audioCtx;
}

function playTone(freq: number, duration: number, type: OscillatorType = 'sine', volume = 0.15) {
  if (!enabled) return;
  try {
    const ctx = getCtx();
    const osc = ctx.createOscillator();
    const gain = ctx.createGain();
    osc.type = type;
    osc.frequency.value = freq;
    gain.gain.value = volume;
    gain.gain.exponentialRampToValueAtTime(0.001, ctx.currentTime + duration);
    osc.connect(gain);
    gain.connect(ctx.destination);
    osc.start();
    osc.stop(ctx.currentTime + duration);
  } catch {
    // Ignore audio errors
  }
}

export function playCardPlace() {
  playTone(800, 0.08, 'sine', 0.1);
}

export function playCardError() {
  playTone(200, 0.15, 'square', 0.08);
}

export function playShuffle() {
  for (let i = 0; i < 5; i++) {
    setTimeout(() => playTone(400 + Math.random() * 400, 0.05, 'sine', 0.06), i * 40);
  }
}

export function playWin() {
  const notes = [523, 659, 784, 1047];
  notes.forEach((freq, i) => {
    setTimeout(() => playTone(freq, 0.3, 'sine', 0.12), i * 150);
  });
}

export function playUndo() {
  playTone(500, 0.06, 'triangle', 0.08);
}

export function playAutoMove() {
  playTone(1000, 0.1, 'sine', 0.08);
}

export function isSoundEnabled(): boolean {
  return enabled;
}

export function setSoundEnabled(on: boolean): void {
  enabled = on;
  localStorage.setItem('freecell_sound', on ? 'on' : 'off');
}
