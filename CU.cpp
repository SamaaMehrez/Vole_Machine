#include "CU.h"
CU::CU(){}
void CU:: load(int regIndex, int memAddress, Register& registers,Memory& memory) {
    if (regIndex >= 16  or memAddress >= 256) {
        cout<<"Invalid register or memory address\n";
    }
    string value=memory.Get(memAddress);
    registers.Set_reg(regIndex,value);
    cout<<"Loaded Value:"<<value<<" from memory["<<memAddress<<"] to register["<<regIndex<<"]\n";
}
void CU:: load_2(int regIndex,string index,Register& registers) {
    if (regIndex >= 16) {
        cout<<"Invalid register address\n";
    }
    registers.Set_reg(regIndex,index);
    cout<<"Loaded Value:"<<index<<" to register["<<regIndex<<"]\n";
}
void CU:: store(int regIndex, int memAddress,Register& registers,Memory& memory) {
    if (regIndex >= 16 or memAddress >= 256) {
        cout<<"Invalid register or memory address\n";
    }
    string value=registers.Get_Specific_Reg(regIndex);
    memory.Set(memAddress,value);
    cout<<"Store Value:"<<value<<" from register["<<regIndex<<"] to memory["<<memAddress<<"]\n";
}
void CU::move(int regIndex1, int regIndex2,Register& registers) {
    if (regIndex1 >= 16 or regIndex2 >= 16) {
        cout<<"Invalid register or memory address\n";
    }
    string value=registers.Get_Specific_Reg(regIndex1);
    registers.Set_reg(regIndex2,value);
    cout<<"Move Value:"<<value<<" from register["<<regIndex1<<"] to register["<<regIndex2<<"]\n";
}
bool CU:: jump(int idxReg,Register&reg){
    string com=reg.Get_Specific_Reg(idxReg);
    if(com==reg.Get_Specific_Reg(0)){
        return true;
    }
    else{
        return false;
    }

}