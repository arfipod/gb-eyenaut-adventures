# Memory Budget

## DMG Facts

- Screen: 160 by 144 pixels.
- Background tiles: 8 by 8 pixels.
- Visible background: 20 by 18 tiles.
- Background map: 32 by 32 tile entries in VRAM.
- VRAM: 8 KiB.
- WRAM: 8 KiB.
- OAM: 40 sprites, with a practical limit of 10 sprites per scanline.

## What This Means

A Terraria-like game cannot keep a large world in RAM. A simple byte-per-tile world uses:

```text
32 x 18 = 576 bytes
64 x 32 = 2048 bytes
128 x 64 = 8192 bytes
```

The last example would consume essentially all WRAM before player state, stacks, buffers, inventory, enemies, or save helpers.

## First Approximation

For early development:

- Keep one tiny active world or a few nearby chunks in WRAM.
- Store block IDs as bytes first, then pack later if needed.
- Keep changed tile coordinates in a small queue.
- Use ROM banks for generated or authored terrain templates.
- Avoid large recursive generators or dynamic allocation.

The current prototype world is 576 bytes, leaving enough room for code state while we test mining, placing, collision, and camera behavior.
