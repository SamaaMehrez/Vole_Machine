#ifndef CPU_H
#define CPU_H
#include <vector>
#include "Register.h"
#include "ALU.h"
#include "CU.h"
#include "Memory.h"
class CPU {
private:
    int programCounter;
    string instructionRegister;
    Register reg;
    ALU alu;
    Memory memory;
    CU cu ;
int flag=0;
    vector<string>vec;
public:
    CPU();
    Register&regg();
    Memory &mem();
    void fetch();
    void execute();
    void vec_screen();
};

#endif // CPU_H

