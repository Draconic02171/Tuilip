#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdarg.h>
#include "header/Time.h"
#include "header/Tuilip.h"

typedef struct {
    char            *top_left;      
    char            *top_right;     
    char            *bottom_left;   
    char            *bottom_right;  
    char            *horizontal;    
    char            *vertical;      
} BorderChars;

static const BorderChars styles[] = {
    [SINGLE] = {
        .top_left = "┌",
        .top_right = "┐",
        .bottom_left = "└",
        .bottom_right = "┘",
        .horizontal = "─",
        .vertical = "│"
    },
    [DOUBLE] = {
        .top_left = "╔",
        .top_right = "╗",
        .bottom_left = "╚",
        .bottom_right = "╝",
        .horizontal = "═",
        .vertical = "║"
    },
};


void ReCalComponentSize(Component *component) {
    component->size = 0;
    for (int i = 0; i < MAX_COMPONENT_BUFFER_SIZE; i ++) {
        if (component->buffer[i] == 0) return;
        component->size ++;
    }
}

Component DrawRectangle(RectStruct RectInfo) {
    RectInfo.position.x ++;
    RectInfo.position.y ++;

    Component RectBuffer = {0};
    int pos = 0;
    const BorderChars Style = styles[RectInfo.character];

    pos += sprintf(&RectBuffer.buffer[pos] , "\033[%d;%dH" , RectInfo.position.y , RectInfo.position.x);

    //building a top rectangle
    pos += sprintf(
            &RectBuffer.buffer[pos],
            "\033[%dm" "\033[%dm" "\033[%dm" ,
            RectInfo.foreground + 30 ,
            RectInfo.background + 40 ,
            RectInfo.style
            );

    for(int i = 0; i < RectInfo.size.x; i ++) {
        if (i == 0)                      pos += sprintf(&RectBuffer.buffer[pos], "%s" , Style.top_left);
        else if (i == RectInfo.size.x-1) pos += sprintf(&RectBuffer.buffer[pos], "%s" , Style.top_right);
        else                             pos += sprintf(&RectBuffer.buffer[pos], "%s" , Style.horizontal);
    }
    pos += sprintf(&RectBuffer.buffer[pos], "\033[%dm" , Reset);


    pos += sprintf(&RectBuffer.buffer[pos] , "\033[%d;%dH" , RectInfo.position.y , RectInfo.position.x); 

    //building a body
    //
    pos += sprintf(
            &RectBuffer.buffer[pos],
            "\033[%dm" "\033[%dm" "\033[%dm" ,
            RectInfo.foreground + 30 ,
            RectInfo.background + 40 ,
            RectInfo.style
            );

    for (int Y = 1; Y < RectInfo.size.y; Y ++) {
        pos += sprintf(&RectBuffer.buffer[pos] ,"\033[%d;%dH", RectInfo.position.y + Y , RectInfo.position.x);
        pos += sprintf(&RectBuffer.buffer[pos] , "%s" , Style.vertical);
        pos += sprintf(&RectBuffer.buffer[pos] , "\033[%d;%dH", RectInfo.position.y + Y , RectInfo.position.x + RectInfo.size.x - 1);
        pos += sprintf(&RectBuffer.buffer[pos] , "%s" , Style.vertical);
    }
    pos += sprintf(&RectBuffer.buffer[pos], "\033[%dm" , Reset);

    // //new line
    pos += sprintf(&RectBuffer.buffer[pos] , "\033[%d;%dH", RectInfo.position.y + RectInfo.size.y , RectInfo.position.x);

    pos += sprintf(
            &RectBuffer.buffer[pos],
            "\033[%dm" "\033[%dm" "\033[%dm" ,
            RectInfo.foreground + 30 ,
            RectInfo.background + 40 ,
            RectInfo.style
            );

    for(int i = 0; i < RectInfo.size.x; i ++) {
        if      (i == 0)                       pos += sprintf(&RectBuffer.buffer[pos] , "%s" , Style.bottom_left);
        else if (i == RectInfo.size.x - 1)     pos += sprintf(&RectBuffer.buffer[pos] , "%s" , Style.bottom_right);
        else                                   pos += sprintf(&RectBuffer.buffer[pos] , "%s" , Style.horizontal);
    }

    pos += sprintf(&RectBuffer.buffer[pos], "\033[%dm" , Reset);
    pos += sprintf(&RectBuffer.buffer[pos] ,"\033[%d;%dH" , RectInfo.position.y + RectInfo.size.y + 1, 0);

    RectBuffer.size = pos;
    return RectBuffer;
}
Component DrawComponent(Component RawComponent, Vec2 position, CharacterStyle style, Color foreground, Color background) {
    
    ReCalComponentSize(&RawComponent);
    position.x ++;
    position.y ++;

    Component component = {0};
    int pos = 0;

    pos += sprintf(&component.buffer[pos] ,"\033[%d;%dH" , position.y, position.x);
    pos += sprintf(&component.buffer[pos], "\033[%d;%d;%dm" , style , foreground + 30, background + 40);
    pos += sprintf(&component.buffer[pos], "%s" , RawComponent.buffer);
    pos += sprintf(&component.buffer[pos], "\033[%dm" , Reset);

    component.size = pos;

    return component; 
}


int AddComponentTo(Component Source, Component *Where) {

    ReCalComponentSize(&Source);
    ReCalComponentSize(Where);
    int LastIndex = Where->size;


    for (int i = 0; i < Source.size; i ++) {
        Where->buffer[LastIndex + i] = Source.buffer[i];
        Where->size ++;
    }
    return 0;
}

int Render(Component RenderBuffer) {
    printf("%.*s" , RenderBuffer.size , RenderBuffer.buffer);
    return 0;
}


