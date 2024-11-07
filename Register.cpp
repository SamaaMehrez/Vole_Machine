#include "Register.h"
#include<bits/stdc++.h>
using namespace std;
// Define Register member functions here
Register::Register():registers(16,"00"){
}
void Register:: Set_reg(int reg,string val){
    if(reg<0 or reg>15){
        cout<<"Register index is not between 0 and 15\n";
    }
    registers[reg]=std::move(val);
}
string Register:: Get_Specific_Reg(int reg){
    if(reg<0 or reg>15){
        cout<<"Register index is not between 0 and 15\n";
    }
    return registers[reg];
}
void Register:: Print(){
    int count=0;
    for(int i=1;i<=registers.size();i++){
        count++;

        if(i>=11){
            cout<<"R"<<hex<<i-1<<": "<<registers[i-1]<<" ";
        }
        else{
            cout<<"R"<<i-1<<": "<<registers[i-1]<<" ";
        }
        if(count==4){
            cout<<endl;
            count=0;
        }
    }
}