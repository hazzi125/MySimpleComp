#include "myBigChars.h"

int bc_printA(char *str) {
    printf("\E(0%s\E(B", str);
    return 0;
}

int bc_box(int x1, int y1, int x2, int y2) {
    int r, c;
    mt_getscreensize(&r, &c);
    if((x1 < 0) || (y1 < 0) || (x2 > r) || (y2 > c)) {
        return -1;
    }
    mt_gotoXY(x1, y1);
    bc_printA("l");
    for(int i = x1+1; i < x1+x2; i++) {
        bc_printA("q");
    }

    bc_printA("k");
    mt_gotoXY(x1, y1);
    for(int i = x1+1; i < x1+x2; i++) {
        mt_gotoXY(i, y1 + y2);
	bc_printA("x");
	mt_gotoXY(i, y1);
	bc_printA("x");
    }

    mt_gotoXY(x1+x2, y1);
    bc_printA("m");

    for(int i = x1+1; i < x1+x2; i++) {
        bc_printA("q");
    }
    bc_printA("j");
    return 0;
}

int bc_printbigchar(int *big, int x, int y, enum colors color1, enum colors color2) {
    int r, c;
    mt_getscreensize(&r, &c);
    if((x < 0) || (y < 0) || (x > r) || (y > c)) {
        return -1;
    }
    mt_setfgcolor(color1);
    mt_setbgcolor(color2);
    int bit;
    mt_gotoXY(x, y);
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            bit = (big[i>>2] >> ((i % 4) * 8 + j)) & 0x1;
            if(bit)
                bc_printA("a");
            else
                bc_printA(" ");
        }
        mt_gotoXY(x + (i+1), y);
    }
    mt_setfgcolor(DEFAULT);
    mt_setbgcolor(DEFAULT);
    return 0;
}

int bc_setbigcharpos(int *big, int x, int y, int value) {
    if((x < 0) || (y < 0) || (x > 7) || (y > 7))
        return -1;
    if(value)
        big[x/4] = big[x/4] | (1 << ((x % 4) * 8 + y));
    else
        big[x/4] = big[x/4] & (~(1 << ((x % 4) * 8 + y)));
    return 0;
}

int bc_getbigcharpos(int *big, int x, int y, int *value) {
    if((x < 0) || (y < 0) || (x > 7) || (y > 7))
        return -1;
    *value = (big[x/4] >> ((x % 4) * 8 + y)) & 0x1;
    return 0;
}

int bc_bigcharwrite(int fd, int *big, int count) {
    write(fd, big, count * sizeof(int) * 2);
    close(fd);
    return 0;
}

int bc_bigcharread(int fd, int *big, int need_count, int *count) {
    read(fd, big, need_count * sizeof(int) * 2);
    close(fd);
    return 0;
}


















