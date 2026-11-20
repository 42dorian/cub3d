*This project has been created as part of the 42 curriculum by dabdulla, bguhty.*

## Description

**cub3D** is a 3D maze explorer built in C using the **MiniLibX** graphics library. The goal of the project is to explore raycasting principles by rendering a dynamic 3D first-person perspective inside a maze from a 2D map defined in a `.cub` scene file. It uses the **DDA (Digital Differential Analyzer) raycasting** algorithm and supports directional wall textures (`NO`, `SO`, `WE`, `EA`), custom floor and ceiling RGB colors, map validation via flood-fill, wall collision, and smooth player movement and rotation.

## Instructions

### Compilation
Compile the project using `make`:
```bash
make
```
Available Makefile rules: `make`, `make clean`, `make fclean`, `make re`.

### Execution
Run the executable by passing a valid `.cub` map file:
```bash
./cub3d path/to/map.cub
```

### Controls
- `W` / `S` — Move forward / backward
- `A` / `D` — Move left / right
- `←` / `→` — Rotate camera left / right
- `ESC` — Close the window and exit

## Libraries used

- **MiniLibX** — X11 graphics library for window creation, image buffering, and event handling
- **libft** — custom C library for string and memory utilities
- **get_next_line** — line-by-line file reader used for `.cub` file parsing

## Resources

### References & Tutorials
- [Lode's Computer Graphics Tutorial — Raycasting](https://lodev.org/cgtutor/raycasting.html)
- [Make Your Own Raycaster Part 1 (YouTube)](https://youtu.be/gYRrGTC7GtA?si=ZwxpbrxgSvuLrACZ)
- [Raycasting & DDA Tutorial (YouTube)](https://youtu.be/g8p7nAbDz6Y?si=0nRdcJ15YZ24yTW0)
- [Raycasting Explanation (YouTube)](https://youtu.be/G9i78WoBBIU?si=xuL9vxUv0mToqJm1)

### Use of AI
AI was used during the project for:
- **Raycasting & Math Concepts:** Helping understand the DDA algorithm and trigonometric/math functions (`cos`, `sin`, `fabs`, `floor`) and how to apply them effectively in raycasting and player rotation.
- **Documentation:** Structuring and formatting the `README.md` file.
