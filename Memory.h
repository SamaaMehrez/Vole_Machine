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

#endif // MEMORY_H
