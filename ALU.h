#ifndef ALU_H
#define ALU_H

#include "Register.h"
#include<bits/stdc++.h>
using namespace std;
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
