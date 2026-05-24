# Tuilip

Tiny text-based user interface rendering library for C.

## What is it?

Tuilip is a minimal TUI renderer for building terminal UIs in C. It handles the tedious buffering and coordinate management so you can focus on drawing.

## Core Functions

- **`DrawComponent()`** – Render raw text/strings
- **`DrawRectangle()`** – Draw prefab rectangles/boxes
- **`AddComponentTo()`** – Concatenate components together
- **`Render()`** – Print everything at once (no flicker)

## Usage

```c
#include Tuilip/src/header/Tuilip.h

int main() {
    Component String = DrawComponent(
        (Component) {.buffer = "This is a test!\n\n"},
        (Vec2) {.x = 1 , .y = 9},
        Reset,
        White,
        Default
    );
    Component Rectangle = DrawRectangle(
        (RectStruct) {
            .position = {0 , 0},
            .size = {40 , 10},
            .character = SINGLE,
            .style = Bold,
            .foreground = Blue,
            .background = Default
        }
    );

    AddComponentTo(String , &Rectangle);
    Render(Rectangle);

    return 0;
}
```
![result](https://github.com/Draconic02171/Tuilip/blob/main/Screenshot-2026-05-24_20-14-37-396.png)

## Features

- Zero external dependencies
- Single-pass rendering (no flickering)
- Stack-allocated, minimal overhead
- Simple API
