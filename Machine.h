#ifndef MACHINE_H
#define MACHINE_H
#include "CPU.h"
#include<bits/stdc++.h>
using namespace std;

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
