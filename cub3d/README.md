*This project has been created as part of the 42 curriculum by kryutaro.*

# cub3D

## Description

cub3D is a first-person maze renderer written in C with MiniLibX. It parses a
`.cub` scene, validates that its map is closed, then uses DDA ray casting to
draw textured walls with separate floor and ceiling colors.

## Instructions

The X11 development dependencies required by the included Linux MiniLibX must
be installed.

```sh
make
./cub3D assets/sample.cub
```

Controls:

- `W`, `A`, `S`, `D`: move
- Left and right arrow keys: rotate
- `ESC` or the window close button: quit

The Makefile provides `all`, `clean`, `fclean`, `re`, and `bonus` rules.

## Scene Format

A scene contains one each of `NO`, `SO`, `WE`, and `EA` texture paths, floor
and ceiling RGB colors (`F` and `C`), followed by a closed map. The map uses
`0`, `1`, spaces, and exactly one player marker: `N`, `S`, `E`, or `W`.

## Resources

- [Lode's Computer Graphics Tutorial: Raycasting](https://lodev.org/cgtutor/raycasting.html)
- [MiniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx)
- The cub3D Version 12.0 subject included in this repository

AI was used to review the implementation against the subject, identify parser
and cleanup edge cases, and assist with refactoring and test-case design. The
resulting code was reviewed and tested locally.
