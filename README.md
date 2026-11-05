# SFML Playground

Short, self-contained C++ examples for [SFML 3](https://www.sfml-dev.org/). Each file demonstrates one concept, from opening a window to acceleration and mouse dragging.

The examples cover window and event handling, keyboard and mouse input, delta-time movement, collision detection, textures and sprites, text and audio, and simple physics. Later programs reuse ideas from earlier ones, but every file compiles and runs on its own.

## Programs

| File | What it does |
|---|---|
| `01.cpp` | Basic window and event loop |
| `02.cpp` | Drawing shapes (circle, rectangle) |
| `03.cpp` | Keyboard and mouse input |
| `04.cpp` | Delta-time based movement with WASD |
| `05.cpp` | AABB collision detection |
| `06.cpp` | Loading a texture and drawing a sprite |
| `07.cpp` | Sprite origin, scaling and rotation |
| `08.cpp` | Score text, fonts and sound effects |
| `09.cpp` | A ball bouncing off the screen edges |
| `10.cpp` | Two balls with random velocities and distance-based collision |
| `11.cpp` | Window resizing with a dynamic view |
| `12.cpp` | Acceleration-based movement with resize-aware bounds |
| `13.cpp` | Drag and drop a ball with the mouse |

## Requirements

- A C++17 compiler (g++)
- **SFML 3.x** (the code uses the SFML 3 API, so SFML 2.x will not compile)
- Tested with MSYS2 on Windows

### Installing SFML on MSYS2

Open the **UCRT64** shell and run:

```bash
pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-sfml
```

## Building and running

From the UCRT64 (or MINGW64) shell, in the repo folder:

```bash
g++ -std=c++17 01.cpp -o 01 -lsfml-graphics -lsfml-window -lsfml-system
./01.exe
```

Replace `01` with the program you want to run.

`08.cpp` also uses audio, so it needs one more library:

```bash
g++ -std=c++17 08.cpp -o 08 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
./08.exe
```

If `pkg-config` is installed, you can skip listing libraries:

```bash
g++ -std=c++17 file.cpp -o file $(pkg-config --libs sfml-all)
```

## Assets

Some programs load files from the working directory. Place them next to the executable (or run from the folder that contains them):

| Program | Required files |
|---|---|
| `06.cpp`, `07.cpp` | `mushroom.png` |
| `08.cpp` | `mushroom.png`, `arial.ttf`, `boom.wav` |

If an asset is missing, the program exits immediately without opening a window.

## Controls

| Program | Controls |
|---|---|
| `03.cpp` | `Space` turns the sun red, left click turns the ground white, `Esc` quits |
| `04.cpp` to `08.cpp` | `W` `A` `S` `D` move the sun, `Space` and left click change colors, `Esc` quits |
| `12.cpp` | Arrow keys accelerate the ball, `Esc` quits |
| `13.cpp` | Arrow keys accelerate the ball, click and drag to move it, `Esc` quits |

All programs close with the window's close button.

## Troubleshooting

- **`sfml-graphics-3.dll not found`**: run the executable from the same MSYS2 shell you compiled in, not by double-clicking it.
- **Compile errors about `std::optional` or `sf::VideoMode({...})`**: you likely have SFML 2.x installed. Check with `pacman -Q mingw-w64-ucrt-x86_64-sfml` and upgrade.