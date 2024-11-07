#ifndef CU_H
#define CU_H

#include "Register.h"
#include "Memory.h"
#include<bits/stdc++.h>
using namespace std;
class CU {
public:
//    CU(Register& reg, Memory& mem);
    CU();
    void load(int regIndex, int memAddress, Register& registers,Memory& memory);
    void load_2(int regIndex,string index,Register& registers);
    void store(int regIndex, int memAddress,Register& registers,Memory& memory);
    void move(int regIndex1, int regIndex2,Register& registers);
    bool jump(int idxReg,Register&reg);

};

#endif // CU_H
