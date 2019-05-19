#include <stdio.h>
#include "mySimpleComputer.h"

int mas_commands[] = {0x10, 0x11, 0x20, 0x21, 0x30, 0x31, 0x32, 0x33, 0x40, 0x41, 0x42, 0x43};

int sc_memoryInit() {
    for(int i = 0; i < N; i++)
        RAM[i] = 0;

    return 0;
}

int sc_memorySet (int address, int value) {
    if((address >= 0) && (address < N)) {
        RAM[address] = value;
        return 0;
    }
    else {
        printf("OUT_OF_ADDRES\n");
        return -1;
    }
}

int sc_memoryGet (int address, int * value) {
    if((address >= 0) && (address < N)) {
        *value = RAM[address];
        return 0;
    }
    else
        return -1;
}

int sc_memorySave (char * filename) {
    FILE* f = fopen(filename, "wb+");
    if(f == NULL)
        return -1;

    fwrite(RAM, sizeof(int), N, f);
    fclose(f);
    return 0;
}

int sc_memoryLoad (char * filename) {
    FILE* f = fopen(filename, "rb+");
    if(f == NULL)
        return -1;    

    fread(RAM, sizeof(int), N, f);
    fclose(f);
    return 0;
}

int sc_regInit(void) {
    reg_flags = 0;
    return 0;
} 

int sc_regSet (int registr, int value) {
    if ( (registr >= 1) && (registr <= 5)) {
        if (value == 1) {
           reg_flags = reg_flags | (1 << (registr - 1));
           return 0;
        }

        else if (value == 0) {
           reg_flags = reg_flags & (~(1 << (registr - 1)));
           return 0;
        }
        else
            return -1;
    }
    else
        return -1;
}

int sc_regGet (int registr, int * value) {
    if ( (registr >= 1) && (registr <= 5)) { 
        *value = (reg_flags >> (registr - 1)) & 0x1;
        return *value;
    }
    else
        return -1;
}

int sc_commandEncode(int command, int operand, int * value) {
    int buf = 0; 

    for(int i = 0; i < commands; i++)
        if(command == mas_commands[i])
            buf = 1;

    if(buf == 0) {
        sc_regSet(WRONG_COMMAND, 1);
        return -1;
    }

    if((buf == 1) && ((operand >= 0) && (operand < N))) {
        *value = (command << 7) | operand;
        sc_regSet(WRONG_COMMAND, 0);
        sc_regSet(OUT_OF_MEMORY, 0);
        return 0;
    }
    else {
        sc_regSet(OUT_OF_MEMORY, 1);
        return -1;
    }
}

int sc_commandDecode(int value, int * command, int * operand) {
    int buf = 0;
    int attribute;
    int buf_command;
    int buf_operand;

    attribute = (value >> 14) & 1;
    if(attribute == 0) {
        buf_command = (value >> 7) & 0x7F;
        buf_operand = value & 0x7F;

        for(int i = 0; i < commands; i++) {
            if(buf_command == mas_commands[i]) {
                buf = 1;
            }
        }

        if((buf == 1) && ((*operand >= 0) && (*operand < N))) {
            *command = buf_command;
            *operand = buf_operand;
        }
        else if(buf == 0)
            return -1;

        return 0;
    }
    else
        return -1;
}
