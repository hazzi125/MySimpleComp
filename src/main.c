#include <stdio.h>
#include "showComp.h"

int main() {
    mt_clrscr();
    sc_regInit();
   
    inst_counter = 7;
    sc_memorySet(6, 165);
    sc_memorySet(5, 14);
    sc_memorySet(7, 7854);

    sc_regSet(OVERFLOW, 1);
    sc_regSet(NULL_DEL, 1);
    sc_regSet(OUT_OF_MEMORY, 1);
    sc_regSet(IMPULS, 1);
    sc_regSet(WRONG_COMMAND, 1);

    memPrint();
    printboxes();
    showCPU();
    printflags();
    keys();
    printBigChars();
    printf("\n");
    //mt_gotoXY(20, 2);
}
