#include <stdlib.h>
#include "showComp.h"

int main() {   
    system("tput reset");
    sc_memoryInit();
    sc_regInit();
    sc_memorySet(6, 165);
    sc_memorySet(5, 14);
    sc_memorySet(7, 7854);
    struct itimerval nval;
    enum keys K;
    K = NONE;
    int val, ac, inst;

    sc_regSet(IMPULS, 1);

    signal(SIGALRM, timer);
    signal(SIGUSR1, reset);

    nval.it_interval.tv_sec = 1;
    nval.it_interval.tv_usec = 0;
    nval.it_value.tv_sec = 1;
    nval.it_value.tv_usec = 0;

    curs = 0;
    while(K != QUIT) {
        allshow();
        printf("\n");
        if(sc_regGet(IMPULS, &val)) {
                mt_gotoXY(25, 1);
                rk_readkey(&K);
		switch(K) {
		    case SAVE: {
		        sc_memorySave("Memory.dat");
		        break;
		    }   
		    case LOAD: {
		        sc_memoryLoad("Memory.dat");
		        break;
		    }
		    case F5: {
		        printf("Enter accumulator value: ");
		        scanf("%d", &ac);
		        if(ac > 0x7FFF)
		            sc_regSet(OVERFLOW, 1);

		        else {
		            sc_regSet(OVERFLOW, 0);
		            accumulator = ac;
                        }
		        break;
		    }
		    case F6: {
		        printf("Enter instruction counter value: ");
		        scanf("%d", &inst);
		        if((inst >= 0) && (inst < 100)) {
		            inst_counter = inst;
		            curs = inst;
		            sc_regSet(OUT_OF_MEMORY, 0);
		        }
		        else
		            sc_regSet(OUT_OF_MEMORY, 1);
		        break;
		    }
		    case RUN: {
		        sc_regInit();
		        curs = 95;
		        break;
		    }
		    case RESET: {
		        raise(SIGUSR1);
		        break;
		    }
		    case UP: {
		        curs -= 10;
		        if(curs < 0)
		            curs += 100;
		        break;
		    }
		    case DOWN: {
		        curs += 10;
		        if(curs >= 100)
		            curs -= 100;
		        break;
		    }
		    case LEFT: {
		        curs--;
		        if(curs < 0)
		            curs = 99;
		        break;
		    }
		    case RIGHT: {
		        curs++;
		        if(curs == 100)
		            curs = 0;
		        break;
		    }
		    default:
		        break;
		}
        }
        else {
            setitimer(ITIMER_REAL, &nval, NULL);
            pause();
            if(curs > 99)
                raise(SIGUSR1);
        }
    }
}
