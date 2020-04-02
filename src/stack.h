#define STACK_SIZE 100
#include <stdio.h>
#include <stdlib.h>
#include <iostream>


typedef struct {
	
	char char_val;
	int int_val;
	float float_val;
	short short_val;
	int value_code;

}Value;

typedef struct {
    int* locals;    // local scoped data, fpstack
    int* code;      // array od byte codes to be executed
    Value* stack;     // virtual stack, rstack
    int pc;         // program counter (aka. IP - instruction pointer)
    int sp;         // stack pointer
    int fp;         // frame pointer (for local scope), fpsp
} VM;
// typedef struct {
//     int* locals;    // local scoped data
//     int* code;      // array od byte codes to be executed
//     int* stack;     // virtual stack
//     int pc;         // program counter (aka. IP - instruction pointer)
//     int sp;         // stack pointer
//     int fp;         // frame pointer (for local scope)
// } VM;

// VM* newVM(int* code,    // pointer to table containing a bytecode to be executed
//     int pc,             // address of instruction to be invoked as first one - entrypoint/main func
//     int datasize) {      // total locals size required to perform a program operations
//     VM* vm = (VM*)malloc(sizeof(VM));
//     vm->code = code;
//     vm->pc = pc;
//     vm->fp = -1;
//     vm->sp = -1;
//     vm->locals = (int*)malloc(sizeof(int) * datasize);
//     vm->stack = (int*)malloc(sizeof(int) * STACK_SIZE);

//     return vm;
// }
VM* newVM(int* code,    // pointer to table containing a bytecode to be executed
    int pc,             // address of instruction to be invoked as first one - entrypoint/main func
    int datasize) {      // total locals size required to perform a program operations
    VM* vm = (VM*)malloc(sizeof(VM));
    vm->code = code;
    vm->pc = pc;
    vm->fp = -1;
    vm->sp = -1;
    vm->locals = (int*)malloc(sizeof(int) * datasize);
    vm->stack = (Value*)malloc(sizeof(Value) * STACK_SIZE);

    return vm;
}

enum { 
  HALT = 0,
    JMP = 36,
    JMPC = 40,
    CALL = 44,
    RET = 48,
    PUSHC = 68,
    PUSHS = 69,
    PUSHI = 70,
    PUSHF = 71,
    PUSHVC = 72,
    PUSHVS = 73,
    PUSHVI = 74,
    PUSHVF = 75,
    POPM = 76,
    POPA = 77,
    POPV = 80,
    PEEKC = 84,
    PEEKS = 85,
    PEEKI = 86,
    PEEKF = 87,
    POKEC = 88,
    POKES = 89,
    POKEI = 90,
    POKEF = 91,
    SWP = 94,
    ADD = 100,
    SUB = 104,
    MUL = 108,
    DIV = 112,
    CMPE = 132,
    CMPLT = 136,
    CMPGT = 140,
    PRINTC = 144,
    PRINTS = 145,
    PRINTI = 146,
    PRINTF = 147   
};

void run(VM* vm);

void delVM(VM* vm){
    free(vm->locals);
    free(vm->stack);
    free(vm);
}