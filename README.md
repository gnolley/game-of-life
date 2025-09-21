
# Game of Life!

This is a basic 64-bit co-ordinate space simulation of Conway's game of life.


 - 64-bit coordinates
 - Loads Life 1.06 files types
 - Outputs simulation snapshots to Life 1.06 files types
 - Basic OpenGL Renderer


## Installation

#### Requirements
- vcpkg
- cmake
    
#### Visual Studio
    1. Install Visual Studio w/ cmake and vcpkg support
    2. Open project as cmake project
    3. Select build configuration (x64 debug, x64 release, arm64 debug, arm64 release)
    4. Generate Solution
    5. (Optional) Install project to export.

#### CMake
    1. cmake ..
    2. cmake --build .
    3. cmake --install <dir>
## CLI Reference

#### Example

```bash
./GameOfLife.exe -f "life_files/stary_glifer.lif" -t 70 -s 100 -o "output.lif"
```


| Option       | Description                                                 |
| :--------    |:------------------------------------------------------------|
| -h, --help   |Shows CLI Help                                               |
| -f,--file    |Path to the life 1.06 file you would like to load.           |
| -o,--output  |Where to output .lif file after simulation                   |
| -t,--ticks   |Number of ticks to simulate. -1 will run until window closed.|
| -w,--width   |Width of the simulation render in pixels. Default 64.        |
| -i,--height  |Height of the simulation render in pixels. Default 64.       |
| -s,--speed   |Tick speed in milliseconds. Default 500.                     |
| -d,--headless|Whether to run the renderer                                  |

