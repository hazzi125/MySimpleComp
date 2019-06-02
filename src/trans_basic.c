#include "trans_basic.h"

FILE *f2;
int counter, after_end;
char str[50];

int check_char(char c) {
    int flag = -1;
    for(int i = 65; i <= 90; i++) {
        if((int)c == i)
            flag = 0;
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

        else if(strcmp(word, "LET") == 0)
            num_commands += 3;

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
    int number, temp, check_num = 10;
    counter = -1, after_end = 1;
    //int after_end = 1, temp_if, num_wars = 0, var1_if, var2_if;
    FILE *f1 = fopen("basic.vbs", "r");
    f2 = fopen("code.sa", "w");
    if(!f1)
        return -1;

    count_weights();

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
            if(INPUT() == -1)
                return -1;
        }

        else if(strcmp(word, "OUTPUT") == 0) {
            if(OUTPUT() == -1)
                return -1;
        }

        else if(strcmp(word, "LET") == 0) {
            if(LET() == -1)
                return -1;
        }

        else if(strcmp(word, "END") == 0) {
            fprintf(f2, "%s", "HALT 00\n");
            fclose(f1);
            fclose(f2);
            return 0;
        }

        else if(strcmp(word, "GOTO") == 0) {
            if(GOTO() == -1)
                return -1;
        }

        else if(strcmp(word, "IF") == 0) {
            if(IF() == -1)
                return -1;
        }

    }
    fclose(f1);
    fclose(f2);
    return 0;
}

int IF() {
    char *word = strtok(NULL, " \n");
    int var, temp, res;
    if(check_char(word[0]) == 0)
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
    //temp_if = ptr->weight;

    //if(strcmp(word, "<") == 0) {
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
            if(GOTO() == -1)
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

        //}
    return 0;
}

int INPUT() {
    char *word = strtok(NULL, " \n");
    fprintf(f2, "%s ", "READ");
    if(check_char(word[0]) == -1)
        return -1;

    int var = (int)word[0] - 65;
    fprintf(f2, "%d\n", (N-1) - var);
    return 0;
}

int OUTPUT() {
    char *word = strtok(NULL, " \n");
    fprintf(f2, "%s ", "WRITE");
    if(check_char(word[0]) == -1)
        return -1;

    int var = (int)word[0] - 65;
    fprintf(f2, "%d\n", (N-1) - var);
    return 0;
}

int LET() {
    int temp;
    char *word = strtok(NULL, " \n");

    if(check_char(word[0]) == -1)
        return -1;

    int res = (int)word[0] - 65;
    word = strtok(NULL, " \n");
    if(strcmp(word, "=") != 0)
        return -1;

    word = strtok(NULL, " \n");
    int var = (int)word[0] - 65;
    fprintf(f2, "%s %d\n", "LOAD", (N-1) - var);

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

     counter++;
     if(sc_memoryGet(counter, &temp) != 0)
         return -1;
     if(counter < 10)
         fprintf(f2, "0%d ", counter);
     else
         fprintf(f2, "%d ", counter);

     fprintf(f2, "%s ", "STORE");
     fprintf(f2, "%d\n", (N-1) - res);
     return 0;
}

int GOTO() {
    char *word = strtok(NULL, " \n");
    int var = atoi(word);
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





