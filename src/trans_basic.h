#ifndef _TRANS_BASIC_
#define _TRANS_BASIC_

#include "trans.h"

struct list {
    int num, weight;
    struct list *next;
};

struct list *head, *tail;

int check_char(char c);
int count_weights();
int translate_basic();

int INPUT();
int OUTPUT();
int LET();
int GOTO();
int IF();

#endif
