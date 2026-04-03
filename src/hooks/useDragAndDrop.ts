import { useState, useCallback, useRef } from 'react';
import type { Selection, Card } from '../types';

interface DragState {
  isDragging: boolean;
  source: Selection | null;
  cards: Card[];
  startPos: { x: number; y: number };
  currentPos: { x: number; y: number };
  offset: { x: number; y: number };
  elementRect: DOMRect | null;
}

const CLICK_THRESHOLD = 5;

const initialDragState: DragState = {
  isDragging: false,
  source: null,
  cards: [],
  startPos: { x: 0, y: 0 },
  currentPos: { x: 0, y: 0 },
  offset: { x: 0, y: 0 },
  elementRect: null,
};

export interface DropZone {
  id: string;
  selection: Selection;
  element: HTMLElement;
}

// Global registry of drop zones
const dropZones: Map<string, DropZone> = new Map();

export function registerDropZone(id: string, selection: Selection, element: HTMLElement) {
  dropZones.set(id, { id, selection, element });
}

export function unregisterDropZone(id: string) {
  dropZones.delete(id);
}

function findDropZone(x: number, y: number, sourceId: string): DropZone | null {
  for (const [id, zone] of dropZones) {
    if (id === sourceId) continue;
    const rect = zone.element.getBoundingClientRect();
    if (x >= rect.left && x <= rect.right && y >= rect.top && y <= rect.bottom) {
      return zone;
    }
  }
  return null;
}

export function useDragAndDrop(
  onMove: (source: Selection, dest: Selection) => void,
  onSelect: (selection: Selection) => void,
) {
  const [dragState, setDragState] = useState<DragState>(initialDragState);
  const dragRef = useRef<DragState>(initialDragState);

  const startDrag = useCallback((
    e: React.PointerEvent,
    source: Selection,
    cards: Card[],
  ) => {
    const rect = (e.currentTarget as HTMLElement).getBoundingClientRect();
    const state: DragState = {
      isDragging: false, // will become true on move
      source,
      cards,
      startPos: { x: e.clientX, y: e.clientY },
      currentPos: { x: e.clientX, y: e.clientY },
      offset: { x: e.clientX - rect.left, y: e.clientY - rect.top },
      elementRect: rect,
    };
    dragRef.current = state;
    setDragState(state);
    (e.currentTarget as HTMLElement).setPointerCapture(e.pointerId);
  }, []);

  const moveDrag = useCallback((e: React.PointerEvent) => {
    const ref = dragRef.current;
    if (!ref.source) return;

    const dx = e.clientX - ref.startPos.x;
    const dy = e.clientY - ref.startPos.y;

    if (!ref.isDragging && Math.sqrt(dx * dx + dy * dy) < CLICK_THRESHOLD) {
      return; // Not yet a drag
    }

    const newState: DragState = {
      ...ref,
      isDragging: true,
      currentPos: { x: e.clientX, y: e.clientY },
    };
    dragRef.current = newState;
    setDragState(newState);
  }, []);

  const endDrag = useCallback((e: React.PointerEvent) => {
    const ref = dragRef.current;
    if (!ref.source) {
      dragRef.current = initialDragState;
      setDragState(initialDragState);
      return;
    }

    if (!ref.isDragging) {
      // Was a click, not a drag
      onSelect(ref.source);
      dragRef.current = initialDragState;
      setDragState(initialDragState);
      return;
    }

    // Find drop target
    const sourceId = `${ref.source.type}-${ref.source.index}`;
    const zone = findDropZone(e.clientX, e.clientY, sourceId);
    if (zone) {
      onMove(ref.source, zone.selection);
    }

    dragRef.current = initialDragState;
    setDragState(initialDragState);
  }, [onMove, onSelect]);

  const cancelDrag = useCallback(() => {
    dragRef.current = initialDragState;
    setDragState(initialDragState);
  }, []);

  return {
    dragState,
    startDrag,
    moveDrag,
    endDrag,
    cancelDrag,
  };
}
