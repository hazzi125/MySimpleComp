#include "trans_basic.h"

int main() {   
    system("tput reset");
    sc_memoryInit();
    sc_regInit();
    sc_regSet(IMPULS, 1);

    struct itimerval nval;
    enum keys K;
    K = NONE;
    int val, temp;

    signal(SIGALRM, timer);

    signal(SIGUSR1, reset);

    nval.it_interval.tv_sec = 5;
    nval.it_interval.tv_usec = 0;

    nval.it_value.tv_sec = 1;
    nval.it_value.tv_usec = 0;

    curs = 0;
    int a, b, c, code;
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
		        scanf("%d", &temp);
		        if(temp > 0x7FFF)
		            sc_regSet(OVERFLOW, 1);

		        else {
		            sc_regSet(OVERFLOW, 0);
		            accumulator = temp;
                        }
		        break;
		    }
		    case F6: {
		        printf("Enter instruction counter value: ");
		        scanf("%d", &temp);
		        if((temp >= 0) && (temp < 100)) {
		            inst_counter = temp;
		            sc_regSet(OUT_OF_MEMORY, 0);
		        }
		        else
		            sc_regSet(OUT_OF_MEMORY, 1);
		        break;
		    }
		    case RUN: {
		        sc_regInit();
		        inst_counter = 0;
		        break;
		    }
		    case RESET: {
		        raise(SIGUSR1);
		        break;
		    }
		    case STEP: {
		        if(cu() == -1)
                            sc_regSet(WRONG_COMMAND, 1);
                        else
                            sc_regSet(WRONG_COMMAND, 0);

		        break;
		    }
		    case ENTER: {
		        scanf("%d", &c);
                        if(c == 0) {
                            printf("Enter data:\n");
                            scanf("%d%d", &a, &b);
                            if(sc_commandEncode(a, b, &code) == 0)
                                sc_memorySet(curs, code);
                            else
                                a = b = 0;
                        }
                        else {
                            scanf("%d", &a);
                            sc_memorySet(curs, a);
                        }
		        break;
		    }
		    case UP: {
		        inst_counter -= 10;
		        if(inst_counter < 0)
		            inst_counter += 10;
		        break;
		    }

                    case TRANS: {
                        if(translate_basic() == -1)
                            sc_regSet(OUT_OF_MEMORY, 1);
                        else
                            sc_regSet(OUT_OF_MEMORY, 0);

                        if(translate() == -1) {
                            int qq;
                            printf("\nhere ");
                            scanf("%d", &qq); 
                            sc_regSet(OUT_OF_MEMORY, 1);
                        }
                        else
                            sc_regSet(OUT_OF_MEMORY, 0);
                        break;
                    }
                 
		    case DOWN: {
		        inst_counter += 10;
		        if(inst_counter >= 100)
		            inst_counter -= 10;
		        break;
		    }
		    case LEFT: {
		        inst_counter--;
		        if(inst_counter < 0)
		            inst_counter = 99;
		        break;
		    }
		    case RIGHT: {
		        inst_counter++;
		        if(inst_counter == 100)
		            inst_counter = 0;
		        break;
		    }
		    default:
		        break;
		}
        }
        else {
            if(cu() == -1) {
                sc_regSet(WRONG_COMMAND, 1);
                sc_regSet(IMPULS, 1);
                inst_counter = 0;
                allshow();
            }
            else
                sc_regSet(WRONG_COMMAND, 0);

            setitimer(ITIMER_REAL, &nval, NULL);
            pause();
            if(inst_counter > 99)
                raise(SIGUSR1);
        }
    }
}
