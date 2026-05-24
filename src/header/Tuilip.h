#ifndef TUILIP_H
#define TUILIP_H

#define MAX_COMPONENT_BUFFER_SIZE 2048

#define true 1
#define false 0
#define failed -1


typedef enum { SINGLE, DOUBLE } Border;

typedef enum {
    Reset,
    Bold,
    Dim,
    Italic,
    Underline,
    Blink,
    Reverse,
    Hidden,
    StrikeThrough
} CharacterStyle;

typedef enum {
    Black = 0,
    Red = 1,
    Green = 2,
    Yellow = 3,
    Blue = 4,
    Magenta = 5,
    Cyan = 6,
    White = 7,
    Default = 9,
    BrightBlack = 60,
    BrightRed = 61,
    BrightGreen = 62,
    BrightYellow = 63,
    BrightBlue = 64,
    BrightMagenta = 65,
    BrightCyan = 66,
    BrightWhite = 67
} Color;

typedef struct {char Code[8];} Ansi;


typedef struct {
    char buffer[2048];
    int size;
} Component;

typedef struct {
    int x;
    int y;
} Vec2;

typedef struct {
    Vec2            position;
    Vec2            size;
    Border          character;
    CharacterStyle  style;
    Color           foreground;
    Color           background;
} RectStruct;


void        ReCalComponentSize(
    Component       *component
);

Component   DrawRectangle(
    RectStruct       RectInfo
);

Component   DrawComponent(
    Component       RawComponent,
    Vec2            position,
    CharacterStyle  style,
    Color           foreground,
    Color           background
);

int         AddComponentTo(
    Component       Source,
    Component       *Where
);
int         Render(
    Component       RenderBuffer
);


#endif