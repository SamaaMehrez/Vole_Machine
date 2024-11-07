#ifndef REGISTER_H
#define REGISTER_H
#include<bits/stdc++.h>
using namespace std;
class Register {
private:
    vector<string>registers;

public:
    Register();
    void Set_reg(int reg,string val);
    string Get_Specific_Reg(int reg);
    void Print();
};

#endif // REGISTER_H
