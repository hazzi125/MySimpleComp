#include "myBigChars.h"

int main() {
    mt_clrscr();
    int m[2];
    m[0] = 541073948;
    m[1] = 472006712;
    bc_printbigchar(m, 4, 4, 2, 3);
    printf("\n");
    bc_setbigcharpos(m, 1, 5, 0);
    bc_printbigchar(m, 4, 4, 2, 3);
    printf("\n");
}
