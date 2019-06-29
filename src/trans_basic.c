#include "trans_basic.h"

FILE *f2;
int counter, after_end;
//int rus_after_end;
char str[50], temp_string[50];

int check_letter(char c) {
    int flag = -1;
    for(int i = 65; i <= 90; i++) {
        if((int)c == i) {
            flag = 0;
            break;
        }
    }
    return flag;
}

int count_weights() {
    int num_commands = 0, k = 0;
    struct list *p;
    head = tail = NULL;
    FILE *f1 = fopen("basic.vbs", "r");
    char str[50], *word;
    while(!feof(f1)) {
        fgets(str, sizeof(str), f1);
        word = strtok(str, " \n");
        p = malloc(sizeof(struct list));
        p->num = k;
        k++;
        word = strtok(NULL, " \n");
        if((strcmp(word, "INPUT") == 0) || (strcmp(word, "OUTPUT") == 0) || (strcmp(word, "GOTO") == 0))
            num_commands++;

        else if(strcmp(word, "END") == 0) {
            num_commands++;
            fclose(f1);
            return 0;
        }        

        else if(strcmp(word, "LET") == 0) {
            word = strtok(NULL, " \n");
            word = strtok(NULL, "\n");
            if(word[strlen(word) - 1] != str[strlen(str) - 1])
                num_commands += 3;
            else
                num_commands++;
        }    

        else if(strcmp(word, "IF") == 0)
            num_commands += 4;

        p->weight = num_commands;
        if(head) {
            tail->next = p;
            tail = p;
        }
        else {
            head = tail = p;
            p->next = NULL;
        }
    }
    fclose(f1);
    return 0;
}

int translate_basic() {
    char *word;
    int number = 0, temp, check_num = 10;
    counter = -1;
    after_end = 1;
    FILE *f1 = fopen("basic.vbs", "r");
    f2 = fopen("code.sa", "w");
    if(!f1)
        return -1;

    count_weights();

    while(!feof(f1)) {
        fgets(str, sizeof(str), f1);
        strcpy(temp_string, str);
        word = strtok(str, " \n");

        number = atoi(word);
        if(number < check_num)
            return -1;
        check_num = number;

//////////////////////////////////////////////////////

        word = strtok(NULL, " \n");

        if(strcmp(word, "INPUT") == 0) {
            counter++;
            if(sc_memoryGet(counter, &temp) != 0)
                return -1;
            if(counter < 10)
                fprintf(f2, "0%d ", counter);
            else
                fprintf(f2, "%d ", counter); 
            if(INPUT() == -1)
                return -1;
        }

        else if(strcmp(word, "OUTPUT") == 0) {
            counter++;
            if(sc_memoryGet(counter, &temp) != 0)
                return -1;
            if(counter < 10)
                fprintf(f2, "0%d ", counter);
            else
                fprintf(f2, "%d ", counter); 
            if(OUTPUT() == -1)
                return -1;
        }

        else if(strcmp(word, "LET") == 0) {
            if(LET(-1) == -1)
                return -1;
        }

        else if(strcmp(word, "END") == 0) {
            counter++;
            if(sc_memoryGet(counter, &temp) != 0)
                return -1;
            if(counter < 10)
                fprintf(f2, "0%d ", counter);
            else
                fprintf(f2, "%d ", counter); 
            fprintf(f2, "%s", "HALT 00\n");
            fclose(f1);
            fclose(f2);
            return 0;
        }

        else if(strcmp(word, "GOTO") == 0) {
            counter++;
            if(sc_memoryGet(counter, &temp) != 0)
                return -1;
            if(counter < 10)
                fprintf(f2, "0%d ", counter);
            else
                fprintf(f2, "%d ", counter); 
            if(GOTO(-1) == -1)
                return -1;
        }

        else if(strcmp(word, "IF") == 0) {
            if(IF(number) == -1)
                return -1;
        }

    }
    fclose(f1);
    fclose(f2);
    return 0;
}

