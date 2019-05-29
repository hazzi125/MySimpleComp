#include "trans_basic.h"

int translate_basic() {
    char str[50], *word;
    int number, counter = -1, var, res, temp, check_num, num_commands = 0;
    FILE *f1 = fopen("basic.vbs", "r");
    FILE *f2 = fopen("code.sa", "w");

    if(!f1)
        return -1;


    while(!feof(f1)) {
        fgets(str, sizeof(str), f1);
        word = strtok(str, " \n");

        number = atoi(word);
        if(number < check_num)
            return -1;
        check_num = number;
        
        counter++;
        if(sc_memoryGet(counter, &temp) != 0)
            return -1;
        if(counter < 10)
            fprintf(f2, "0%d ", counter);
        else
            fprintf(f2, "%d ", counter);

//////////////////////////////////////////////////////

        word = strtok(NULL, " \n");
        if(strcmp(word, "INPUT") == 0) {
            fprintf(f2, "%s ", "READ");
            word = strtok(NULL, " \n");
            var = (int)word[0] - 65;
            fprintf(f2, "%d\n", (N-1) - var);
            num_commands++;
        }

        else if(strcmp(word, "LET") == 0) {
            word = strtok(NULL, " \n");
            res = (int)word[0] - 65;
            word = strtok(NULL, " \n");
            if(strcmp(word, "=") != 0)
                return -1;

            word = strtok(NULL, " \n");
            var = (int)word[0] - 65;
            fprintf(f2, "%s %d\n", "LOAD", (N-1) - var);
            num_commands++;

            counter++;
            if(sc_memoryGet(counter, &temp) != 0)
                return -1;
            if(counter < 10)
                fprintf(f2, "0%d ", counter);
            else
                fprintf(f2, "%d ", counter);

            word = strtok(NULL, " \n");
            switch(word[0]) {
                case '-': {
                    fprintf(f2, "%s ", "SUB");
                    break; 
                }
                case '+': {
                    fprintf(f2, "%s ", "ADD");
                    break; 
                }
                case '*': {
                    fprintf(f2, "%s ", "MUL");
                    break; 
                }
                case '/': {
                    fprintf(f2, "%s ", "DIVIDE");
                    break; 
                }
            }
            word = strtok(NULL, " \n");
            var = (int)word[0] - 65;
            fprintf(f2, "%d\n", (N-1) - var);
            num_commands++;

            counter++;
            if(sc_memoryGet(counter, &temp) != 0)
                return -1;
            if(counter < 10)
                fprintf(f2, "0%d ", counter);
            else
                fprintf(f2, "%d ", counter);

            fprintf(f2, "%s ", "STORE");
            fprintf(f2, "%d\n", (N-1) - res);
            num_commands++;
        }

        else if(strcmp(word, "END") == 0) {
            fprintf(f2, "%s", "HALT 00\n");
            fclose(f1);
            fclose(f2);
            return 0;
        }

        else if(strcmp(word, "GOTO") == 0) {
            
        }
    }
    fclose(f1);
    fclose(f2);
    return 0;
}






