#include "curs_work.h"

int alu(int com, int op) {
    int value;
    sc_memoryGet(op, &value);
    switch(com) {
        case 30: {
            if((value + accumulator) > 0x7FFF) {
                sc_regSet(OVERFLOW, 1);
                sc_regSet(IMPULS, 1);
                curs = inst_counter = 0;
            }
            else {
                sc_regSet(OVERFLOW, 0);
                accumulator += value;
            }
            break;
        }

        case 31: {    
            accumulator -= value;
            break;
        }

        case 32: {
            if(value == 0) {
                sc_regSet(NULL_DEL, 1);
                sc_regSet(IMPULS, 1);
                curs = inst_counter = 0;
                break;
            }
            else {
                sc_regSet(NULL_DEL, 0);
                accumulator /= value;
            }
            break;
        }
    
        case 33: {
            if((value * accumulator) > 0x7FFF) {
                sc_regSet(OVERFLOW, 1);
                sc_regSet(IMPULS, 1);
                curs = inst_counter = 0;
                break;
            }
            else {
                sc_regSet(OVERFLOW, 0);
                accumulator *= value;
            }
            break;
        }
    }
    return 0;
}

int cu() {
    int value;
    sc_memoryGet(inst_counter, &value);
    command = operand = 0;
    int result = sc_commandDecode(value, &command, &operand);
    if(result == -1) {
        return -1;
    }

    else {
        sc_regSet(WRONG_COMMAND, 0);
        if((command == 30) || (command == 31) || (command == 32) || (command == 33))
            alu(command, operand);

        else {
            int a;
            switch(command) {
                case 10: {
                    printf("\nEnter value: ");
                    scanf("%d", &a);
                    if(a > 0x7FFF) {
                        sc_regSet(OVERFLOW, 1);
                        sc_regSet(IMPULS, 1);
                        inst_counter = 0;
                    }
                    else {
                        sc_regSet(OVERFLOW, 0);
                        sc_memorySet(operand, a);
                    }
                    break;
                }

                case 11: {
                    sc_memoryGet(operand, &a);
                    char get_ch[10];
                    printf("\nValue in cell: %d\nPress any key to continue...\n", a);

		    struct termios def_opt;
		    if(tcgetattr(0, &def_opt) == -1)
			return -1;

		    if(rk_mytermregime(0, 1, 1, 0, 0) == -1)
			return -1;

                    read(0, get_ch, 9);
                    if(tcsetattr(0, TCSANOW, &def_opt) != 0)
                        return -1;
                    break;
                }

                case 20: {
                    sc_memoryGet(operand, &a);
                    accumulator = a;
                    break;
                }

                case 21: {
                    sc_memorySet(operand, accumulator);
                    break;
                }

                case 40: {
                    curs = inst_counter = operand;
                    inst_counter--;
                    break;
                }

                case 41: {
                    if(accumulator < 0) {
                        curs = inst_counter = operand;
                        inst_counter--;
                    }
                    break;
                }

                case 42: {
                    if(accumulator == 0) {
                        curs = inst_counter = operand;
                        inst_counter--;
                    }
                    break;
                }

                case 43: {
                    raise(SIGUSR1);
                    break;
                }
            }
        }
        return 0;
    }
}
