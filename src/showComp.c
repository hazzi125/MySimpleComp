#include "showComp.h"

void memPrint() {
    mt_clrscr();
    for(int i = 0; i < N; i++) {
        if(i == inst_counter) {
            curs = inst_counter;
            mt_setfgcolor(GREEN);
            mt_setbgcolor(BLACK);
        }
        else {
            mt_setbgcolor(DEFAULT);
            mt_setfgcolor(DEFAULT);
        }
        if(i % 10 == 0)
            mt_gotoXY((i / 10) + 3, 2);
        printf("+%04X ", RAM[i]);
    }
    mt_setbgcolor(DEFAULT);
    mt_setfgcolor(DEFAULT);
}

void showCPU() {
    mt_gotoXY(2, 28);
    printf("Memory");
    mt_gotoXY(2, 67);
    printf("accumulator");
    mt_gotoXY(3, 69);
    if(accumulator >= 0)
        printf("+");
    printf("%04X", accumulator);
    mt_gotoXY(5, 64);
    printf("instructionCounter");
    mt_gotoXY(6, 69);
    printf("+%04d", inst_counter);
    mt_gotoXY(8, 67);
    printf("Operation");
    mt_gotoXY(9, 68);
    printf("+%02d : +%02d", command, operand);
}

void printflags() {
    int flag;
    mt_gotoXY(11, 68);
    printf("Flags");
    mt_gotoXY(12, 67);
    sc_regGet(OVERFLOW, &flag);
    if(flag)
        printf("O ");
    else
        printf(" ");

    sc_regGet(NULL_DEL, &flag);
    if(flag)
        printf("D ");
    else
        printf(" ");

    sc_regGet(OUT_OF_MEMORY, &flag);
    if(flag)
        printf("M ");
    else
        printf(" ");

    sc_regGet(IMPULS, &flag);
    if(flag)
        printf("T ");
    else
        printf(" ");

    sc_regGet(WRONG_COMMAND, &flag);
    if(flag)
        printf("E ");
    else
        printf(" ");
}

void keys() {
    mt_gotoXY(14, 51);
    printf("Keys:");
    mt_gotoXY(15, 51);
    printf("l  - load      g - translator");
    mt_gotoXY(16, 51);
    printf("s  - save      e - enter");
    mt_gotoXY(17, 51);
    printf("r  - run");
    mt_gotoXY(18, 51);
    printf("t  - step");
    mt_gotoXY(19, 51);
    printf("i  - reset");
    mt_gotoXY(20, 51);
    printf("f5 - accumulator");
    mt_gotoXY(21, 51);
    printf("f6 - instructionCounter");
    mt_gotoXY(22, 51);
    printf("q  - quit");
    mt_gotoXY(25, 0);
}

void printboxes() {
    bc_box(1, 2, 60, 11);
    bc_box(63, 2, 19, 2);
    bc_box(63, 5, 19, 2);
    bc_box(63, 8, 19, 2);
    bc_box(63, 11, 19, 2);
    bc_box(2, 14, 45, 9);
    bc_box(49, 14, 33, 9);
}

void printBigChars() {
    int val, bc_mas[2];
    char symbols[6];
    sc_memoryGet(inst_counter, &val);
    if(val >> 14)
        sprintf(symbols, "-%04X", val);
    else
        sprintf(symbols, "+%04X", val);

    for(int i = 0; i < 5; i++) {
        bc_initBC(bc_mas, symbols[i]);
        bc_printbigchar(bc_mas, 15, 3 + (i * 9), GREEN, BLACK);
    }
    mt_gotoXY(25, 1);
}

void allshow() {
    memPrint();
    printboxes();
    showCPU();
    printflags();
    keys();
    printBigChars();
    printf("Input/Output:");
}

void timer() {
    int val;
    if(!sc_regGet(IMPULS, &val)) {
        inst_counter++;
    }
}

void reset() {
    accumulator = 0;
    inst_counter = 0;
    curs = 0;
    sc_memoryInit();
    sc_regInit();
    sc_regSet(IMPULS, 1);
}
