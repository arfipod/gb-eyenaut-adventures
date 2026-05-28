# Architecture

## Tile World

The prototype uses a fixed 128 by 18 active world stored in WRAM. Each tile is one byte: empty, dirt, grass, stone, wood, leaves, planks, workbench, or torch. The renderer draws a 32 by 18 background slice around the camera so the logical world can be wider than the Game Boy background map.

## Chunks

The active world is divided into 16 chunks of 8 columns. `chunk.c` procedurally generates surface height, caves, trees, and basic underground layers per chunk. The next step is to keep only nearby chunks in WRAM and reload distant chunks from generator/save data.

## Collision

Collision is tile-based. The player sprite is 8 by 16 pixels, but movement uses a 6 by 8 pixel hitbox on the lower half of the sprite so decorative head pixels do not block tight gaps. Movement tests the box corners against solid world tiles before applying horizontal or vertical movement.

## Render Loop

The loop updates input, player physics, camera, chunk bookkeeping, background tiles, and sprite position. Redrawing the whole tiny background is acceptable for this first prototype, but a real game should only update changed tiles and newly visible columns or rows.

## Camera

The camera follows the player horizontally and clamps to the active world width. Rendering uses the integer tile part of the camera to choose the world slice, and the low three pixel bits to scroll the background smoothly.

## Hardware Constraints

The design avoids large dynamic structures, high sprite counts, and per-pixel effects. The original Game Boy is strongest when most gameplay is expressed as tile changes, simple sprites, and predictable update work per frame.
