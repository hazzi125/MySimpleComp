#include "myterm.h"
#include <termios.h>
#include <sys/ioctl.h>

int mt_clrscr() {
    printf("\E[H\E[J");
    return 0;
}

int mt_gotoXY(int r, int c) {
    int x, y;
    mt_getscreensize(&x, &y);
    if((r >= 0) && (c >= 0) && (r <= x) && (r <= y)) {
        printf("\E[%d;%dH", r, c);
        return 0;
    }
    else {
        return -1;
    }
    
}

int mt_getscreensize(int *rows, int *cols) {
    struct winsize ws;
    if(!ioctl(1, TIOCGWINSZ, &ws)) {
        *rows = ws.ws_row;
        *cols = ws.ws_col;
        return 0;
    }
    else {
        return -1;
    }
}
