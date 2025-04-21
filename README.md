<h1 align="center">
	cub3D (Projects at 42tokyo)
</h1>

<p align="center">
	<b><i>Final Score: 105/100 (work in progress)</i></b><br>
</p>

> A RayCaster built with MiniLibX

# 💡 Overview
This project is inspired by the classic FPS game "Wolfenstein 3D". It implements a pseudo-3D environment using a raycasting algorithm, allowing a player to navigate a maze from a first-person perspective.

`cub3D` was my first experience creating a graphical engine using low-level rendering techniques, requiring a solid understanding of math, memory management, and user input handling.

## Features

### Mandatory

- Raycasting engine using the DDA (Digital Differential Analysis) algorithm
- Texture-mapped walls with direction-based textures (N, S, E, W)
- Floor and ceiling color rendering
- Player movement with `W`, `A`, `S`, `D` and rotation with arrow keys
- Correct parsing and validation of `.cub` scene description files
- Graceful program exit via ESC key or window close
- Input handling via MiniLibX
- Map validation: wall-closed, valid characters, single spawn point

### Bonus

- **Wall collision detection**

---

## How to Build & Run

### Dependencies

- `gcc`
- `make`
- `MiniLibX`
- `libc`
- `math.h` (linked with `-lm`)

### Build

```bash
make

# run
./cub3D <path_to_cub_file>
```

## Controls

| Key         | Action                      |
|-------------|-----------------------------|
| `W`         | Move forward                |
| `S`         | Move backward               |
| `A`         | Strafe left                 |
| `D`         | Strafe right                |
| `←`         | Rotate left                 |
| `→`         | Rotate right                |
| `ESC`       | Exit                        |

## Example `.cub` File

```plaintext
NO ./textures/texture_north.xpm
SO ./textures/texture_south.xpm
WE ./textures/texture_west.xpm
EA ./textures/texture_east.xpm

F 255,0,0
C 0,255,0

111111
100001
1000N1
111111
```

## Technical Highlights

- Raycasting: Implemented from scratch using the DDA algorithm to compute wall intersections.
- Parser: Robust .cub file parser with strict validation and error handling.
- MiniLibX: Used for rendering, event management, and buffer control.
- Mathematics: Heavy use of trigonometry and vector arithmetic for spatial reasoning.

## Known Limitations

- No animated sprites or minimap
- Bonus features are limited to wall collision only
- No mouse-based view rotation

## What I Learned

- Fundamentals of 3D rendering through raycasting
- Real-time graphics programming with MiniLibX
- Input handling in graphical environments
- Writing efficient, modular C code using custom libraries
- The importance of robust parsing and edge-case testing
