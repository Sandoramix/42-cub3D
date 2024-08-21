# CUB3D

Cub3D is a [42](https://42.fr/)'s School project where the main goal is to make a first-person 3D representation of a maze by using raycasting.

---

## Supported OS

Theoretically it should work on both Linux and MacOS, but... the keybindings and the `mlx` seem to differ between these OS.

So for now it only supports `Linux` systems.

## Build prerequisites

All tools you might need to build this project:


- `make`
- `build-essential` (C compilers)
- `wget`
- `xorg`
- `libxext-dev`
- `libbsd-dev`
- `unzip`


(Debian/Ubuntu)
```bash
sudo apt install make build-essential wget xorg libxext-dev libbsd-dev unzip
```

### How to build

To build the program you have just to run:
```bash
make
```

---

## How to play

`cub3D` requires one argument which should be the file with texture configurations and the actual map.
there are a few sample maps in [`assets/maps`](assets/maps) folder.

E.g.:
```bash
./cub3D assets/maps/small.cub
```

### Keybindings

These are the implemented keybindings:

#### Player Movement

- **`w`**: Move forward
- **`a`**: Move left
- **`s`**: Move backwards
- **`d`**: Move right

#### Camera movement

- **`Up arrow`**: Look up
- **`Down arrow`**: Look down
- **`Left arrow`**: Look left
- **`Right arrow`**: Look right

#### QUIT

- **`ESC`**: Quit the game

#### Extra features

- **`Space`**: Jump
- **`PageUp`**: Minimap zoom in
- **`PageDown`**: Minimap zoom out
- **`Left Shift`**: Sprint
- **`Left Control`**: Squat
- **`Left Alt`**: Guard mode (yeah it's useless but it's beautiful)

---

#### What is it made of

The game itself is made entirely in C.
The graphics library used here is a **42**'s wrapper for `Xlib` called `mlx`.
Most crazy part is that the whole project (except for `mlx`) is wrote by following [`norminette`](https://github.com/42School/norminette/blob/master/pdf/en.norm.pdf)'s rules... :P
