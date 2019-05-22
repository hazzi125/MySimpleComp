#ifndef _MY_TERM
#define _MY_TERM

#include <stdio.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>

enum colors {
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHTGRAY,
    DARKGRAY,
    LIGHTBLUE,
    LIGHTGREEN,
    LIGHTCYAN,
    LIGHTRED,
    LIGHTMAGENTA,
    YELLOW,
    WHITE,
    DEFAULT = 9
};

int mt_clrscr();
int mt_gotoXY(int, int);
int mt_getscreensize(int *rows, int *cols);
int mt_setfgcolor(enum colors);
int mt_setbgcolor(enum colors);

#endif
