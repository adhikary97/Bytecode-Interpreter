#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>

enum Instr {
    HALT = 0,
    JMP = 36,
    JMPC = 40,
    CALL = 44,
    RET = 48,
    PUSHC = 68,
    PUSHS,
    PUSHI,
    PUSHF,
    PUSHVC,
    PUSHVS,
    PUSHVI,
    PUSHVF,
    POPM = 76,
    POPA = 77,
    POPV = 80,
    PEEKC = 84,
    PEEKS,
    PEEKI,
    PEEKF,
    POKEC = 88,
    POKES,
    POKEI,
    POKEF,
    SWP = 94,
    ADD = 100,
    SUB = 104,
    MUL = 108,
    DIV = 112,
    CMPE = 132,
    CMPLT = 136,
    CMPGT = 140,
    PRINTC = 144,
    PRINTS,
    PRINTI,
    PRINTF
};

void output_to_binary_file(std::string str, std::vector<unsigned char> vec) {
    std::ofstream output_file(str, std::ios::out | std::ios::binary);
    std::ostream_iterator<unsigned char> output_iterator(output_file, "");
    std::copy(vec.begin(), vec.end(), output_iterator);
}

int main() {
    //Basics.bin - PUSH, PRINT, HALT
    std::vector<unsigned char> basics_vec = {PUSHC, 12, PRINTC, PUSHI, 16, 0, 0, 0, PRINTI, HALT};
       /* PUSHC, 34,
        PUSHC, 56,
        PRINTC,
        PRINTC,
        PRINTC,

        //Shorts
        PUSHS, 0xD2, 0x04,
        PRINTS,
        PUSHS, 0x1F, 0xEF,
        PRINTS,

        //Ints
        PUSHI, 16, 0, 0, 0,
        PRINTI,
        PUSHI, 0xFF, 0xFF, 0xFF, 0xFF,
        PRINTI,

        //Floats
        PUSHF, 0x00, 0x00, 0x80, 0x41,
        PRINTF,
        PUSHF, 0x66, 0xE6, 0xF6, 0x42,
        PRINTF,

        //Halt
        HALT
        };*/
    output_to_binary_file("Basics.bin", basics_vec);

    return 0;
}