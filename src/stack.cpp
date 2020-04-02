#include "stack.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>
typedef unsigned char BYTE;
#define PUSH(vm, v) vm->stack[++vm->sp] = v // push value on top of the stack
#define POP(vm)     vm->stack[vm->sp--]     // pop value from top of the stack
#define NCODE(vm)   vm->code[vm->pc++]      // get next bytecode

void run(VM* vm){
    do{
        //printf("pc : %d\n", vm->pc);
        int opcode = NCODE(vm);        // fetch
        //printf("opcode : %d\n", opcode);
         //printf("pc : %d\n", vm->pc);
         
        //std::cout << opcode << std::endl;
        int v, addr, offset, a, b, argc, rval;

        switch (opcode) {   // decode
            case PUSHC:
            {              
                int c = NCODE(vm);   

                vm->stack[++vm->sp].char_val = c;
                vm->stack[vm->sp].value_code = 1;
                
                break;
            } 
                
            case PRINTC:
                {
                Value v = vm->stack[vm->sp--];
                  
                printf("%i\n", v.char_val);
                break;
                }
                
            case PUSHI:
                {
            	int i;
            	unsigned char arr[] = {NCODE(vm), NCODE(vm), NCODE(vm), NCODE(vm)};
            	memcpy(&i, &arr, sizeof(i));
 
                vm->stack[++vm->sp].int_val = i;
                vm->stack[vm->sp].value_code = 2;
                
                break;
                }
            case PRINTI:
                {
                Value v = vm->stack[vm->sp--];  
                printf("%d\n", v.int_val);  

                break;    
                }    
            case PUSHF:
                {
            	float f;
            	unsigned char arr[] = {NCODE(vm), NCODE(vm), NCODE(vm), NCODE(vm)};
            	memcpy(&f, &arr, sizeof(f));

                vm->stack[++vm->sp].float_val = f;
                vm->stack[vm->sp].value_code = 3;
                
                break;
                }
            case PRINTF:
            {
                Value v = vm->stack[vm->sp--];  
                printf("%f\n", v.float_val);  

                break;    
            }   

            case PUSHS:
            {
                short s;
                unsigned char arr [] = {NCODE(vm), NCODE(vm)};
                memcpy(&s, &arr, sizeof(s));

                vm->stack[++vm->sp].short_val = s;
                vm->stack[vm->sp].value_code = 4;

                break;
            }

            case PRINTS:
            {
                Value v = vm->stack[vm->sp--];  
                printf("%i\n", v.short_val);  

                break;    
            }  

            case ADD:{
                Value y = vm->stack[vm->sp--];
                Value x = vm->stack[vm->sp--];

                if (x.value_code==2) {
                    vm->stack[++vm->sp].int_val = x.int_val+y.int_val;
                    vm->stack[vm->sp].value_code = 2;
                }else if (x.value_code==3) {
                    vm->stack[++vm->sp].float_val = x.float_val+y.float_val;
                    vm->stack[vm->sp].value_code = 3;
                }else if (x.value_code==1) {
                    vm->stack[++vm->sp].char_val = (int)x.char_val+(int)y.char_val;
                    vm->stack[vm->sp].value_code = 1;
                }else if (x.value_code==4) {
                    vm->stack[++vm->sp].short_val = x.short_val+y.short_val;
                    vm->stack[vm->sp].value_code = 4;
                }
                break;
            }

            case SUB: {
                Value y = vm->stack[vm->sp--];
                Value x = vm->stack[vm->sp--];

                if (x.value_code==2) {
                    vm->stack[++vm->sp].int_val = x.int_val-y.int_val;
                    vm->stack[vm->sp].value_code = 2;
                }else if (x.value_code==3) {
                    vm->stack[++vm->sp].float_val = x.float_val-y.float_val;
                    vm->stack[vm->sp].value_code = 3;
                }else if (x.value_code==1) {
                    vm->stack[++vm->sp].char_val = (int)x.char_val-(int)y.char_val;
                    vm->stack[vm->sp].value_code = 1;
                }else if (x.value_code==4) {
                    vm->stack[++vm->sp].short_val = x.short_val-y.short_val;
                    vm->stack[vm->sp].value_code = 4;
                }
                break;
            }

            case MUL:{
                Value y = vm->stack[vm->sp--];
                Value x = vm->stack[vm->sp--];

                if (x.value_code==2) {
                    vm->stack[++vm->sp].int_val = x.int_val*y.int_val;
                    vm->stack[vm->sp].value_code = 2;
                }else if (x.value_code==3) {
                    vm->stack[++vm->sp].float_val = x.float_val*y.float_val;
                    vm->stack[vm->sp].value_code = 3;
                }else if (x.value_code==1) {
                    vm->stack[++vm->sp].char_val = (int)x.char_val*(int)y.char_val;
                    vm->stack[vm->sp].value_code = 1;
                }else if (x.value_code==4) {
                    vm->stack[++vm->sp].short_val = x.short_val*y.short_val;
                    vm->stack[vm->sp].value_code = 4;
                }
                break;
            }

            case DIV:{
                Value y = vm->stack[vm->sp--];
                Value x = vm->stack[vm->sp--];

                if (x.value_code==2) {
                    vm->stack[++vm->sp].int_val = x.int_val/y.int_val;
                    vm->stack[vm->sp].value_code = 2;
                }else if (x.value_code==3) {
                    vm->stack[++vm->sp].float_val = x.float_val/y.float_val;
                    vm->stack[vm->sp].value_code = 3;
                }else if (x.value_code==1) {
                    vm->stack[++vm->sp].char_val = (int)x.char_val/(int)y.char_val;
                    vm->stack[vm->sp].value_code = 1;
                }else if (x.value_code==4) {
                    vm->stack[++vm->sp].short_val = x.short_val/y.short_val;
                    vm->stack[vm->sp].value_code = 4;
                }
                break;
            }
            case SWP: {
                Value tmp = vm->stack[vm->sp-1];
                vm->stack[vm->sp-1] = vm->stack[vm->sp];
                vm->stack[vm->sp] = tmp;
                break;
            }

            case CMPE:
            {
                // vm->stack[vm->sp-1] = (vm->stack[vm->sp-1] == vm->stack[vm->sp]);
                // vm->sp--
                //printf("vals: %i\n", vm->sp);
                if (vm->stack[vm->sp-1].value_code==2) {
                    //printf("vals: %i\n", vm->stack[vm->sp-1].int_val == vm->stack[vm->sp].int_val);
                    vm->stack[vm->sp-1].int_val = (vm->stack[vm->sp-1].int_val == vm->stack[vm->sp].int_val);
                    vm->stack[vm->sp].value_code = 2;
                }else if (vm->stack[vm->sp-1].value_code==3) {
                    vm->stack[vm->sp-1].int_val = (vm->stack[vm->sp-1].float_val == vm->stack[vm->sp].float_val);
                    vm->stack[vm->sp].value_code = 2;
                }else if (vm->stack[vm->sp-1].value_code==1) {
                    vm->stack[vm->sp-1].int_val = (vm->stack[vm->sp-1].char_val == vm->stack[vm->sp].char_val);
                    vm->stack[vm->sp].value_code = 2;
                }else if (vm->stack[vm->sp-1].value_code==4) {
                    vm->stack[vm->sp-1].int_val = (vm->stack[vm->sp-1].short_val == vm->stack[vm->sp].short_val);
                    vm->stack[vm->sp].value_code = 2;
                }
                vm->sp--;
                break;
            }

            case CMPLT:
            {
                // vm->stack[vm->sp-1] = (vm->stack[vm->sp-1] == vm->stack[vm->sp]);
                // vm->sp--

                if (vm->stack[vm->sp-1].value_code==2) {
                    vm->stack[vm->sp-1].int_val = (vm->stack[vm->sp-1].int_val < vm->stack[vm->sp].int_val);
                    vm->stack[vm->sp].value_code = 2;
                }else if (vm->stack[vm->sp-1].value_code==3) {
                    vm->stack[vm->sp-1].int_val = (vm->stack[vm->sp-1].float_val < vm->stack[vm->sp].float_val);
                    vm->stack[vm->sp].value_code = 2;
                }else if (vm->stack[vm->sp-1].value_code==1) {
                    vm->stack[vm->sp-1].int_val = (vm->stack[vm->sp-1].char_val < vm->stack[vm->sp].char_val);
                    vm->stack[vm->sp].value_code = 2;
                }else if (vm->stack[vm->sp-1].value_code==4) {
                    vm->stack[vm->sp-1].int_val = (vm->stack[vm->sp-1].short_val < vm->stack[vm->sp].short_val);
                    vm->stack[vm->sp].value_code = 2;
                }
                vm->sp--;
                break;
            }

            case CMPGT:
            {
                // vm->stack[vm->sp-1] = (vm->stack[vm->sp-1] == vm->stack[vm->sp]);
                // vm->sp--

                if (vm->stack[vm->sp-1].value_code==2) {
                    vm->stack[vm->sp-1].int_val = (vm->stack[vm->sp-1].int_val > vm->stack[vm->sp].int_val);
                    vm->stack[vm->sp].value_code = 2;
                }else if (vm->stack[vm->sp-1].value_code==3) {
                    vm->stack[vm->sp-1].int_val = (vm->stack[vm->sp-1].float_val > vm->stack[vm->sp].float_val);
                    vm->stack[vm->sp].value_code = 2;
                }else if (vm->stack[vm->sp-1].value_code==1) {
                    vm->stack[vm->sp-1].int_val = (vm->stack[vm->sp-1].char_val > vm->stack[vm->sp].char_val);
                    vm->stack[vm->sp].value_code = 2;
                }else if (vm->stack[vm->sp-1].value_code==4) {
                    vm->stack[vm->sp-1].int_val = (vm->stack[vm->sp-1].short_val > vm->stack[vm->sp].short_val);
                    vm->stack[vm->sp].value_code = 2;
                }
                vm->sp--;
                break;
            }

            case JMP: {
                vm->pc = vm->stack[vm->sp].int_val;
                vm->sp = vm->sp - 1;
                break;
            }
            case JMPC:{
                if(vm->stack[vm->sp-1].int_val == 1) {      // ... pop value from top of the stack, and if it's true ...
                    vm->pc = vm->stack[vm->sp].int_val; // ... jump with program counter to provided address
                }
                vm->sp = vm->sp - 2;
                break;
            }

            case CALL: {
                vm->locals[++vm->fp] = vm->sp - vm->stack[vm->sp].int_val - 1;
                vm->sp--;
                vm->pc = vm->stack[vm->sp--].int_val;
                break;
            }

            case RET: {
                vm->sp = vm->locals[vm->fp--];
                vm->pc = vm->stack[vm->sp--].int_val;
                break;
            }

            case POPA: {
                for(int i = 0; i < vm->stack[vm->sp].int_val; i++) {
                    vm->stack[vm->locals[vm->fp] + i + 1] = vm->stack[vm->sp - vm->stack[vm->sp].int_val + i];
                }
                vm->sp = vm->locals[vm->fp] + vm->stack[vm->sp].int_val;
                break;
            }

            case POPV: {
                vm->stack[vm->locals[vm->fp]+vm->stack[vm->sp].int_val+1] = vm->stack[vm->sp-1];
                vm->sp -= 2;
                break;
            }

            case POPM: {
                vm->sp -= vm->stack[vm->sp].int_val + 1;
                break;
            }

            case PUSHVC: {
                vm->stack[vm->sp].char_val = vm->stack[vm->locals[vm->fp]+vm->stack[vm->sp].int_val+1].char_val;
                vm->stack[vm->sp].value_code = 1;
                break;
            }

            case PUSHVI: {
                vm->stack[vm->sp].int_val = vm->stack[vm->locals[vm->fp]+vm->stack[vm->sp].int_val+1].int_val;
                vm->stack[vm->sp].value_code = 2;
                break;
            }

            case PUSHVF: {
                vm->stack[vm->sp].float_val = vm->stack[vm->locals[vm->fp]+vm->stack[vm->sp].int_val+1].float_val;
                vm->stack[vm->sp].value_code = 3;
                break;
            }

            case PUSHVS: {
                vm->stack[vm->sp].short_val = vm->stack[vm->locals[vm->fp]+vm->stack[vm->sp].int_val+1].short_val;
                vm->stack[vm->sp].value_code = 4;
                break;
            }

            case PEEKC: {
                vm->stack[vm->locals[vm->fp] + vm->stack[vm->sp-1].int_val+1].char_val = vm->stack[vm->locals[vm->fp]+vm->stack[vm->sp].int_val+1].char_val;
                vm->stack[vm->locals[vm->fp] + vm->stack[vm->sp-1].int_val+1].value_code = 1;
                break;
            }

            case PEEKI: {
                vm->stack[vm->locals[vm->fp] + vm->stack[vm->sp-1].int_val+1].int_val = vm->stack[vm->locals[vm->fp]+vm->stack[vm->sp].int_val+1].int_val;
                vm->stack[vm->locals[vm->fp] + vm->stack[vm->sp-1].int_val+1].value_code = 2;
                break;
            }

            case PEEKF: {
                vm->stack[vm->locals[vm->fp] + vm->stack[vm->sp-1].int_val+1].float_val = vm->stack[vm->locals[vm->fp]+vm->stack[vm->sp].int_val+1].float_val;
                vm->stack[vm->locals[vm->fp] + vm->stack[vm->sp-1].int_val+1].value_code = 3;
                break;
            }

            case PEEKS: {
                vm->stack[vm->locals[vm->fp] + vm->stack[vm->sp-1].int_val+1].short_val = vm->stack[vm->locals[vm->fp]+vm->stack[vm->sp].int_val+1].short_val;
                vm->stack[vm->locals[vm->fp] + vm->stack[vm->sp-1].int_val+1].value_code = 4;
                break;
            }

            case POKEC: {
                vm->stack[vm->locals[vm->fp] + vm->stack[vm->sp].int_val+1].char_val = vm->stack[vm->locals[vm->fp] + vm->stack[vm->sp-1].int_val+1].char_val;
                vm->stack[vm->locals[vm->fp] + vm->stack[vm->sp].int_val+1].value_code = 1;
                break;
            }

            case POKEI: {
                vm->stack[vm->locals[vm->fp] + vm->stack[vm->sp].int_val+1].int_val = vm->stack[vm->locals[vm->fp] + vm->stack[vm->sp-1].int_val+1].int_val;
                vm->stack[vm->locals[vm->fp] + vm->stack[vm->sp].int_val+1].value_code = 2;
                break;
            }

            case POKEF: {
                vm->stack[vm->locals[vm->fp] + vm->stack[vm->sp].int_val+1].float_val = vm->stack[vm->locals[vm->fp] + vm->stack[vm->sp-1].int_val+1].float_val;
                vm->stack[vm->locals[vm->fp] + vm->stack[vm->sp].int_val+1].value_code = 3;
                break;
            }

            case POKES: {
                vm->stack[vm->locals[vm->fp] + vm->stack[vm->sp].int_val+1].short_val = vm->stack[vm->locals[vm->fp] + vm->stack[vm->sp-1].int_val+1].short_val;
                vm->stack[vm->locals[vm->fp] + vm->stack[vm->sp].int_val+1].value_code = 4;
                break;
            }
          
            case HALT: 
                printf("\nCompile values:\n");
                printf("PC: %d\n", vm -> pc - 1);
                printf("sp: %d\n", vm -> sp);
                printf("rstack: empty\n");
                printf("fpsp: %d\n", vm -> fp);
                printf("fpstack: empty");

                return;
            
            default:
                break;
        }

    }while(1);
}

int main(int argc, char *argv[]) {
    std::ifstream file(argv[1], std::ios::binary);

    // Stop eating new lines in binary mode!!!
    file.unsetf(std::ios::skipws);

    // get its size:
    std::streampos fileSize;

    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // reserve capacity
    std::vector<BYTE> vec;
    vec.reserve(fileSize);

    // read the data:
    vec.insert(vec.begin(),
               std::istream_iterator<BYTE>(file),
               std::istream_iterator<BYTE>());

    int program[vec.size()];
    int count = 0;
    // for(auto i: vec) {
    //     int value = i;
    //     program[count] = value;
    //     count++;
    // }    
    for(int i = 0; i < vec.size(); i++) {
        program[i] = (int) vec[i];
    }

    VM* vm = newVM(program,   // program to execute
                    0,    // start address of main function
                    0);    // locals to be reserved, fib doesn't require them
    
    run(vm);
}