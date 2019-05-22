#ifndef _MY_SIMPLE_COMPUTER_
#define _MY_SIMPLE_COMPUTER_

#define N 100
#define commands 12

#define OVERFLOW 1
#define NULL_DEL 2
#define OUT_OF_MEMORY 3
#define IMPULS 4
#define WRONG_COMMAND 5

#include <stdio.h>

int RAM[N];
int reg_flags;

int sc_memoryInit();
int sc_memorySet(int address, int value);
int sc_memoryGet(int address, int * value);
int sc_memorySave(char * filename);
int sc_memoryLoad(char * filename);
int sc_regInit(void);
int sc_regSet(int registr, int value);
int sc_regGet(int registr, int * value);
int sc_commandEncode(int command, int operand, int * value);
int sc_commandDecode(int value, int * command, int * operand);

#endif
