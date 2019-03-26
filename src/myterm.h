#ifndef MY_TERM
#define MY_TERM

#include <stdio.h>

int mt_clrscr();
int mt_gotoXY(int, int);
int mt_getscreensize(int *rows, int *cols);
//int mt_setfgcolor(enum colors);
//int mt_setbgcolor(enum colors);

#endif
