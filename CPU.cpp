#include "CPU.h"
#include<bits/stdc++.h>

using namespace std;

Memory& CPU::mem() {
    return memory;

}
Register& CPU::regg() {
    return reg;
}
CPU::CPU(): programCounter(10), alu() { }
void CPU::fetch() {
    if(programCounter%2==0) {
        instructionRegister = memory.Get(programCounter) + memory.Get(programCounter + 1);
        programCounter += 2;
    }
    else{
        instructionRegister = memory.Get(programCounter-1) + memory.Get(programCounter);
        programCounter += 2;
    }
}
void CPU::execute() {
    if (!flag) {
        char op;
        string last3;
        op = instructionRegister[0];
        string first, last;
        if (op == '1') {
            first += instructionRegister[1];
            last += instructionRegister[2];
            last += instructionRegister[3];
            cu.load(alu.hexadecimalToDecimal(first), alu.hexadecimalToDecimal(last), reg, memory);
        } else if (op == '2') {
            first += instructionRegister[1];
            last += instructionRegister[2];
            last += instructionRegister[3];
            cu.load_2(alu.hexadecimalToDecimal(first), last, reg);

        } else if (op == '3') {
            first += instructionRegister[1];
            last += instructionRegister[2];
            last += instructionRegister[3];
            cu.store(alu.hexadecimalToDecimal(first), alu.hexadecimalToDecimal(last), reg, memory);
            if(last=="00"){
                vec.push_back(memory.Get(alu.hexadecimalToDecimal(last)));
            }
        } else if (op == '4') {
            first += instructionRegister[1];
            last += instructionRegister[2];
            last += instructionRegister[3];
            cu.move(alu.hexadecimalToDecimal(first), alu.hexadecimalToDecimal(last), reg);

        } else if (op == '5') {
            string last1;
            first += instructionRegister[1];
            last += instructionRegister[2];
            last1 += instructionRegister[3];
            alu.add(alu.hexadecimalToDecimal(last), alu.hexadecimalToDecimal(last1), alu.hexadecimalToDecimal(first),
                    reg);
        }

        else if(op=='B'){
            first+=instructionRegister[1];
            last += instructionRegister[2];
            last += instructionRegister[3];
            if(cu.jump(alu.hexadecimalToDecimal(first),reg)){
                string a=memory.Get(alu.hexadecimalToDecimal(last));
                if(alu.hexadecimalToDecimal(last)%2==0){
                    string full=a+memory.Get(alu.hexadecimalToDecimal(last)+1);
                    programCounter=alu.hexadecimalToDecimal(last);
                    cout<<"Jump to memory["<<last<<"]\n";
                    while(memory.Get(programCounter)!="00") {
                        fetch();
                        execute();
                    }
                }
                else{
                    string full=memory.Get(alu.hexadecimalToDecimal(last)-1)+a;
                    programCounter=alu.hexadecimalToDecimal(last);
                    cout<<"Jump to memory["<<last<<"]\n";
                    while(memory.Get(programCounter)!="00") {
                        fetch();
                        execute();
                    }
                }
            }
        }

        else if (op == 'C') {
            flag=1;
            first += instructionRegister[1];
            last += instructionRegister[2];
            last += instructionRegister[3];
            if (first == "0" and last == "00") {
                cout << "HALT instruction encountered. Stopping execution.\n";
            }


        } else if (op == '6') {
            string last1;
            first += instructionRegister[1];
            last += instructionRegister[2];
            last1 += instructionRegister[3];
            alu.addFloatHexRegisters(alu.hexadecimalToDecimal(last), alu.hexadecimalToDecimal(last1),
                                     alu.hexadecimalToDecimal(first), reg);
        }

    }


}
void CPU:: vec_screen(){
    cout<<"[";
    for(int i=0;i<vec.size();i++){
        if(i!=vec.size()-1){
            cout<<vec[i]<<" , ";
        }
        else{
            cout<<vec[i];
        }

    }
    if(vec.empty()){
        cout<<"00";
    }
    cout<<"]";

}