#ifndef _PRINT_COMP_
#define _PRINT_COMP_

#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include "myBigChars.h"
#include "mySimpleComputer.h"
#include "myReadkey.h"

int accumulator;
int inst_counter;

void memPrint();
void showCPU();
void printflags();
void keys();
void printboxes();
void printBigChars();
void allshow();
void timer();
void reset();

#endif
