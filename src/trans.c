#include "trans.h"

int translate() {
    char str[50], *word, buf[4][9999];
    int i, memory, oper, comm, val, flag_eq;
    int mas[N];

    FILE *f1 = fopen("code.sa", "r");
    if(!f1)
        return -1;

    for(int i = 0; i < N; i++)
        mas[i] = 0;

    while(!feof(f1)) {
        fgets(str, sizeof(str), f1);
        word = strtok(str, " \n");
        i = 0;
        flag_eq = 0;

        while(word) {
            strncpy(buf[i], word, 5);
            word = strtok(NULL, " \n");
            switch(i) {
                case 0: {
                    memory = atoi(buf[i]);
                    if((memory < 0) || (memory > 99))
                        return -1;

                    break;
                }
                case 1: {
                    if(strcmp(buf[i], "READ") == 0)
                        comm = 10;

                    else if(strcmp(buf[i], "WRITE") == 0)
                        comm = 11;

                    else if(strcmp(buf[i], "LOAD") == 0)
                        comm = 20;

                    else if(strcmp(buf[i], "STORE") == 0)
                        comm = 21;

                    else if(strcmp(buf[i], "ADD") == 0)
                        comm = 30;

                    else if(strcmp(buf[i], "SUB") == 0)
                        comm = 31;

                    else if(strcmp(buf[i], "DIVIDE") == 0)
                        comm = 32;

                    else if(strcmp(buf[i], "MUL") == 0)
                        comm = 33;

                    else if(strcmp(buf[i], "JUMP") == 0)
                        comm = 40;

                    else if(strcmp(buf[i], "JNEG") == 0)
                        comm = 41;

                    else if(strcmp(buf[i], "JZ") == 0)
                        comm = 42;

                    else if(strcmp(buf[i], "HALT") == 0)
                        comm = 43;

                    else if(strcmp(buf[i], "JNS") == 0)
                        comm = 55;

                    else if(strcmp(buf[i], "=") == 0)
                        flag_eq = 1;

                    else
                        return -1;

                    break;
                }
                case 2: {
                    oper = atoi(buf[i]);
                    if(buf[i][0] != '+') {
                        if((oper < 0) || (oper > 99))
                            return -1;
                    }
                    else {
                        if((oper < 0) || (oper > 9999))
                            return -1;
                    }
                    break;
                }
                case 3: {
                    if(buf[i][0] == ';')
                        break;
                    else
                        return -1;

                    break;
                }                
            }
            if(!flag_eq)
                sc_commandEncode(comm, oper, &val);
            else
                val = oper;
            mas[memory] = val;
            i++;
        }
    }
    fclose(f1);
    FILE* f2 = fopen("Memory.dat", "w");

    fwrite(mas, sizeof(int), N, f2);
    fclose(f2);
    allshow();
    return 0;
}
