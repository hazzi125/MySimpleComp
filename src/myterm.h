#ifndef _MY_TERM
#define _MY_TERM

#include <stdio.h>

enum colors {
    BLACK, 
    RED,  
    GREEN,
    YELLOW,
    BLUE,
    PURPLE,
    LIGHT_BLUE,
    WHITE, 
    DEFAULT = 9
};

int mt_clrscr();
int mt_gotoXY(int, int);
int mt_getscreensize(int *rows, int *cols);
int mt_setfgcolor(enum colors);
int mt_setbgcolor(enum colors);

#endif