int IF(int number) {
    char *word = strtok(NULL, " \n");
    int var, temp, res;
    if(check_letter(word[0]) == 0)
        var = (int)word[0] - 65;
    else
        var = atoi(word);

    word = strtok(NULL, " \n");

    struct list *ptr = head;
    for(int j = 1; j < var - 1; j++) {
        if(!ptr)
            return -1;
        ptr = ptr->next;
    }

    if(strcmp(word, "<") == 0) {
        word = strtok(NULL, " \n");

        //if(check_char(word[0]) == 0) {
            res = (int)word[0] - 65;
            fprintf(f2, "%s %d\n", "LOAD", (N-1) - var);

	    counter++;
	    if(sc_memoryGet(counter, &temp) != 0)
	        return -1;
	    if(counter < 10)
	        fprintf(f2, "0%d ", counter);
	    else
	        fprintf(f2, "%d ", counter);

            fprintf(f2, "%s %d\n", "SUB", (N-1) - res);

	    counter++;
	    if(sc_memoryGet(counter, &temp) != 0)
	        return -1;
	    if(counter < 10)
	        fprintf(f2, "0%d ", counter);
	    else
	        fprintf(f2, "%d ", counter);

            fprintf(f2, "%s %d\n", "STORE", tail->weight + after_end);
            after_end++;
            
	    if(tail->weight + after_end < 10)
	        fprintf(f2, "0%d ", tail->weight + after_end);
	    else
	        fprintf(f2, "%d ", tail->weight + after_end);

            word = strtok(NULL, " \n");
            if(strcmp(word, "GOTO") == 0) {
                if(GOTO(-1) == -1)
                    return -1;

	        counter++;
	        if(sc_memoryGet(counter, &temp) != 0)
	            return -1;
	        if(counter < 10)
	            fprintf(f2, "0%d ", counter);
	        else
	            fprintf(f2, "%d ", counter);

                fprintf(f2, "%s %d\n", "JNEG", tail->weight + after_end);
                after_end++;
            }

            else { 
                if(strcmp(word, "INPUT") == 0) {
                    if(INPUT() == -1)
                        return -1;
                }
                else if(strcmp(word, "OUTPUT") == 0) {
                    if(OUTPUT() == -1)
                        return -1;
                }
                else if(strcmp(word, "LET") == 0) {
                    if(LET(tail->weight + after_end) == -1)
                        return -1;
                }

	        counter++;
	        if(sc_memoryGet(counter, &temp) != 0)
	            return -1;
	        if(counter < 10)
	            fprintf(f2, "0%d ", counter);
	        else
	            fprintf(f2, "%d ", counter);

                fprintf(f2, "%s %d\n", "JNEG", tail->weight + 2);
                after_end++;

	        if(tail->weight + after_end < 10)
	            fprintf(f2, "0%d ", tail->weight + after_end);
	        else
	            fprintf(f2, "%d ", tail->weight + after_end);

                if(GOTO(number + 10) == -1) {
                    int qq;
                    printf("\nhere ");
                    scanf("%d", &qq);
                    return -1;
                }
            }
    }
    return 0;
}

int INPUT() {
    char *word = strtok(NULL, " \n");
    fprintf(f2, "%s ", "READ");
    if(check_letter(word[0]) == -1)
        return -1;

    int var = (int)word[0] - 65;
    fprintf(f2, "%d\n", (N-1) - var);
    return 0;
}

int OUTPUT() {
    char *word = strtok(NULL, " \n");
    fprintf(f2, "%s ", "WRITE");
    if(check_letter(word[0]) == -1)
        return -1;

    int var = (int)word[0] - 65;
    fprintf(f2, "%d\n", (N-1) - var);
    return 0;
}

