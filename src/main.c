#include "myterm.h"
int main() {
    mt_clrscr();
    mt_gotoXY(50, 20);
    int x, y;
    mt_getscreensize(&x, &y);
    printf("%d, %d\n", x, y);
}
