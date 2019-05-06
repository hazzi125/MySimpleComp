#include <stdio.h>
#include <stdlib.h>
#include "showComp.h"
#include "myReadkey.h"
#include "myBigChars.h"
#include "myterm.h"
#include "mySimpleComputer.h"

int main() {
    //mt_clrscr();
    system("tput reset");
    sc_memoryInit();
    sc_regInit();
   
    sc_memorySet(6, 165);
    sc_memorySet(5, 14);
    sc_memorySet(7, 7854);

    enum keys K;
    K = NONE;
    curs = 0;

    memPrint();
    printboxes();
    showCPU();
    printflags();
    keys();
    printBigChars();
    
    printf("\n");

    int val, ac, inst;
    while(K != QUIT) {
        mt_gotoXY(25, 1);
        rk_readkey(&K);
        switch(K) {
            case SAVE: {
                sc_memorySave("Memory.dat");
                printf("\n");
                break;
            }   
            case LOAD: {
                sc_memoryLoad("Memory.dat");
                memPrint();
                printboxes();
                showCPU();
                printflags();
                keys();
                printBigChars();
                printf("\n");
                break;
            }
            case F5: {
                printf("Enter accumulator value: ");
                scanf("%d", &ac);
                accumulator = ac;
                memPrint();
                printboxes();
                showCPU();
                printflags();
                keys();
                printBigChars();
                printf("\n");
                break;
            }
            case F6: {
                printf("Enter instruction counter value: ");
                scanf("%d", &inst);
                inst_counter = inst;
                curs = inst;
                memPrint();
                printboxes();
                showCPU();
                printflags();
                keys();
                printBigChars();
                printf("\n");
                break;
            }
            case RUN: {
                printf("Enter value: ");
                scanf("%d", &val);
                sc_memorySet(inst_counter, val);
                memPrint();
                printboxes();
                showCPU();
                printflags();
                keys();
                printBigChars();
                printf("\n");
                break;
            }
            case RESET: {
                accumulator = 0;
                inst_counter = 0;
                curs = 0;
                sc_memoryInit();
                sc_regInit();
                memPrint();
                printboxes();
                showCPU();
                printflags();
                keys();
                printBigChars();
                printf("\n");
                break;
            }
            case UP: {
                curs -= 10;
                if(curs <= 0)
                    curs += 100;
                memPrint();
                printboxes();
                showCPU();
                printflags();
                keys();
                printBigChars();
                printf("\n");
                break;
            }
            case DOWN: {
                curs += 10;
                if(curs >= 100)
                    curs -= 100;
                memPrint();
                printboxes();
                showCPU();
                printflags();
                keys();
                printBigChars();
                printf("\n");
                break;
            }
            case LEFT: {
                curs -= 1;
                if(curs <= 0)
                    curs = 99;
                memPrint();
                printboxes();
                showCPU();
                printflags();
                keys();
                printBigChars();
                printf("\n");
                break;
            }
            case RIGHT: {
                curs ++;
                if(curs == 100)
                    curs = 0;
                memPrint();
                printboxes();
                showCPU();
                printflags();
                keys();
                printBigChars();
                printf("\n");
                break;
            }
            default:
                break;
        }
    }
}