int LET(int val) {
    int temp, var;
    char *word = strtok(NULL, " \n");

    if(check_letter(word[0]) == -1)
        return -1;

    int res = (int)word[0] - 65;
    word = strtok(NULL, " \n");
    if(strcmp(word, "=") != 0)
        return -1;

    word = strtok(NULL, " \n");

    if(check_letter(word[0]) == 0) {
        counter++;
        if(sc_memoryGet(counter, &temp) != 0)
            return -1;
        if(counter < 10)
            fprintf(f2, "0%d ", counter);
        else
            fprintf(f2, "%d ", counter);

        var = (int)word[0] - 65;
        fprintf(f2, "%s %d\n", "LOAD", (N-1) - var);
    }

    else {
        var = atoi(word);
        if(after_end + tail->weight < 10)
            fprintf(f2, "0%d = +%04d\n", after_end + tail->weight, var);
        else
            fprintf(f2, "%d = +%04d\n", after_end + tail->weight, var);

        counter++;
        if(sc_memoryGet(counter, &temp) != 0)
            return -1;
        if(counter < 10)
            fprintf(f2, "0%d ", counter);
        else
            fprintf(f2, "%d ", counter);

        fprintf(f2, "%s %d\n", "LOAD", after_end + tail->weight);

        after_end++;
    }

    if(check_letter(temp_string[strlen(temp_string) - 2]) != 0) {
        int j = 0, k = 0;
        while((temp_string[j] != '+') && (temp_string[j] != '-') && (temp_string[j] != '*') && (temp_string[j] != '/')) {
            j++;
        }
        j += 2;
        char buffer_str[5];
        while(temp_string[j] != '\0') {
            buffer_str[k] = temp_string[j];
            k++;
            j++;
        }

        var = atoi(buffer_str);
        if(after_end + tail->weight < 10)
            fprintf(f2, "0%d = +%04d\n", after_end + tail->weight, var);
        else
            fprintf(f2, "%d = +%04d\n", after_end + tail->weight, var);
    }

    if(val == -1) {
        counter++;
        if(sc_memoryGet(counter, &temp) != 0)
             return -1;
         if(counter < 10)
             fprintf(f2, "0%d ", counter);
         else
             fprintf(f2, "%d ", counter);
    }
    else {
        after_end++;
        val++;
        if(sc_memoryGet(val, &temp) != 0)
             return -1;
         if(val < 10)
             fprintf(f2, "0%d ", val);
         else
             fprintf(f2, "%d ", val);
    }

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
    if(check_letter(word[0]) == 0) {
        var = (int)word[0] - 65;
        fprintf(f2, "%d\n", (N-1) - var);
    }

    else {
        if(after_end + tail->weight < 10)
            fprintf(f2, "0%d\n", after_end + tail->weight);
        else
            fprintf(f2, "%d\n", after_end + tail->weight);
        after_end++;
    }

    if(val == -1) {
        counter++;
        if(sc_memoryGet(counter, &temp) != 0)
             return -1;
         if(counter < 10)
             fprintf(f2, "0%d ", counter);
         else
             fprintf(f2, "%d ", counter);
    }
    else {
        val++;
        after_end++;
        if(sc_memoryGet(val, &temp) != 0)
             return -1;
         if(val < 10)
             fprintf(f2, "0%d ", val);
         else
             fprintf(f2, "%d ", val);
    }

    fprintf(f2, "%s ", "STORE");
    fprintf(f2, "%d\n", (N-1) - res);
    return 0;
}

int GOTO(int var) {
    if(var == -1) {
        char *word = strtok(NULL, " \n");
        var = atoi(word);
    }

    if(var % 10 != 0)
        return -1;
    var /= 10;

    struct list *ptr = head;
    for(int j = 1; j < var - 1; j++) {
        if(!ptr)
            return -1;
        ptr = ptr->next;
    }
    if(ptr->num + 2 != var)
        return -1;

    if(ptr->weight < 10)
        fprintf(f2, "%s 0%d\n", "JUMP", ptr->weight);
    else
        fprintf(f2, "%s %d\n", "JUMP", ptr->weight);
    return 0;
}





