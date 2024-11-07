#ifndef MEMORY_H
#define MEMORY_H
#include<bits/stdc++.h>
using namespace std;

class Memory {
protected:
    vector<string>memory;

public:
    Memory();
    void Set(int addr,string val);
    string Get(int addr);
    void print();
};

#endif

#ifndef REGISTER_H
#define REGISTER_H

class Register {
private:
    vector<string>registers;

public:
    Register();
    void Set_reg(int reg,string val);
    string Get_Specific_Reg(int reg);
    void Print();
};

#endif

#ifndef CU_H
#define CU_H
class CU {
public:
    CU();
    void load(int regIndex, int memAddress, Register& registers,Memory& memory);
    void load_2(int regIndex,string index,Register& registers);
    void store(int regIndex, int memAddress,Register& registers,Memory& memory);
    void move(int regIndex1, int regIndex2,Register& registers);
    bool jump(int idxReg,Register&reg);

};

#endif

#ifndef ALU_H
#define ALU_H

class ALU {
public:
    int hexadecimalToDecimal(const std::string& hexStr);
    string decimalToHexadecimal(int decimal);
    void add(int idx1, int idx2, int idx3, Register& reg);
    bool isValidHexadecimal(const string& hexStr);
    string hexToBinary(const string& hexStr);
    float binaryToFloat(const string& binaryStr);
    string floatToBinary(float value);
    string binaryToHex(const string& binaryStr);
    void addFloatHexRegisters(int f_idx1, int f_idx2, int f_idx3, Register& reg);

};


#endif

#ifndef CPU_H
#define CPU_H
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

#endif

#ifndef MACHINE_H
#define MACHINE_H

class Machine {
private:
    CPU processor;


public:
    Machine();
    void loadProgramFile();
    void screen();
    void outputState();

};

#endif






