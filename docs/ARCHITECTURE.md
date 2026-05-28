# Architecture

## Tile World

The prototype uses a fixed 32 by 18 tile world stored in WRAM. Each tile is one byte: empty, dirt, grass, or stone. This is intentionally tiny so the code stays readable before introducing streaming.

## Chunks

The future world should be divided into compact chunks. Only nearby chunks should live in WRAM; distant chunks should be generated, streamed from ROM, or loaded from save data. `chunk.c` is a placeholder for that step.

## Collision

Collision is tile-based. The player is an 8 by 8 pixel box. Movement tests the box corners against solid world tiles before applying horizontal or vertical movement.

## Render Loop

The loop updates input, player physics, camera, chunk bookkeeping, background tiles, and sprite position. Redrawing the whole tiny background is acceptable for this first prototype, but a real game should only update changed tiles and newly visible columns or rows.

## Camera

The camera follows the player horizontally and clamps to the small world width. On DMG this maps directly to background scroll registers.

## Hardware Constraints

The design avoids large dynamic structures, high sprite counts, and per-pixel effects. The original Game Boy is strongest when most gameplay is expressed as tile changes, simple sprites, and predictable update work per frame.
