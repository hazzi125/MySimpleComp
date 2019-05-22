#ifndef _PRINT_COMP_
#define _PRINT_COMP_

#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include "myBigChars.h"
#include "mySimpleComputer.h"
#include "myReadkey.h"
#include "curs_work.h"

int accumulator, inst_counter, command, operand;

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
